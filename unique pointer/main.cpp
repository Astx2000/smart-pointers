#include <functional>
#include <iostream>

#include "unique_ptr.hpp"

int clear(int* ptr)
{
	delete[]ptr;
	return 0;
}
int main()
{
	auto it = [] (int*& ptr)->int{delete[]ptr;return 0;};
	int * tmp = new int[5];
	Unique_ptr<int,decltype(it)> p(tmp,it);
	p[0] = 15;
	p[1] = 18;
	std::cout<< p[0] <<std::endl;
	std::cout<< p[1] <<std::endl;
	return 0;
}