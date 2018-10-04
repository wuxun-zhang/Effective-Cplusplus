#include<iostream>
#include<new>
using namespace std;

// define base class that supports different new_handler for different derived classes
template<class T>
class NewHandlerSupport {
public:
	static new_handler set_new_handler(new_handler p);
	static void* operator new(size_t size);
	static void operator delete(void* rawMemory, size_t size);
private:
	static new_handler currentHandler;
};

// define member funtion body
template<class T>
new_handler NewHandlerSupport<T>::set_new_handler(new_handler p) {
	new_handler oldHandler = currentHandler;
	currentHandler = p;
	return oldHandler;
}

// overloaded operator new
template<class T>
void* NewHandlerSupport<T>::operator new(size_t size) {
	// get the previous handler pointer 
	new_handler globalHandler = std::set_new_handler(currentHandler);
	void* memory;
	// catch exception (std::bad_alloc)
	try {
		memory = ::operator new(size);
	}
	catch (std::bad_alloc&) {
		std::set_new_handler(globalHandler);
		throw;
	}

	std::set_new_handler(globalHandler);
	return memory;
}

template<class T>
void NewHandlerSupport<T>::operator delete(void* rawMemory, size_t size) {
	if (!rawMemory)
		return;
	// free memory space pointed by rawMemory
	::operator delete rawMemory;

	return;
}

// set currentHandler to 0
template<class T>
new_handler NewHandlerSupport<T>::currentHandler;


// define a class which has new handler
class X : public NewHandlerSupport<X> {
public:
	/*
	other member funtions
	*/
private:
	/*
	define member varibles
	*/
};
