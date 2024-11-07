# Target executable name
program: main.o drive.o list.o
	gcc main.o drive.o list.o -o program

# Individual compilation commands
main.o: main.c drive.h list.h node.h
	gcc -c main.c

drive.o: drive.c drive.h list.h node.h
	gcc -c drive.c

list.o: list.c list.h node.h
	gcc -c list.c

# Clean up build files
clean:
	del /Q main.o drive.o list.o program
