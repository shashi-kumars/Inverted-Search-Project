OBJ = $(patsubst %.c, %.o, $(wildcard *.c))
result.out : $(OBJ)
	gcc -o $@ $^
clean: 
	rm *.o *.out

