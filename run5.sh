#!/bin/bash
compile(){
    g++ 5soil.cpp -std=c++11 -o 5.exe
}

run() {
    echo -----------------------------
    echo == Input:
    echo -e $1
    echo == Output:
    echo -e $1 | ./5.exe
}

compile \
&& run "A=1\nBx=2\nC=3\nA2BxC" \
&& run "A=1\nBx=2\nC=3\n(A2Bx)10C" \
&& run "A=1\nBx=2\nC=3\n(A2B)10C" \
&& run "A=1\nBx=2\nC=3\n(12A2B)10C" \
&& run "H = 1.00794\nC = 12.011\nN = 14.00674\nO = 15.9994\nFe = 55.845\nH2O\nCH3(CH2)16CH3\nFe3[Fe(CN)6]2\n" \
