FROM ubuntu:16.04

RUN apt-get update
RUN apt-get -y install libosmium2-dev make g++
COPY changeset2tsv.cpp /root
COPY Makefile /root

WORKDIR root 
RUN make 

