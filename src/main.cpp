#include <pthread.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>

#include "factory.h"
#include "product.h"

using namespace std;

static int prd_num = 0;
static factory* f;

void *producer(void*);
void *consumer(void*);

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "The correct format to execute is:"
			 << endl
			 << "\t./producer_consumer <size of semaphore> <number of product>"
			 << endl;
		exit(1);
	}
	
	istringstream* ss;
	long size, num_of_prod;
	
	ss = new istringstream(argv[1]);
	if (!(*ss >> size)) {
		cerr << "Invalid number " << argv[1] << '\n';
		exit(2);
	}
	
	ss = new istringstream(argv[2]);
	if (!(*ss >> num_of_prod)) {
		cerr << "Invalid number " << argv[2] << '\n';
		exit(3);
	}
	
	f = new factory(size);
	
	/* pthreads */
	pthread_t producers[num_of_prod];
	pthread_t consumers[num_of_prod];
	
	/* return code */
	int rc;
	
	/* creation of all producers */
	for (long i = 0; i < num_of_prod; i++) {
		/* create pthread */
		rc = pthread_create(&producers[i], NULL, producer, (void *)i);
		
		/* if error */
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(4);
		}
	}
	
	/* creation of all consumers */
	for (long i = 0; i < num_of_prod; i++) {
		/* create pthread */
		rc = pthread_create(&consumers[i], NULL, consumer, (void *)i);
	
		/* if error */
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(5);
		}
	}
	
	/* wait for all pthreads to end */
	for (long i = 0; i < num_of_prod; i++) {
		pthread_join(producers[i], NULL);
		pthread_join(consumers[i], NULL);
	}
	
	cout << "All threads are done!" << endl;
	
	/* free memory */
	delete f;
	
	cout << "All resources are cleaned up!" << endl;
	
	/* Last thing that main() should do */
	pthread_exit(NULL);
}

void* producer(void* thr_id) {
	//for (int i = 0; i < 20; i++) {
		product p(prd_num++);
        sem_wait(&(f->empty));						/* wait for empty slot */
        pthread_mutex_lock(&(f->mutex));			/* locks critical section */
        f->insert_item((long)thr_id, p);			/* if fail, retry */
        this_thread::sleep_for(chrono::seconds(1));	/* sleep for 1 second */
        pthread_mutex_unlock(&(f->mutex));			/* let go of critical section */
        sem_post(&(f->full));						/* alert that there is a cookie */
    //}
    
    /* exit */
    pthread_exit(NULL);
}

void *consumer(void *thr_id)
{
    //for (int i = 0; i < MAX_PASS; i++) {
        sem_wait(&(f->full));						/* wait for cookie */
        pthread_mutex_lock(&(f->mutex));			/* locks critical section */
        f->remove_item((long)thr_id);				/* if fail, retry */
        this_thread::sleep_for(chrono::seconds(1));	/* sleep for 1 second */
        pthread_mutex_unlock(&(f->mutex));			/* let go of critical section */
        sem_post(&(f->empty));						/* alert that a cookie has been eaten */
    //}
    
    /* exit */
    pthread_exit(NULL);
}
