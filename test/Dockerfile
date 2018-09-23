FROM ubuntu:18.04

RUN apt-get update
RUN apt-get install -y cmake
RUN apt-get install -y git
RUN apt-get install -y build-essential gcc python2.7-dev libtiff-dev libboost-all-dev
RUN git clone https://github.com/stefanofiorentino/s3it-tech-challenge
RUN cd s3it-tech-challenge \
    && git submodule update --init --recursive
RUN cd s3it-tech-challenge/test/libs/Catch2 \
    && rm -rf ./build \
    && mkdir -p build \
    && cd build \
    && cmake .. \
    && make \
    && make install
RUN cd s3it-tech-challenge \
    && rm -rf ./build \
    && mkdir -p build \
    && cd build \
    && cmake .. \
    && make
RUN cd s3it-tech-challenge/build \
    && ./s3it-tech-challenge \
    && cd test \
    && ./s3it-tech-challenge-tester


