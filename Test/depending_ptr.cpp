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
	T* operator++(); // Prefix increment operator
	T* operator++(int); // Postfix increment operator
	T* operator--(); // Prefix decrement operator
	T* operator--(int); // Postfix decrement operator

	// Binary relational operators
	bool operator==(T *v);

private:
	// Disabled operators
	int operator~(); // No prefix bitwise complement operator
	int operator+(); // No prefix plus operator
	int operator-(); // No prefix negation operator

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
T* depending_ptr<T>::operator++() // Prefix increment operator
{
	++this->dp_rep;
	return this->dp_rep;
}

template<typename T>
T* depending_ptr<T>::operator++(int) // Postfix increment operator
{
	T *temp = this->dp_rep;

	++this->dp_rep;
	return temp;
}

template<typename T>
T* depending_ptr<T>::operator--() // Prefix decrement operator
{
	--this->dp_rep;
	return this->dp_rep;
}

template<typename T>
T* depending_ptr<T>::operator--(int) // Postfix decrement operator
{
	T *temp = this->dp_rep;

	--this->dp_rep;
	return temp;
}

template<typename T>
bool depending_ptr<T>::operator==(T *v) // Infix equality relational operator
{
	return this->dp_rep == v; // BUGGY -- need external function
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

	// Binary operators
	std::cout << "\nInfix ==: ";
	std::cout << (p == nullptr);
	// std::cout << " Again but equal: ";
	// std::cout << (p == p);

	std::cout << "\n";
	return 0;
}
