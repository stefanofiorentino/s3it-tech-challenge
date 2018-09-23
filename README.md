[![Build Status](https://travis-ci.org/stefanofiorentino/s3it-tech-challenge.svg?branch=master)](https://travis-ci.org/stefanofiorentino/s3it-tech-challenge)

## Introduction
This project, based on libtiff and lodePNG is a Modern C++ software solution to the tech challenge at S3IT.

Problem specification can be found in the specs/DESCRIPTION.pdf

Input data samples can be found in the data/images folder.

Helper data samples can be found in the data/images/cells-mask folder.

Output data sample (to test against your very results) can be found in test/expected_results folder.

If you just want to give the software a try, just enter the commands in "Build instruction".

If you are wondering how to give command line arguments to the program, just enter 
> ./s3it-tech-challenge --help
  
## Architecture
The software is mainly based on two lib-wrapper written in Modern C++.
The first lib is a wrapper of libtiff http://www.libtiff.org/ and the API exposes a couple of interfaces which leverage modern data structure (avoiding opaque void pointers).
The second lib is a tiny wrapper to the lodePNG https://www.lodev.org/lodepng/ lib.

## Build instruction

    user (master) $> git clone https://github.com/stefanofiorentino/s3it-tech-challenge 

    user (master) $> cd s3it-tech-challenge 

    user (master) $> git submodule update --init --recursive

    user (master) $> rm -rf ./build/*

    user (master) $> mkdir -p build && cd build

    user (master) $> cmake ..

    user (master) $> make s3it-tech-challenge

    user (master) $> ./s3it-tech-challenge


# Mac OS users
After installing the dependencies as brew recipe, the software is fully compatible with Mac OS X command line terminal.

# Windows users (under review)
The windows user should be able to build in Visual Studio just by installing dependencies with NuGET and producing the solution file with 
> cmake -G "Visual Studio 11 2012" ../