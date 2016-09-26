#!/bin/bash

set -e
set -u
set -x

CC=${CC:-g++}
CCFLAGS="-std=c++11 -g -Wall -Werror"

$CC $CCFLAGS -o depending_ptr_simple depending_ptr_simple.cpp -lpthread &&
	./depending_ptr_simple

$CC $CCFLAGS -o depending_ptr_inparam depending_ptr_inparam.cpp -lpthread &&
	./depending_ptr_inparam

$CC $CCFLAGS -o depending_ptr_outreturn depending_ptr_outreturn.cpp -lpthread &&
	./depending_ptr_outreturn

$CC $CCFLAGS -o depending_ptr_inout depending_ptr_inout.cpp -lpthread &&
	./depending_ptr_inout

$CC $CCFLAGS -o depending_ptr_fanout depending_ptr_fanout.cpp -lpthread &&
	./depending_ptr_fanout

$CC $CCFLAGS -o depending_ptr_fanin depending_ptr_fanin.cpp -lpthread &&
	./depending_ptr_fanin

$CC $CCFLAGS -o depending_ptr_faninout depending_ptr_faninout.cpp -lpthread &&
	./depending_ptr_faninout

$CC $CCFLAGS -o depending_ptr_condcomp depending_ptr_condcomp.cpp -lpthread &&
	./depending_ptr_condcomp
$CC $CCFLAGS -DFOO -o depending_ptr_condcomp depending_ptr_condcomp.cpp -lpthread &&
	./depending_ptr_condcomp

$CC $CCFLAGS -o depending_ptr_handoff depending_ptr_handoff.cpp -lpthread &&
	./depending_ptr_handoff
