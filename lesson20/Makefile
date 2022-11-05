CC=g++
FLAGS=-std=c++11 -lpthread
Src=server.cc 
Target=server 

$(Target):$(Src)
	$(CC) -o $@ $^ $(FLAGS)

.PHONY:clean
clean:
	rm -rf $(Target)


