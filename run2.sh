#!/bin/bash
compile(){
    g++ 2pilot.cpp -std=c++11 -o 2.exe
}

run() {
    echo -----------------------------
    echo == Input:
    echo -e $1
    echo == Output:
    echo -e $1 | ./2.exe
}

compile \
&& run "20,20\n0,0,N\nMMMMRMMMRMMMRLMMMR\n0,5,S\nMMLRLMRMM" \
&& run "20,20\n0,0,N\nMMMMRMMMRMMMRLMMMR\n10,5,S\nMMMMMLRMRMM" \
&& run "20,20\n10,10,E\nMMMMBBBB\n10,5,W\nMMBBBBB" \
