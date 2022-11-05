.PHONY:all
all:mykill myproc

myproc:test.c
	gcc -o $@ $^

mykill:mykill.c
	gcc -o $@ $^


.PHONY:clean
clean:
	rm myproc mykill -f
