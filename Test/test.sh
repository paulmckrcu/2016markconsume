#!/bin/bash

set -e
set -u
set -x

CC=${CC:-g++}

$CC -std=c++11 -g -o depending_ptr_simple depending_ptr_simple.cpp -lpthread &&
	./depending_ptr_simple

$CC -std=c++11 -g -o depending_ptr_inparam depending_ptr_inparam.cpp -lpthread &&
	./depending_ptr_inparam

$CC -std=c++11 -g -o depending_ptr_outreturn depending_ptr_outreturn.cpp -lpthread &&
	./depending_ptr_outreturn

$CC -std=c++11 -g -o depending_ptr_inout depending_ptr_inout.cpp -lpthread &&
	./depending_ptr_inout

$CC -std=c++11 -g -o depending_ptr_fanout depending_ptr_fanout.cpp -lpthread &&
	./depending_ptr_fanout

$CC -std=c++11 -g -o depending_ptr_fanin depending_ptr_fanin.cpp -lpthread &&
	./depending_ptr_fanin

$CC -std=c++11 -g -o depending_ptr_faninout depending_ptr_faninout.cpp -lpthread &&
	./depending_ptr_faninout

$CC -std=c++11 -g -o depending_ptr_condcomp depending_ptr_condcomp.cpp -lpthread &&
	./depending_ptr_condcomp
$CC -std=c++11 -g -DFOO -o depending_ptr_condcomp depending_ptr_condcomp.cpp -lpthread &&
	./depending_ptr_condcomp

$CC -std=c++11 -g -o depending_ptr_handoff depending_ptr_handoff.cpp -lpthread &&
	./depending_ptr_handoff
