CFLAGS = -g -pedantic -Wall

getaddrinfo: getaddrinfo.c
	cc $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f getaddrinfo
	rm -rf *.dSYM
