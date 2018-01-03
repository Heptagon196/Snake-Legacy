@echo off
echo Building a release version
echo [1/4] Compiling ./main.cpp
g++ -c --std=c++11 -Dwindows -O2 ./main.cpp -o ./main.o
echo [2/4] Compiling ./Snake.cpp
g++ -c --std=c++11 -Dwindows -O2 ./Snake.cpp -o ./Snake.o
echo [3/4] Compiling ./Conio.cpp
g++ -c --std=c++11 -Dwindows -O2 ./Conio.cpp -o ./Conio.o
echo [4/4] Building snake
g++ --std=c++11 -Dwindows -O2 ./main.o ./Snake.o ./Conio.o -o snake
