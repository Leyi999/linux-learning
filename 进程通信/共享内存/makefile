.PHONY: all
all: server client
client: ipc_client.cxx
	g++ $^ -o $@ -std=c++11
server: ipc_server.cxx
	g++ $^ -o $@ -std=c++11
.PHONY: clean
clean: 
	rm -f client server