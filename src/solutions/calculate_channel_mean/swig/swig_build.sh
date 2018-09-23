#!/usr/bin/env bash
mkdir -p python || exit 1
swig -python -c++ -outdir python -I../ calculate_channel_mean.i || exit 1

rm -rf build && mkdir -p build && cd build || exit 1
g++ -fpic -std=c++11 -x c++ -c ../../calculate_channel_mean.h ../calculate_channel_mean_wrap.cxx -I/usr/include/python2.7 || exit 1
g++ -shared calculate_channel_mean.o calculate_channel_mean_wrap.o -o ../_ExampleModule.so || exit 1
cd ../ || exit 1