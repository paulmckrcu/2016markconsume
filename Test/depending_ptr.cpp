// T must be a pointer type.
template<typename T> class depending_ptr;

template<typename T>
class depending_ptr {
	// Unary operators
	bool operator!(); // Prefix logical-not (is-NULL) operator
	T* operator&(); // Prefix address-of operator
	// No prefix bitwise complement operator (private)
	T& operator*(); // Prefix indirection operator
	T& operator++(); // Prefix increment operator
	T operator++(int); // Postfix increment operator
private:
	int operator~(); // No prefix bitwise complement operator
	T dp_rep;
};


// Unary operators

template<typename T>
bool depending_ptr<T>::operator!() // Prefix logical-not (is-NULL) operator
{
	return !this->dp_rep;
}

template<typename T>
T* depending_ptr<T>::operator&() // Prefix address-of operator
{
	T *temp = &this;
	return temp;
}

template<typename T>
T& depending_ptr<T>::operator*() // Prefix indirection operator
{
	return *this.dp_rep;
}

template<typename T>
T& depending_ptr<T>::operator++() // Prefix increment operator
{
	++this->dp_rep;
	return *this;
}

template<typename T>
T depending_ptr<T>::operator++(int) // Postfix increment operator
{
	T temp = this->dp_rep;

	++this->dp_rep;
	return temp;
}

int main(int argc, char **argv)
{
	char *cp = "abcde";
	depending_ptr<char *> p = &cp[1];

	return 0;
}
