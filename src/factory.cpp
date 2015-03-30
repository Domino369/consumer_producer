#include <iostream>

#include "factory.h"

using namespace std;

factory::factory(const long& size) {
	/* semaphore initialization */
    sem_init(&empty, 0, size);
    sem_init(&full, 0, 0);
}

factory::~factory() {
	sem_destroy(&empty);
	sem_destroy(&full);
	pthread_mutex_destroy(&mutex);
}

void factory::insert_item(int thr_id, product prd) {
	/* insert item */
    vp.push_back(prd);
    
    cout << "Producer #"
		 << thr_id
		 << " inserted product #"
		 << vp.rbegin()->get_data()
		 << ". Total: "
		 << vp.size()
		 << endl;
}

void factory::remove_item(int thr_id) {
    cout << "Consumer #"
		 << thr_id
		 << " removed product #"
		 << vp.rbegin()->get_data()
		 << ". Total: "
		 << vp.size() - 1
		 << endl;
		 
	/* remove item */
    vp.pop_back();
}
