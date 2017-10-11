/* Pthreads setup: initialize mutex and explicitly create threads in a
     joinable state (for portability).  Pass each thread its loop offset */

    pthread_mutex_init(&sum_mutex, NULL);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


/* Clean up and exit */
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&sum_mutex);
    pthread_exit (NULL);

  /*  Declare and initialize the mutex: */  pthread_mutex_t *mutex;
       const pthread_mutexattr_t *attr;
           pthread_mutex_init(mutex, attr)

   /* Get a lock on the mutex */  pthread_mutex_lock(mutex);

  // Execute the critical section

  /* Unlock the mutex */  pthread_mutex_unlock(mutex);
