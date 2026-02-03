CC = gcc
CFLAGS = -Wall -I./src

all: server

server:
	$(CC) $(CFLAGS) -o server src/server.c src/utils.c

test:
	$(CC) $(CFLAGS) -o test_runner tests/test_utils.c src/utils.c
	./test_runner

clean:
	rm -f server test_runner

release:
	@if [ -z "$(VERSION)" ]; then echo "VERSION is not set. Usage: make release VERSION=v1.0.0"; exit 1; fi
	git tag -a $(VERSION) -m "Release $(VERSION)"
	git push origin $(VERSION)

