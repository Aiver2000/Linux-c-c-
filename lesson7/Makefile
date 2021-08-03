mytest:main.o test.o
	gcc -o $@ $^
main.o:main.c
	gcc -c $<
test.o:test.c
	gcc -c $<
.PHONY:clean
clean:
	rm -f *.o mytest

