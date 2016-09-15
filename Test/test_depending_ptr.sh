#!/bin/bash

set -e
set -u
set -x

CC=${CC:-g++}
CCFLAGS="-std=c++11 -g -Wall -Werror"

$CC $CCFLAGS -o test_depending_ptr test_depending_ptr.cpp pointer_cmp.cpp &&
	./test_depending_ptr
