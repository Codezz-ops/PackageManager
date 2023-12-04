BINARY_NAME=gpm

all: build

build:
	go build -o bin/$(BINARY_NAME) cmd/main.go

clean:
	rm -rf bin/