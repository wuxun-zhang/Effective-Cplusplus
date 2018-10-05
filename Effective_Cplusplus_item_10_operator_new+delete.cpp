#include<iostream>
using namespace std;

struct AirplaneRep{
	double length;
	double weight;
};

class Airplane {
	static void* operator new(size_t size);
	static void operator delete(void* deadObject, size_t size);
private:
	// 
	union {
		AirplaneRep *rep;
		Airplane *next;
	};
	// how many Airplane objects can be stored in a large mmeory block
	static const int BLOCK_SIZE;
	// free memory space
	// all objects share the same free list
	static Airplane *headOfFreeList;
};

void* Airplane::operator new(size_t size) {
	if (size != sizeof(Airplane))
		return ::operator new(size);

	Airplane* p = headOfFreeList;
	// the free list is not empty...
	if (p)
		headOfFreeList = p->next;
	else {
		Airplane* newBlock = static_cast<Airplane*>(::operator new(BLOCK_SIZE * sizeof(Airplane)));
		//  skip the first block (newBlock[0]) which will be returned to the caller
		for (int i = 1; i < BLOCK_SIZE; i++)
			newBlock[i].next = &newBlock[i + 1];
		newBlock[BLOCK_SIZE - 1].next = nullptr;
		p = newBlock;
		headOfFreeList = &newBlock[1];
	}
	return p;
}

void Airplane::operator delete(void* deadObject, size_t size) {
	if (deadObject == nullptr)
		return;
	if (size != sizeof(Airplane)) {
		::operator delete(deadObject);
		return;
	}
	// add useless memory to the head of free list
	Airplane *carcass = static_cast<Airplane*>(deadObject);
	carcass->next = headOfFreeList;
	headOfFreeList = carcass;
}

Airplane* Airplane::headOfFreeList;
const int Airplane::BLOCK_SIZE = 512;

/*
  define general memory pool
*/
class Pool {
public:
	Pool(size_t size);
	void* alloc(size_t size);
	void free(void* p, size_t size);
	~Pool();
};

Pool::Pool(size_t size) {

}

void* Pool::alloc(size_t size) {

}

void Pool::free(void* p, size_t size) {

}

Pool::~Pool() {

}