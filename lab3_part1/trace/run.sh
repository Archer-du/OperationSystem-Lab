#! /bin/bash

TASKPATH=$PWD
MALLOCPATH=~/oslab/lab3/malloclab/
export LD_LIBRARY_PATH=$MALLOCPATH
cd $MALLOCPATH; make clean; make
cd $TASKPATH
g++ -g workload.cc -o workload -I$MALLOCPATH -L$MALLOCPATH -lmem -lpthread # -std=c++11
#./workload