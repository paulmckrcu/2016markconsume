#include <cstdint>
#include <atomic>

namespace std {
	bool pointer_cmp_eq_dep(void *p, void *q) noexcept;
	bool pointer_cmp_ne_dep(void *p, void *q) noexcept;
	bool pointer_cmp_gt_dep(void *p, void *q) noexcept;
	bool pointer_cmp_ge_dep(void *p, void *q) noexcept;
	bool pointer_cmp_lt_dep(void *p, void *q) noexcept;
	bool pointer_cmp_le_dep(void *p, void *q) noexcept;
}

template<typename T>
class depending_ptr {
public:
	// Constructors
	depending_ptr(T *v) noexcept;
	depending_ptr() noexcept;

	// Unary operators
	bool operator!() noexcept; // Prefix logical-not (is-NULL) operator
	class depending_ptr<T>* operator&(); // Prefix address-of operator
	// No prefix bitwise complement operator (private)
	T operator*(); // Prefix indirection operator
	T *operator->();
	class depending_ptr<T> operator++(); // Prefix increment operator
	class depending_ptr<T> operator++(int); // Postfix increment operator
	class depending_ptr<T> operator--(); // Prefix decrement operator
	class depending_ptr<T> operator--(int); // Postfix decrement operator
	operator T*();
	T operator[](long int);

	// Binary relational operators
	bool operator==(T *v) noexcept;
	bool operator!=(T *v) noexcept;
	bool operator>(T *v) noexcept;
	bool operator>=(T *v) noexcept;
	bool operator<(T *v) noexcept;
	bool operator<=(T *v) noexcept;

	// Other binary operators
	class depending_ptr<T> operator+(long idx);
	class depending_ptr<T> operator+=(long idx);
	class depending_ptr<T> operator-(long idx);
	class depending_ptr<T> operator-=(long idx);

	// Disabled operators.  Yes, they could work around with double...
	int operator~() = delete;
	int operator+() = delete;
	int operator-() = delete;
	int operator&(long int) = delete;
	int operator&=(long int) = delete;
	int operator%(long int) = delete;
	int operator%=(long int) = delete;
	int operator*(long int) = delete;
	int operator*=(long int) = delete;
	int operator/(long int) = delete;
	int operator/=(long int) = delete;
	int operator<<(long int) = delete;
	int operator<<=(long int) = delete;
	int operator>>(long int) = delete;
	int operator>>=(long int) = delete;
	int operator^(long int) = delete;
	int operator^=(long int) = delete;
	int operator|(long int) = delete;
	int operator|=(long int) = delete;

private:
	T *dp_rep;
};


// Constructors

template<typename T>
depending_ptr<T>::depending_ptr(T *v) noexcept
{
	this->dp_rep = v;
}

template<typename T>
depending_ptr<T>::depending_ptr() noexcept
{
}


// Unary operators

template<typename T>
bool depending_ptr<T>::operator!() noexcept
{
	return !this->dp_rep;
}

template<typename T>
class depending_ptr<T>* depending_ptr<T>::operator&()
{
	return this;
}

template<typename T>
T depending_ptr<T>::operator*() // Prefix indirection operator
{
	return *this->dp_rep;
}

template<typename T>
T *depending_ptr<T>::operator->()
{
	return this->dp_rep;
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
depending_ptr<T>::operator T*() // Conversion to T* pointer
{
	return this->dp_rep;
}

template<typename T>
T depending_ptr<T>::operator[](long int idx)
{
	return this->dp_rep[idx];
}


// Binary relational operators

template<typename T>
bool depending_ptr<T>::operator==(T *v) noexcept
{
	return std::pointer_cmp_eq_dep(this->dp_rep, v);
}

template<typename T>
bool depending_ptr<T>::operator!=(T *v) noexcept
{
	return std::pointer_cmp_ne_dep(this->dp_rep, v);
}

template<typename T>
bool depending_ptr<T>::operator<(T *v) noexcept
{
	return std::pointer_cmp_gt_dep(this->dp_rep, v);
}

template<typename T>
bool depending_ptr<T>::operator<=(T *v) noexcept
{
	return std::pointer_cmp_ge_dep(this->dp_rep, v);
}

template<typename T>
bool depending_ptr<T>::operator>(T *v) noexcept
{
	return std::pointer_cmp_lt_dep(this->dp_rep, v);
}

template<typename T>
bool depending_ptr<T>::operator>=(T *v) noexcept
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

// RCU functions for testing, not necessarily for standardization.

template<typename T>
class depending_ptr<T> rcu_consume(std::atomic<T*> *p)
{
	volatile std::atomic<T*> *q = p;
	// Change to memory_order_consume once it is fixed
	class depending_ptr<T> temp(q->load(std::memory_order_relaxed));

	return temp;
}

template<typename T>
class depending_ptr<T> rcu_consume(T *p)
{
	// Alternatively, could cast p to volatile atomic...
	class depending_ptr<T> temp(*(T* volatile *)&p);

	return temp;
}

template<typename T>
T *rcu_store_release(std::atomic<T*> *p, T *v)
{
	p->store(v, std::memory_order_release);
	return v;
}

template<typename T>
T *rcu_store_release(T **p, T *v)
{
	// Alternatively, could cast p to volatile atomic...
	atomic_thread_fence(std::memory_order_release);
	*((volatile T **)p) = v;
	return v;
}

// Linux-kernel compatibility macros, not for atomics

#define rcu_dereference(p) rcu_consume(p)
#define rcu_assign_pointer(p, v) rcu_store_release(&(p), v)
