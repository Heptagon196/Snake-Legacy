@echo off
echo Building a release version
echo [1/5] Compiling ./Menu.cpp
g++ -c --std=c++11 -Dwindows -O2 ./Menu.cpp -o ./Menu.o
echo [2/5] Compiling ./main.cpp
g++ -c --std=c++11 -Dwindows -O2 ./main.cpp -o ./main.o
echo [3/5] Compiling ./Conio.cpp
g++ -c --std=c++11 -Dwindows -O2 ./Conio.cpp -o ./Conio.o
echo [4/5] Compiling ./Snake.cpp
g++ -c --std=c++11 -Dwindows -O2 ./Snake.cpp -o ./Snake.o
echo [5/5] Building snake
g++ --std=c++11 -Dwindows -O2 ./Menu.o ./main.o ./Conio.o ./Snake.o -o snake
