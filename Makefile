.SILENT:
FLAG = --std=c++11 -Dlinux
CPP = g++
DEPENDENCIES = ./Menu.o ./main.o ./Conio.o ./Snake.o
ifdef MAKE_RELEASE
	FLAG += -O2
endif
ifdef MAKE_DEBUG
	FLAG += -DDEBUG -g
endif
ifdef MAKE_STATIC
	FLAG += -static
endif

default:
	make release

snake: $(DEPENDENCIES)
	 echo "[5/5] Building snake"
	$(CPP) $(DEPENDENCIES) $(FLAG) -o snake

./Menu.o: ./Menu.cpp
	echo "[1/5] Compiling ./Menu.cpp"
	$(CPP) -c $(FLAG) $< -o ./Menu.o
./main.o: ./main.cpp
	echo "[2/5] Compiling ./main.cpp"
	$(CPP) -c $(FLAG) $< -o ./main.o
./Conio.o: ./Conio.cpp
	echo "[3/5] Compiling ./Conio.cpp"
	$(CPP) -c $(FLAG) $< -o ./Conio.o
./Snake.o: ./Snake.cpp
	echo "[4/5] Compiling ./Snake.cpp"
	$(CPP) -c $(FLAG) $< -o ./Snake.o

clean:
	echo "Cleaning files"
	rm -rf ./Menu.o ./main.o ./Conio.o ./Snake.o
install:
	echo "Installing snake to /usr/local/bin"
	cp ./snake /usr/local/bin/
debug:
	echo "Building a debug version"
	env MAKE_DEBUG=true make snake
static:
	echo "Building a statically linked version"
	env MAKE_STATIC=true make snake
release:
	echo "Building a release version"
	env MAKE_RELEASE=true make snake
