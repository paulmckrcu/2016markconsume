#!/bin/bash

set -e
set -u
set -x

CC=${CC:-g++}

$CC -std=c++11 -o test_depending_ptr test_depending_ptr.cpp pointer_cmp.cpp &&
	./test_depending_ptr
