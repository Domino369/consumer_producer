#include "product.h"

using namespace std;

product::product(const int& data) {
	this->data = data;
}

int product::get_data() const {
	return data;
}
