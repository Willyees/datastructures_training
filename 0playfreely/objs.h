#pragma once
#include <iostream>
#include <string>

class A {
	mutable int _i = 7;
public:
	int ptr;

	A(int i) : ptr(i){
		std::cout << "construct int called" << std::endl;

	}
	A(int i, double b) {
		std::cout << "construct int, double called" << std::endl;

	}

	A(std::initializer_list<int> i) {
		std::cout << "initializer list construct int called" << std::endl;

	}
	A() {
		std::cout << "construct called" << std::endl;

	}

	/*A(A& o) {
		std::cout << "copy constructor called" << std::endl;
	}*/

	~A() {
		std::cout << "destructor base called" << std::endl;
	}

	void print() const { std::cout << "Base i: " << i << std::endl; };
	

	std::string name = "A";
	int i = 5;

	void del_this() {
		delete this;
	}

	void set_i(int i) const {
		_i = i;
	}
};

class Derived : public A {
public:
	Derived() {
		std::cout << "constructor derived called" << std::endl;
	}

	~Derived()  {
		std::cout << "destructor derived class called" << std::endl;
	}
	void print() const { std::cout << "Derived i " << i << std::endl; };;
};

class BankCustomer {
	double amount = 100.0;
public:
	BankCustomer() {
		
	}
	~BankCustomer() = default;

	BankCustomer(const BankCustomer& b) = default;

	//operator overloadings
	void operator++() {
		BankCustomer b;
		amount += 1.0;
		b.amount = amount;
		//return b;
	}

	BankCustomer operator+(BankCustomer& b) {
		BankCustomer b_new;
		b_new.amount = this->amount + b.amount;
		return b_new;
	}

	bool operator ==(BankCustomer& b) {
		if (this == &b)
			return true;
		return false;
	}

	inline void print() { std::cout << amount << std::endl; }
	inline void set_amount(double amount) { this->amount = amount; }
	
};