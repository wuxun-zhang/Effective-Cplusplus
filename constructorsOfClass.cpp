#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Sales_data {
public:
	Sales_data();
	Sales_data(string bNo, int p, double r);
	Sales_data(const Sales_data& other);
	~Sales_data();
	// const member function
	string get_name(void) const;
	int get_price(void) const;
	Sales_data& operator=(const Sales_data& other);
private:
	string bookNo;
	int price;
	double revenue;
};

// copy constructor
// the first parameter must be a reference to another object
Sales_data::Sales_data(const Sales_data& other) {
	if (this != &other) {
		bookNo = other.bookNo;
		price = other.price;
		revenue = other.revenue;
	}
	cout << "copy ctor is called!!!" << endl;
}

Sales_data::Sales_data() {
	cout << "synthesized ctor is called!!!" << endl;
}

// common constructor
// initialization list
Sales_data::Sales_data(string bNo, int p, double r) :
	bookNo(bNo), price(p), revenue(r) {
	cout << "common ctor is called!!!" << endl;
}

Sales_data::~Sales_data() {
	cout << "synthesized dtor is called!!!" << endl;
}

string Sales_data::get_name(void) const {
	return bookNo;
}

int Sales_data::get_price(void) const {
	return price;
}

// copy-assignment operator
// the return value should be a reference to (this) object
Sales_data& Sales_data::operator=(const Sales_data& other) {
	cout << "operator= is called!!!" << endl;
	if (this != &other) {
		this->bookNo = other.bookNo;
		this->price = other.price;
		this->revenue = other.revenue;
	}
	return *this;
}

int main(void) {
	Sales_data A("Harry Potter", 30, 8.9);
	Sales_data B(A);
	Sales_data C = A;
	cout << "C.price = " << C.get_price() << endl;
	cout << "C.bookNo = " << C.get_name() << endl;

	//vector<Sales_data> vec(5);
	//Sales_data arr[5];
	//Sales_data *ptr = (Sales_data*)malloc(5 * sizeof(Sales_data));
	//free(ptr);
	
	Sales_data* ptr = new Sales_data[5];
	delete[] ptr;

	return 0;
}