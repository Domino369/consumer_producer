#ifndef FACTORY_H
#define FACTORY_H

#include <pthread.h>
#include <semaphore.h>
#include <vector>

#include "product.h"

class factory {
	std::vector<product> vp;
	
public:	
	sem_t empty;
	sem_t full;
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	factory(const long&);
	~factory();

	void insert_item(int, product);
	void remove_item(int);
};

#endif
