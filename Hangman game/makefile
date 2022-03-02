build_debug: bin\Debug\hangman.exe
build_release: bin\Release\hangman.exe

bin\Debug\hangman.exe:\
      obj\Debug\main.o                obj\Debug\hangman.o\
      obj\Debug\IO.o                  obj\Debug\consolemanip.o\
      obj\Debug\assets.o
	g++ -o bin\Debug\hangman.exe\
    obj\Debug\main.o                obj\Debug\hangman.o\
    obj\Debug\IO.o                  obj\Debug\consolemanip.o\
		obj\Debug\assets.o

bin\Release\hangman.exe:\
      obj\Release\main.o              obj\Release\hangman.o\
      obj\Release\IO.o                obj\Release\consolemanip.o\
      obj\Release\assets.o
	g++ -o bin\Release\hangman.exe\
    obj\Release\main.o              obj\Release\hangman.o\
    obj\Release\IO.o                obj\Release\consolemanip.o\
		obj\Release\assets.o


obj\Debug\main.o: source\main.cpp source\hangman.h
	g++ -c -g -std=c++17 -Wall source\main.cpp -o obj\Debug\main.o

obj\Debug\hangman.o: source\hangman.cpp source\hangman.h source\IO.h source\assets.h
	g++ -c -g -std=c++17 -Wall source\hangman.cpp -o obj\Debug\hangman.o

obj\Debug\IO.o: source\IO.cpp source\IO.h source\consolemanip.h
	g++ -c -g -std=c++17 -Wall source\IO.cpp -o obj\Debug\IO.o

obj\Debug\consolemanip.o: source\consolemanip.cpp source\consolemanip.h
	g++ -c -g -std=c++17 -Wall source\consolemanip.cpp -o obj\Debug\consolemanip.o

obj\Debug\assets.o: source\assets.cpp source\assets.h
	g++ -c -g -std=c++17 -Wall source\assets.cpp -o obj\Debug\assets.o


obj\Release\main.o: source\main.cpp source\hangman.h
	g++ -c -O2 -std=c++17 -Wall source\main.cpp -o obj\Release\main.o

obj\Release\hangman.o: source\hangman.cpp source\hangman.h source\IO.h source\assets.h
	g++ -c -O2 -std=c++17 -Wall source\hangman.cpp -o obj\Release\hangman.o

obj\Release\IO.o: source\IO.cpp source\IO.h source\consolemanip.h
	g++ -c -O2 -std=c++17 -Wall source\IO.cpp -o obj\Release\IO.o

obj\Release\consolemanip.o: source\consolemanip.cpp source\consolemanip.h
	g++ -c -O2 -std=c++17 -Wall source\consolemanip.cpp -o obj\Release\consolemanip.o
	
obj\Release\assets.o: source\assets.cpp source\assets.h
	g++ -c -O2 -std=c++17 -Wall source\assets.cpp -o obj\Release\assets.o


source\main.cpp:
source\hangman.cpp:
source\IO.cpp:
source\consolemanip.cpp:
source\assets.cpp:

source\hangman.h:
source\IO.h:
source\consolemanip.h:
source\assets.h: