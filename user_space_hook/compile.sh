#!/bin/sh
gcc -shared -fPIC -o my_malloc.so my_malloc.c -ldl
