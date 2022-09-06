#include <iostream>

template<typename T>
void Deletor(T*m_ptr) {
        delete m_ptr;
}
template<typename T,typename DT = void(*)(int)>
struct DataPointer {
        int count;
	DT Del_ptr;
	DataPointer() {
		count = 0;
		Del_ptr = Deletor<T>;
	}
};
template<typename T,typename DT = void(*)(int)>
class Shared_ptr {
private:
        T* m_ptr;
        DataPointer<T>* buf;
public:
        Shared_ptr() {
                m_ptr = NULL;
                buf = nullptr;
        }
        Shared_ptr(T*in_ptr) {
                m_ptr = in_ptr;
                buf = new DataPointer<T>;
                buf->count++ ;
                buf->Del_ptr = Deletor<T>;
        }
        Shared_ptr(const Shared_ptr<T>& tmp) {
                this->m_ptr = tmp.m_ptr;
                this->buf = tmp.buf;
                this->buf->count++ ;
                buf->Del_ptr = Deletor<T>;
        }
        Shared_ptr(Shared_ptr<T>&& tmp) {
                this->m_ptr = tmp.m_ptr;
                this->buf = tmp.buf;
                tmp.m_ptr = nullptr ;
                tmp.buf = nullptr ;
        }
        Shared_ptr<T> operator=(const Shared_ptr<T>& tmp) {
                if(this == &tmp){ return *this; }
                delete m_ptr ;
                delete buf;
                this->m_ptr = tmp.m_ptr;
                this->buf = tmp.buf;
                this->buf->count++ ;
                return tmp ;
        }
        ~Shared_ptr() {
                buf->count--;
                if(!buf->count && m_ptr!=nullptr) {
                        buf->Del_ptr(m_ptr);
                }
}
        T& operator[](int index){
                return m_ptr[index];
        }
};
