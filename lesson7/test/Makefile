mytest:test.o
	gcc -o mytest test.o
test.o:test.s
	gcc -c test.s -o test.o
test.s:test.i
	gcc -S test.i -o test.s
test.i:test.c 
	gcc -E test.c -o test.i
.PHONY:clean 
clean:
	rm -f test.i test.s test.o mytest 
