CFLAGS = -g -pedantic -Wall

host: host.c
	cc $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f host
	rm -rf *.dSYM
