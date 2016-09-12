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

using namespace std;

template<typename T>
class depending_ptr {
public:
	typedef T* pointer;
	typedef T element_type;

	// Constructors
	constexpr depending_ptr() noexcept;
	explicit depending_ptr(pointer v) noexcept;
	depending_ptr(nullptr_t) noexcept;
	depending_ptr(const depending_ptr &d) noexcept;
	depending_ptr(const depending_ptr &&d) noexcept;

	// Assignment
	depending_ptr& operator=(pointer p) noexcept;
	depending_ptr& operator=(const depending_ptr &d) noexcept;
	depending_ptr& operator=(const depending_ptr &&d) noexcept;
	depending_ptr& operator=(nullptr_t) noexcept;

	// Modifiers
	void swap(depending_ptr& d) noexcept;

	// Unary operators
	bool operator!() noexcept; // Prefix logical-not (is-nullptr) operator
	// No prefix bitwise complement operator
	element_type operator*(); // Prefix indirection operator
	pointer operator->();
	depending_ptr<element_type> operator++(); // Prefix increment operator
	depending_ptr<element_type> operator++(int); // Postfix increment operator
	depending_ptr<element_type> operator--(); // Prefix decrement operator
	depending_ptr<element_type> operator--(int); // Postfix decrement operator
	operator pointer();
	element_type operator[](size_t);

	// Binary relational operators
	bool operator==(pointer v) noexcept;
	bool operator!=(pointer v) noexcept;
	bool operator>(pointer v) noexcept;
	bool operator>=(pointer v) noexcept;
	bool operator<(pointer v) noexcept;
	bool operator<=(pointer v) noexcept;

	// Other binary operators
	depending_ptr<T> operator+(long idx);
	depending_ptr<T> operator+=(long idx);
	depending_ptr<T> operator-(long idx);
	depending_ptr<T> operator-=(long idx);

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
	pointer dp_rep;
};


// Constructors

template<typename T> constexpr depending_ptr<T>::depending_ptr() noexcept : dp_rep(nullptr) {}
template<typename T> depending_ptr<T>::depending_ptr(pointer v) noexcept : dp_rep(v) {}
template<typename T> depending_ptr<T>::depending_ptr(nullptr_t) noexcept : depending_ptr() {}
template<typename T> depending_ptr<T>::depending_ptr(const depending_ptr &d) noexcept : dp_rep(d.dp_rep) {}
template<typename T> depending_ptr<T>::depending_ptr(const depending_ptr &&d) noexcept : dp_rep(d.dp_rep) {}

// Assignment
template<typename T> depending_ptr<T>& depending_ptr<T>::operator=(pointer p) noexcept { dp_rep = p; return *this; }
template<typename T> depending_ptr<T>& depending_ptr<T>::operator=(const depending_ptr<T> &d) noexcept { dp_rep = d.dp_rep; return *this; }
template<typename T> depending_ptr<T>& depending_ptr<T>::operator=(const depending_ptr<T> &&d) noexcept { dp_rep = d.dp_rep; return *this; }
template<typename T> depending_ptr<T>& depending_ptr<T>::operator=(nullptr_t) noexcept { dp_rep = nullptr; return *this; }

// Modifiers
template<typename T> void depending_ptr<T>::swap(depending_ptr<T>& d) noexcept { pointer p = d.dp_rep; d.dp_rep = dp_rep; dp_rep = p; }

// Unary operators
template<typename T> bool depending_ptr<T>::operator!() noexcept { return !dp_rep; }
template<typename T> T depending_ptr<T>::operator*() { return *dp_rep; }
template<typename T> typename depending_ptr<T>::pointer depending_ptr<T>::operator->() { return dp_rep; }
template<typename T> depending_ptr<T> depending_ptr<T>::operator++() { ++dp_rep; return *this; }
template<typename T> depending_ptr<T> depending_ptr<T>::operator++(int)
{
	depending_ptr<T> temp(dp_rep);
	++dp_rep;
	return temp;
}
template<typename T> depending_ptr<T> depending_ptr<T>::operator--() { --dp_rep; return *this; }
template<typename T> depending_ptr<T> depending_ptr<T>::operator--(int)
{
	depending_ptr<T> temp(dp_rep);
	--dp_rep;
	return temp;
}
template<typename T> depending_ptr<T>::operator pointer() { return dp_rep; }
template<typename T> T depending_ptr<T>::operator[](size_t idx) { return dp_rep[idx]; }


// Binary relational operators

template<typename T>
bool depending_ptr<T>::operator==(pointer v) noexcept
{
	return std::pointer_cmp_eq_dep(dp_rep, v);
}

template<typename T>
bool depending_ptr<T>::operator!=(pointer v) noexcept
{
	return std::pointer_cmp_ne_dep(dp_rep, v);
}

template<typename T>
bool depending_ptr<T>::operator<(pointer v) noexcept
{
	return std::pointer_cmp_gt_dep(dp_rep, v);
}

template<typename T>
bool depending_ptr<T>::operator<=(pointer v) noexcept
{
	return std::pointer_cmp_ge_dep(dp_rep, v);
}

template<typename T>
bool depending_ptr<T>::operator>(pointer v) noexcept
{
	return std::pointer_cmp_lt_dep(dp_rep, v);
}

template<typename T>
bool depending_ptr<T>::operator>=(pointer v) noexcept
{
	return std::pointer_cmp_le_dep(dp_rep, v);
}

template<typename T>
depending_ptr<T> depending_ptr<T>::operator+(long idx)
{
	depending_ptr<T> temp(dp_rep + idx);

	return temp;
}

template<typename T>
depending_ptr<T> depending_ptr<T>::operator+=(long idx)
{
	dp_rep += idx;
	return *this;
}

template<typename T>
depending_ptr<T> depending_ptr<T>::operator-(long idx)
{
	depending_ptr<T> temp(dp_rep - idx);

	return temp;
}

template<typename T>
depending_ptr<T> depending_ptr<T>::operator-=(long idx)
{
	dp_rep -= idx;
	return *this;
}

// RCU functions for testing, not necessarily for standardization.

template<typename T>
depending_ptr<T> rcu_consume(std::atomic<T*> *p)
{
	volatile std::atomic<typename depending_ptr<T>::pointer> *q = p;
	// Change to memory_order_consume once it is fixed
	depending_ptr<T> temp(q->load(std::memory_order_relaxed));

	return temp;
}

template<typename T>
depending_ptr<T> rcu_consume(T *p)
{
	// Alternatively, could cast p to volatile atomic...
	depending_ptr<T> temp(*(T *volatile *)&p);

	return temp;
}

template<typename T>
T* rcu_store_release(std::atomic<T*> *p, T *v)
{
	p->store(v, std::memory_order_release);
	return v;
}

template<typename T>
T* rcu_store_release(T **p, T *v)
{
	// Alternatively, could cast p to volatile atomic...
	atomic_thread_fence(std::memory_order_release);
	*((volatile T **)p) = v;
	return v;
}

// Linux-kernel compatibility macros, not for atomics

#define rcu_dereference(p) rcu_consume(p)
#define rcu_assign_pointer(p, v) rcu_store_release(&(p), v)
