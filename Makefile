.PHONY: get-deps build install uninstall clean

all: build

build: get-deps
	mkdir -p dist/
	go build -o dist/lumberjack cmd/lumberjack/main.go
	go build -o dist/lumberjackd cmd/lumberjackd/main.go
	go build -o dist/timberd cmd/timberd/main.go

get-deps:
	if [ -z `which glide` ]; then \
		curl https://glide.sh/get | sh \
	fi
	glide install

install:

uninstall:

clean:

