all:
	gcc -o trainer main.c cardhelper.c cardhelper.h csvmanager.c csvmanager.h
debug:
	gcc -g -o trainer main.c cardhelper.c cardhelper.h csvmanager.c csvmanager.h
clean:
	rm trainer