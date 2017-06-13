.PHONY:all
all:server client
server:server.c comm.h comm.c
	gcc -o $@ $^
client:client.c comm.h comm.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -f server client
