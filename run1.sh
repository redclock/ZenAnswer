#!/bin/bash

compile(){
    g++ 1compass.cpp -std=c++11 -o 1.exe
}

run() {
    echo -----------------------------
    echo == Input:
    echo -e $1
    echo == Output:
    echo -e $1"\n"$2 | ./1.exe
}

compile \
&& run "AB2 BC4 CD8 DA8 DE26 AD15 CE2 EB3 FA7\nB->A->E" \
&& run "AB2 BC1 CD3 DA4 DE2 AD8 CE2\nA->D->E" \
&& run "AB2 BC1 CD3 DA8 DE2 AD8 CE2\nA->A" \
&& run "AB2 BC1 CD3 DA8 DE2 AD8 CE2\nA->D->A" \
&& run "AB2 BC1 CD3 DA8 AD8 EF3\nA->D->F" \
&& run "AB2 BC1 CD3 DA8\nA->D->S" \
