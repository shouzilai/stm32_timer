#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 10

typedef struct
{
    void *(*function)(void *);
    void *arg;
} threadpool_task_t;

typedef enum
{
    threadpool_invalid        = -1,
    threadpool_lock_failure   = -2,
    threadpool_queue_full     = -3,
    threadpool_shutdown       = -4,
    threadpool_thread_failure = -5
} threadpool_error_t;

typedef struct
{
    pthread_mutex_t lock;
    pthread_cond_t notify;
    pthread_t *threads;
    threadpool_task_t *queue;
    int thread_count;
    int queue_size;
    int head;
    int tail;
    int count;
    int shutdown;
    int started;
} threadpool_t;

threadpool_t *threadpool_create(int thread_count, int queue_size);
int threadpool_add(threadpool_t *pool, void (*function)(void *), void *arg);
int threadpool_destroy(threadpool_t *pool, int flags);

void *threadpool_thread(void *threadpool);

threadpool_t *threadpool_create(int thread_count, int queue_size)
{
    threadpool_t *pool;
    int i;

    if (thread_count <= 0 || thread_count > MAX_THREADS || queue_size <= 0)
    {
        return NULL;
    }

    if ((pool = (threadpool_t *)malloc(sizeof(threadpool_t))) == NULL)
    {
        goto err;
    }

    /* Initialize */
    pool->thread_count = 0;
    pool->queue_size = queue_size;
    pool->head = pool->tail = pool->count = 0;
    pool->shutdown = pool->started = 0;

    /* Allocate thread and task queue */
    pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * thread_count);
    pool->queue = (threadpool_task_t *)malloc(sizeof(threadpool_task_t) * queue_size);

    /* Initialize mutex and conditional variable first */
    if ((pthread_mutex_init(&(pool->lock), NULL) != 0) ||
        (pthread_cond_init(&(pool->notify), NULL) != 0) ||
        (pool->threads == NULL) ||
        (pool->queue == NULL))
    {
        goto err;
    }

    /* Start worker threads */
    for (i = 0; i < thread_count; i++)
    {
        if (pthread_create(&(pool->threads[i]), NULL,
                           threadpool_thread, (void *)pool) != 0)
        {
            threadpool_destroy(pool, 0);
            return NULL;
        }
        pool->thread_count++;
        pool->started++;
    }

    return pool;
err:
    if (pool)
    {
        threadpool_free(pool);
    }
    return NULL;
}

int threadpool_add(threadpool_t *pool, void (*function)(void *), void *arg)
{
    int err = 0;
    int next;

    if (pool == NULL || function == NULL)
    {
        return threadpool_invalid;
    }

    if (pthread_mutex_lock(&(pool->lock)) != 0)
    {
        return threadpool_lock_failure;
    }

    next = (pool->tail + 1) % pool->queue_size; // (MISSING)

    do
    {
        /* Are we full ? */
        if (pool->count == pool->queue_size)
        {
            err = threadpool_queue_full;
            break;
        }

        /* Are we shutting down ? */
        if (pool->shutdown)
        {
            err = threadpool_shutdown;
            break;
        }

        /* Add task to queue */
        pool->queue[pool->tail].function = function;
        pool->queue[pool->tail].arg = arg;
        pool->tail = next;
        pool->count += 1;

        /* pthread_cond_broadcast */
        if (pthread_cond_signal(&(pool->notify)) != 0)
        {
            err = threadpool_lock_failure;
            break;
        }
    } while (0);

    if (pthread_mutex_unlock(&pool->lock) != 0)
    {
        err = threadpool_lock_failure;
    }

    return err;
}

int threadpool_destroy(threadpool_t *pool, int flags)
{
    int i, err = 0;

    if (pool == NULL)
    {
        return threadpool_invalid;
    }

    if (pthread_mutex_lock(&(pool->lock)) != 0)
    {
        return threadpool_lock_failure;
    }

    do
    {
        /* Already shutting down */
        if (pool->shutdown)
        {
            err = threadpool_shutdown;
            break;
        }

        // pool->shutdown = (flags & threadpool_graceful) ? graceful_shutdown : immediate_shutdown;
        pool->shutdown = 1;

        /* Wake up all worker threads */
        if ((pthread_cond_broadcast(&(pool->notify)) != 0) ||
            (pthread_mutex_unlock(&(pool->lock)) != 0))
        {
            err = threadpool_lock_failure;
            break;
        }

        /* Join all worker thread */
        for (i = 0; i < pool->thread_count; i++)
        {
            if (pthread_join(pool->threads[i], NULL) != 0)
            {
                err = threadpool_thread_failure;
            }
        }
    } while (0);

    /* Only if everything went well do we deallocate the pool */
    if (!err)
    {
        threadpool_free(pool);
    }
    return err;
}

void *threadpool_thread(void *threadpool)
{
    threadpool_t *pool = (threadpool_t *)threadpool;
    threadpool_task_t task;

    for (;;)
    {
        /* Lock must be taken to wait on conditional variable */
        pthread_mutex_lock(&(pool->lock));

        /* Wait on condition variable, check for spurious wakeups.
           When returning from pthread_cond_wait(), we own the lock. */
        while ((pool->count == 0) && (!pool->shutdown))
        {
            pthread_cond_wait(&(pool->notify), &(pool->lock));
        }

        if (pool->shutdown)
        {
            break;
        }
        // if ((pool->shutdown == immediate_shutdown) ||
        //     ((pool->shutdown == graceful_shutdown) &&
        //      (pool->count == 0)))
        // {
        //     break;
        // }

        /* Grab our task */
        task.function = pool->queue[pool->head].function;
        task.arg = pool->queue[pool->head].arg;
        pool->head = (pool->head + 1) % pool->queue_size;
        pool->count -= 1;

        /* Unlock */
        pthread_mutex_unlock(&(pool->lock));

        /* Get to work */
        (*(task.function))(task.arg);
    }

    pool->started--;

    pthread_mutex_unlock(&(pool->lock));
    pthread_exit(NULL);
    return (NULL);
}