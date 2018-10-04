#include<iostream>
#include<new>
using namespace std;

/*
	non class-member operator new realization
*/

/*

void* operator new(size_t size){
	// instead of processing 0-byte request, we can process 1-byte request
	if(size == 0)
		size=1;
	
	// step into loop of memory allocation
	while(1){
		//alloc memory space of size bytes
		void* memory;
		memory = ::operator new(size);

		if (memory != nullptr):
			return memory;
		
		// allocation failed
		new_handler globalHandler = set_new_handler(0);
		set_new_handler(globalHandler);

		if(globalHandler)
			(*globalHandler)();
		else
			throw std::bad_alloc();
	}
	
}

*/

class Base {
public:
	static void* operator new(size_t size);
	static void operator delete(void* rawMemory, size_t size);
};

void* Base::operator new(size_t size) {
	if (size != sizeof(Base))
		return ::operator new(size);
	// use Base::operator new to alloc memory space

}

void Base::operator delete(void* rawMemory, size_t size) {
	if (rawMemory == 0)
		return;
	if (size != sizeof(Base)) {
		::operator delete(rawMemory);
		return;
	}

	// use Base::operator delete to free memory space pointed by rawMemory
	
	return;
}

class Derived :public Base {

};

