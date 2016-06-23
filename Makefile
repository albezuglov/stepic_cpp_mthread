all: exe

exe: test.c
	c99 -fPIC test.c -o shell
	
clean:
	-rm shell 2>/dev/null