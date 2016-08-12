echo depending_ptr_simple
g++ -std=c++11 -g -o depending_ptr_simple depending_ptr_simple.cpp -lpthread &&
	./depending_ptr_simple
echo depending_ptr_inparam
g++ -std=c++11 -g -o depending_ptr_inparam depending_ptr_inparam.cpp -lpthread &&
	./depending_ptr_inparam
echo depending_ptr_outreturn
g++ -std=c++11 -g -o depending_ptr_outreturn depending_ptr_outreturn.cpp -lpthread &&
	./depending_ptr_outreturn
