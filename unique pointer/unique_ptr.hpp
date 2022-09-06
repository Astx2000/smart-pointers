#include <iostream>
#include <functional>

template<typename T , typename deletor = std::function<void(T*)> >
class Unique_ptr {
public:
	Unique_ptr(T*);
	Unique_ptr(T*,deletor);
	Unique_ptr(deletor);
	Unique_ptr(Unique_ptr&);
	~Unique_ptr();
public:
	T& get()const;
	deletor getDeletor()const;
public:
	T& operator*()const;
	T& operator->()const;
	T& operator[](size_t);
	const T& operator[](size_t)const;
    T* release();
	bool operator==(const Unique_ptr&)const;
	bool operator!=(const Unique_ptr&)const;
	bool operator>=(const Unique_ptr&)const;
	bool operator<=(const Unique_ptr&)const;
	bool operator>(const Unique_ptr&)const;
	bool operator<(const Unique_ptr&)const; 
private:
	void clear();
	T* ptr;
	deletor del;
};

template<typename T,typename deletor>
Unique_ptr<T,deletor>::Unique_ptr(T* in_ptr) {
	ptr = in_ptr;
	del = nullptr;
}
template<typename T,typename deletor>
Unique_ptr<T,deletor>::Unique_ptr(T* in_ptr,deletor in_del) {
	ptr = in_ptr;
	del = in_del;
}

template<typename T,typename deletor>
Unique_ptr<T,deletor>::Unique_ptr(deletor in_del) {
	ptr = nullptr;
	del = in_del;
}

template<typename T,typename deletor>
Unique_ptr<T,deletor>::Unique_ptr(Unique_ptr<T,deletor>& other) {
	ptr = other.ptr;
	del = other.del;
}

template<typename T,typename deletor>
void Unique_ptr<T,deletor>::clear() {
	if (del != nullptr)
	{
		del(ptr);
		return;
	}
	delete ptr;
}

template<typename T,typename deletor>
Unique_ptr<T,deletor>::~Unique_ptr() {
	this->clear();
}

template<typename T,typename deletor>
T& Unique_ptr<T,deletor>::get()const {
	return *ptr;
}

template<typename T,typename deletor>
deletor Unique_ptr<T,deletor>::getDeletor()const {
	return del;
}

template<typename T,typename deletor>
T& Unique_ptr<T,deletor>::operator*()const {
	return *ptr;
}

template<typename T,typename deletor>
T& Unique_ptr<T,deletor>::operator->()const {
	return *ptr;
}

template<typename T,typename deletor>
const T& Unique_ptr<T,deletor>::operator[](size_t pos)const {
	return ptr[pos];
}

template<typename T,typename deletor>
T& Unique_ptr<T,deletor>::operator[](size_t pos) {
	return ptr[pos];
}
template<typename T,typename deletor>
T* Unique_ptr<T,deletor>::release() {
    T* tmp = this->ptr;
    this->ptr = nullptr;
    return tmp;
}

template<typename T,typename deletor>
bool Unique_ptr<T,deletor>::operator==(const Unique_ptr<T,deletor>& other)const {
	return *ptr == *other.ptr;
}
template<typename T,typename deletor>
bool Unique_ptr<T,deletor>::operator!=(const Unique_ptr<T,deletor>& other)const {
	return *ptr != *other.ptr;
}
template<typename T,typename deletor>
bool Unique_ptr<T,deletor>::operator>=(const Unique_ptr<T,deletor>& other)const {
	return *ptr >= *other.ptr;
}
template<typename T,typename deletor>
bool Unique_ptr<T,deletor>::operator<=(const Unique_ptr<T,deletor>& other)const {
	return *ptr <= *other.ptr;
}
template<typename T,typename deletor>
bool Unique_ptr<T,deletor>::operator>(const Unique_ptr<T,deletor>& other)const {
	return *ptr > *other.ptr;
}
template<typename T,typename deletor>
bool Unique_ptr<T,deletor>::operator<(const Unique_ptr<T,deletor>& other)const {
	return *ptr < *other.ptr;
}

