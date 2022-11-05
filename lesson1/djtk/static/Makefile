mylib=libcal.a
CC=gcc 

$(mylib):add.o sub.o
	ar -rc $(mylib) $^ 
%.o:%.c
	$(CC) -c $<

.PHONY:clean
clean:
		rm -f $(mylib) *.o 
.PHONY:output
output:
		mkdir -p mathlib/lib
		mkdir -p mathlib/include
		cp *.h mathlib/include
		cp *.a mathlib/lib
