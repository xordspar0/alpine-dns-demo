FROM alpine:3.12 AS build

RUN apk add make gcc libc-dev

COPY Makefile host.c /src/

WORKDIR /src/
RUN make

FROM alpine:3.12 AS test

COPY --from=build /src/host /usr/local/bin/host

RUN host google.com
