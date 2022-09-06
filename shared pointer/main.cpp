#include <iostream>
#include "shared_ptr.hpp"
int main() {
    Shared_ptr<int> a(new int);
	a[0] = 18;
    Shared_ptr<int> b;
    b = a;
	std::cout<< a[0] <<std::endl;
}