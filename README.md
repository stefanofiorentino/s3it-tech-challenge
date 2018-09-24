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

## Output
The outputs can be found in the build folder. 

The results of the contest points 1, 2, 3 are respectively 1_output.png, 2_output.png and 3_output.csv.

A convenient -o,--output_dir utility flag is under development.

## Mac OS users
After installing the dependencies as brew recipe, the software is fully compatible with Mac OS X command line terminal.

## Windows users (under review)
The windows user should be able to build in Visual Studio just by installing dependencies with NuGET and producing the solution file with 
> cmake -G "Visual Studio 11 2012" ../

## Docker 
Are you onto a Mac or Windows machine and haven't experience with cmake? Inside the test folder you'll find a convenient Dockerfile you can build the product just entering in the commandline
> cd test

> docker build -t s3it-tech-challenge .

## Software APIs
A fully portable API structure is under investigation. 

A SWIG based interface is created in order to port the libraries to Java, Node.js and Python.

The example can be found in the file
> src/solutions/calculate_channel_mean/swig/calculate_channel_mean.i

Working in this way, every ported version of the library is based on the same C++ codebase, so clients and developers can refer to a single reference documentation, jira dashboard, continuous integration report and git issues repository. 

## Restful web APIs
A restful API structure is under investigation. 

A C++ web server (based on www.github.com/ipkn/crow) can be exposed to public (customers) without the effort to ship working software as built executable.
Not shipping code normally reduces patent infringement risks and software upgrade difficulties. 

## Future needs
Ability to export in TIFF.

Ability to import in PNG.

Ability to overlay more than 3 images (not visually trivial).

Custom data structure shared among professionals at lab.

Public web APIs to enhance collaboration and contracts.
