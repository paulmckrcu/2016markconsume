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
private:
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
	depending_ptr<T*> temp(&this->dp_rep);
	return temp;
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

#include <iostream>

int main(int argc, char **argv)
{
	char *cp = (char *)"abcde";
	depending_ptr<char> p(&cp[1]);

	std::cout << "Initialized value: ";
	std::cout << *p;
	std::cout << "\nPostfix ++: ";
	p++;
	std::cout << *p;
	std::cout << "\nPrefix ++: ";
	++p;
	std::cout << *p;
	std::cout << "\n";
	return 0;
}
