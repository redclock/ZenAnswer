#!/bin/bash
compile(){
    g++ 4neo.cpp -std=c++11 -o 4.exe
}

run() {
    echo -----------------------------
    echo == Input:
    echo -e $1
    echo == Output:
    echo -e $1 | ./4.exe
}

compile \
&& run "A->B\nB->C\nA->C\nD->C" \
&& run "A->B\nB->C\nC->A\nD->C" \
&& run "戴眼镜 -> 刷牙\n戴眼镜 -> 洗脸\n戴眼镜 -> 穿t恤\n穿袜子 -> 穿鞋\n穿t恤 -> 穿外套\n穿裤子 -> 穿袜子\n穿裤子 -> 穿鞋\n刷牙  -> 洗脸\n刷牙  -> 吃早饭\n" \