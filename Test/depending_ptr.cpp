#include <cstdint>

namespace std {
	bool pointer_cmp_eq_dep(void *p, void *q);
	bool pointer_cmp_ne_dep(void *p, void *q);
	bool pointer_cmp_gt_dep(void *p, void *q);
	bool pointer_cmp_ge_dep(void *p, void *q);
	bool pointer_cmp_lt_dep(void *p, void *q);
	bool pointer_cmp_le_dep(void *p, void *q);
}

template<typename T> class depending_ptr;

template<typename T>
class depending_ptr {
public:
	// Constructors
	depending_ptr(T *v);

	// Unary operators
	bool operator!(); // Prefix logical-not (is-NULL) operator
	T** operator&(); // Prefix address-of operator
	// No prefix bitwise complement operator (private)
	T operator*(); // Prefix indirection operator
	class depending_ptr<T> operator++(); // Prefix increment operator
	class depending_ptr<T> operator++(int); // Postfix increment operator
	class depending_ptr<T> operator--(); // Prefix decrement operator
	class depending_ptr<T> operator--(int); // Postfix decrement operator
	operator void*();
	T operator[](long int);

	// Binary relational operators
	bool operator==(T *v);
	bool operator!=(T *v);
	bool operator>(T *v);
	bool operator>=(T *v);
	bool operator<(T *v);
	bool operator<=(T *v);

	// Other binary operators
	class depending_ptr<T> operator+(long idx);
	class depending_ptr<T> operator+=(long idx);
	class depending_ptr<T> operator-(long idx);
	class depending_ptr<T> operator-=(long idx);

private:
	// Disabled operators.  Yes, they could work around with double...
	int operator~();
	int operator+();
	int operator-();
	int operator&(long int);
	int operator&=(long int);
	int operator%(long int);
	int operator%=(long int);
	int operator*(long int);
	int operator*=(long int);
	int operator/(long int);
	int operator/=(long int);
	int operator<<(long int);
	int operator<<=(long int);
	int operator>>(long int);
	int operator>>=(long int);
	int operator^(long int);
	int operator^=(long int);
	int operator|(long int);
	int operator|=(long int);

	T *dp_rep;
};


// Constructors

template<typename T>
depending_ptr<T>::depending_ptr(T *v)
{
	this->dp_rep = v;
}


// Unary operators

template<typename T>
bool depending_ptr<T>::operator!() // Prefix logical-not (is-NULL) operator
{
	return !this->dp_rep;
}

template<typename T>
T** depending_ptr<T>::operator&() // Prefix address-of operator
{
	return &this->dp_rep;
}

template<typename T>
T depending_ptr<T>::operator*() // Prefix indirection operator
{
	return *this->dp_rep;
}

template<typename T>
class depending_ptr<T> depending_ptr<T>::operator++() // Prefix increment operator
{
	++this->dp_rep;
	return *this;
}

template<typename T>
class depending_ptr<T> depending_ptr<T>::operator++(int)
{
	class depending_ptr<T> temp(this->dp_rep);

	++this->dp_rep;
	return temp;
}

template<typename T>
class depending_ptr<T> depending_ptr<T>::operator--()
{
	--this->dp_rep;
	return *this;
}

template<typename T>
class depending_ptr<T> depending_ptr<T>::operator--(int)
{
	class depending_ptr<T> temp(this->dp_rep);

	--this->dp_rep;
	return temp;
}

template<typename T>
depending_ptr<T>::operator void*() // Conversion to void* pointer
{
	return (void *)this->dp_rep;
}

template<typename T>
T depending_ptr<T>::operator[](long int idx)
{
	return this->dp_rep[idx];
}


// Binary relational operators

template<typename T>
bool depending_ptr<T>::operator==(T *v)
{
	return std::pointer_cmp_eq_dep(this->dp_rep, v);
}

template<typename T>
bool depending_ptr<T>::operator!=(T *v)
{
	return std::pointer_cmp_ne_dep(this->dp_rep, v);
}

template<typename T>
bool depending_ptr<T>::operator<(T *v)
{
	return std::pointer_cmp_gt_dep(this->dp_rep, v);
}

template<typename T>
bool depending_ptr<T>::operator<=(T *v)
{
	return std::pointer_cmp_ge_dep(this->dp_rep, v);
}

template<typename T>
bool depending_ptr<T>::operator>(T *v)
{
	return std::pointer_cmp_lt_dep(this->dp_rep, v);
}

template<typename T>
bool depending_ptr<T>::operator>=(T *v)
{
	return std::pointer_cmp_le_dep(this->dp_rep, v);
}

template<typename T>
class depending_ptr<T> depending_ptr<T>::operator+(long idx)
{
	class depending_ptr<T> temp(this->dp_rep + idx);

	return temp;
}

template<typename T>
class depending_ptr<T> depending_ptr<T>::operator+=(long idx)
{
	this->dp_rep += idx;
	return *this;
}

template<typename T>
class depending_ptr<T> depending_ptr<T>::operator-(long idx)
{
	class depending_ptr<T> temp(this->dp_rep - idx);

	return temp;
}

template<typename T>
class depending_ptr<T> depending_ptr<T>::operator-=(long idx)
{
	this->dp_rep -= idx;
	return *this;
}

#include <iostream>

int main(int argc, char **argv)
{
	char *cp = (char *)"abcde";
	depending_ptr<char> p(&cp[1]);
	depending_ptr<char> q((char *)nullptr);

	std::cout << "Initialized value: ";
	std::cout << *p;
	std::cout << "\nPostfix ++: ";
	p++;
	std::cout << *p;
	std::cout << "\nPrefix ++: ";
	++p;
	std::cout << *p;
	std::cout << "\nPostfix --: ";
	p--;
	std::cout << *p;
	std::cout << "\nPrefix --: ";
	--p;
	std::cout << *p;
	std::cout << "\nPrefix &: ";
	std::cout << &p;
	std::cout << "\nPrefix *&: ";
	std::cout << *&p;
	std::cout << "\nPrefix **&: ";
	std::cout << **&p;
	std::cout << "\nPrefix !: ";
	std::cout << !p;
	std::cout << "\nPrefix !nullptr: ";
	std::cout << !q;
	std::cout << "\nPostfix [2]: ";
	std::cout << p[2];
	std::cout << "\nPostfix [-1]: ";
	std::cout << p[-1];

	// Binary operators
	std::cout << "\nInfix ==: ";
	std::cout << (p == nullptr);
	std::cout << " Again but equal: ";
	std::cout << (p == p);
	std::cout << "\nInfix + 1: ";
	std::cout << p + 1;
	std::cout << " * ";
	std::cout << *(p + 1);
	std::cout << "\nInfix - 1: ";
	std::cout << p - 1;
	std::cout << " * ";
	std::cout << *(p - 1);

	std::cout << "\nInfix += 1: ";
	std::cout << (p += 1);
	std::cout << " * ";
	std::cout << *p;

	std::cout << "\nInfix -= 1: ";
	std::cout << (p -= 1);
	std::cout << " * ";
	std::cout << *p;

	std::cout << "\n";
	return 0;
}
