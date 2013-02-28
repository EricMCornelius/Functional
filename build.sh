#!/bin/bash -x

mkdir -p bin
g++ -std=c++11 src/example.cpp -Iinclude -o bin/example.tsk
