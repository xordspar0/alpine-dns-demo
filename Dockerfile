FROM alpine:3.12 AS build

RUN apk add make gcc libc-dev

COPY Makefile getaddrinfo.c /src/

WORKDIR /src/
RUN make

FROM alpine:3.12 AS test

COPY --from=build /src/getaddrinfo /usr/local/bin/getaddrinfo

RUN getaddrinfo google.com
