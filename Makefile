.SILENT:
FLAG = --std=c++11 -Dlinux
CPP = g++
DEPENDENCIES = ./main.o ./Snake.o ./Conio.o
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
	echo "[4/4] Building snake"
	$(CPP) $(DEPENDENCIES) $(FLAG) -o snake

./main.o: ./main.cpp
	echo "[1/4] Compiling ./main.cpp"
	$(CPP) -c $(FLAG) $< -o ./main.o
./Snake.o: ./Snake.cpp
	echo "[2/4] Compiling ./Snake.cpp"
	$(CPP) -c $(FLAG) $< -o ./Snake.o
./Conio.o: ./Conio.cpp
	echo "[3/4] Compiling ./Conio.cpp"
	$(CPP) -c $(FLAG) $< -o ./Conio.o

clean:
	echo "Cleaning files"
	rm -rf ./main.o ./Snake.o ./Conio.o
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
