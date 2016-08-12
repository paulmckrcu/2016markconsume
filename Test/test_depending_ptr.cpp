#include <iostream>
#include "depending_ptr.hpp"

int main(int argc, char **argv)
{
	char *cp = (char *)"abcde";
	char *cp1;
	char *cp2;
	depending_ptr<char> p(&cp[1]);
	depending_ptr<char> q((char *)nullptr);
	std::atomic<char *> ap(cp);

	std::cout << "Initialized value: ";
	std::cout << *p;
	std::cout << "\nPostfix ++: ";
	std::cout << p++;
	std::cout << " result: ";
	std::cout << *p;

	std::cout << "\nPrefix ++: ";
	std::cout << ++p;
	std::cout << " result: ";
	std::cout << *p;

	std::cout << "\nPostfix --: ";
	std::cout << p--;
	std::cout << " result: ";
	std::cout << *p;

	std::cout << "\nPrefix --: ";
	std::cout << --p;
	std::cout << " result: ";
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

	std::cout << "\nInfix = cp: ";
	std::cout << (p = cp);
	std::cout << " * ";
	std::cout << *p;

	std::cout << "\nInfix q = p: ";
	std::cout << (q = p);
	std::cout << " * ";
	std::cout << *q;

	p = rcu_consume(cp);
	std::cout << "\nrcu_consume(cp): " << p;
	p = rcu_consume(&ap);
	std::cout << "\nrcu_consume(&ap): " << p;
	p = rcu_dereference(cp);
	std::cout << "\nrcu_dereference(cp): " << p;

	cp1 = rcu_store_release(&cp2, cp);
	std::cout << "\nrcu_store_release(&cp2, cp): " << cp1 << " -> " << cp2;
	cp1 = rcu_store_release(&ap, &cp[1]);
	std::cout << "\nrcu_store_release(&ap, &cp[1]): " << cp1 << " -> " << ap;
	cp1 = rcu_assign_pointer(ap, &cp[2]);
	std::cout << "\nrcu_assign_pointer(ap, &cp[2]): " << cp1 << " -> " << ap;

	std::cout << "\n";
	return 0;
}
