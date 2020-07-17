#!/bin/sh

echo "clean build dir"
rm -rf build

echo "generate makefile"
mkdir build
cd build

if [ $# -lt 1 ];
then
    echo "Missing parameter: ./build.sh 0~1, 0(debug), 1(release)"
    exit
fi

if [ $1 -eq 0 ]
then
    #build debug
    echo "build debug..."
    cmake  -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles" ../
else
    #build release
    echo "build release..."
    cmake  -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles" ../
fi

echo "build starting ..."
echo "build thread:$(nproc)"
make all -j$(nproc)
echo "build finished!"

if [ $1 -eq 0 ]
then
    echo "debug bin&lib"
    rm -rf ../debug/*
else
    echo "release bin&lib"
    rm -rf ../release/*
fi

make install

cd -

