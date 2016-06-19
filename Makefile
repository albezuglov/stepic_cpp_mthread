all: exe

exe: test.cpp
	gcc -fPIC test.cpp -o shell
	
clean:
	-rm shell 2>/dev/null