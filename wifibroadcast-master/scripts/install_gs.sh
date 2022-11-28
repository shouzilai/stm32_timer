#!/bin/bash
set -e

if [[ $# -eq 0 ]] ; then
    echo 'Please specify the name of the WiFi adapter'
    echo 'Find the name using command: ip a'
    echo 'Aborting ...'
    exit 1
fi

IFNAME="${1}"

# Install required packages
apt update
apt upgrade

apt install python3-all libpcap-dev libsodium-dev python3-pip python3-pyroute2 \
  python3-future python3-twisted python3-serial iw virtualenv debhelper dh-python build-essential -y

# Build
make deb

# Create key and copy to right location
./wfb_keygen
mv gs.key /etc/gs.key

# Install
dpkg -i deb_dist/*.deb 

# Setup config
cat <<EOF >> /etc/wifibroadcast.cfg
[common]
wifi_channel = 161     # 161 -- radio channel @5825 MHz, range: 5815–5835 MHz, width 20MHz
                       # 1 -- radio channel @2412 Mhz, 
                       # see https://en.wikipedia.org/wiki/List_of_WLAN_channels for reference
wifi_region = 'BO'     # Your country for CRDA (use BO or GY if you want max tx power)  

[gs_mavlink]
peer = 'connect://127.0.0.1:14550'  # outgoing connection
# peer = 'listen://0.0.0.0:14550'   # incoming connection

[gs_video]
peer = 'connect://127.0.0.1:5600'  # outgoing connection for
                                   # video sink (QGroundControl on GS)
EOF

echo "WFB_NICS=\"${IFNAME}\"" > /etc/default/wifibroadcast

cat <<EOF >> /etc/NetworkManager/NetworkManager.conf
[keyfile]
unmanaged-devices=interface-name:${IFNAME}
EOF

if [ -f /etc/dhcpcd.conf ]; then
    echo "denyinterfaces ${IFNAME}" >> /etc/dhcpcd.conf
fi

# Start gs service
systemctl daemon-reload
systemctl start wifibroadcast@gs

echo "Started wifibroadcast@gs"
systemctl status wifibroadcast@gs
