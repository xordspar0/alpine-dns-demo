#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

#define EX_OK 0
#define EX_USAGE 64
#define EX_NOHOST 68
#define EX_SOFTWARE 70

void usage()
{
	fputs("usage: getaddrinfo hostname\n"
	      "\n"
	      "getaddrinfo is a tool for doing DNS lookups. It uses the POSIX\n"
	      "standard getaddrinfo(3) interface. Give a hostname as an argument\n"
	      "and getaddrinfo will respond with the IP addresses it maps to.\n",
	      stderr);
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		usage();
		return EX_USAGE;
	}

	struct addrinfo *addrs;
	int err = getaddrinfo(argv[1], NULL, NULL, &addrs);
	switch (err) {
	case 0:
		break;
	case EAI_NONAME:
		fprintf(stderr, "Host not found: %s\n", argv[1]);
		return EX_NOHOST;
		break;
	default:
		fprintf(stderr, "%s\n", gai_strerror(err));
		return EX_SOFTWARE;
	}

	for (struct addrinfo * addr = addrs; addr != NULL; addr = addr->ai_next) {
		char ip_address[128] = "";

		int err = getnameinfo(addr->ai_addr, addr->ai_addrlen,
				      ip_address, sizeof ip_address,
				      NULL, 0,
				      NI_NUMERICHOST);
		if (err != 0) {
			fprintf(stderr, "%s\n", gai_strerror(err));
			return EX_SOFTWARE;
		}

		puts(ip_address);
	}

	freeaddrinfo(addrs);

	return EX_OK;
}
