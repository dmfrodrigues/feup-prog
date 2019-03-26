#!/bin/bash
set -e
echo 'Create ./linux/obj/, remove all content'
mkdir -p linux/obj
rm -rf ./linux/obj/*
echo 'Creating .o files...'
for filename in src/*.cpp; do
    echo -e '======> '$filename
    g++ -std=c++11 -c $filename -o ./linux/obj/${filename:4:-4}.o -I./include/
done
echo 'Done'
echo 'Create ./bin/'
mkdir -p linux/bin
echo 'Link .o files...'
cd linux/obj
g++ -o ../bin/main.app *.o
echo 'Done'
cd ../bin
./main.app
