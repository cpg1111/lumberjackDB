.PHONY: all, build, install, uninstall, clean, get-deps, get-deps-lumberjackd, get-deps-timberd

PKG_MGR := apt-get

all: get-deps build

build: build-lumberjackd

build-lumberjackd:
	cp -r ./lumberjackd/vendor/ /usr/local/include/
	mkdir ./build/
	cp -r ./cmd/lumberjackd/ ./build/
	cp -r ./lumberjackd/src/ ./build/
	mkdir ./dist/
	g++ -std=c++14 -pthread -c ./build/vectored.cpp -o vectored.o
	g++ -std=c++14 -pthread -o ./dist/lumberjackd ./build/main.cpp
	rm -rf ./build/

install:
	# TODO

uinstall:
	# TODO

clean:
	# TODO

get-deps: get-deps-lumberjackd get-deps-timberd

get-deps-lumberjackd:
	${PKG_MGR} install -y automake libtool
	gpg --keyserver pool.sks-keyservers.net --recv-keys AE9BC059
	curl -o /tmp/libuv.tar.gz.sign http://dist.libuv.org/dist/v1.9.1/libuv-v1.9.1.tar.gz.sign
	curl -o /tmp/libuv.tar.gz http://dist.libuv.org/dist/v1.9.1/libuv-v1.9.1.tar.gz && \
	gpg --verify /tmp/libuv.tar.gz.sign /tmp/libuv.tar.gz
	cd /tmp/ && \
	tar xzvf libuv.tar.gz && \
	cd libuv-v1.9.1/ && \
	sh autogen.sh && \
	./configure && \
	make && \
	make check && \
	make install
	curl -L -o /tmp/wiredtiger.tar.gz https://github.com/wiredtiger/wiredtiger/archive/2.9.1.tar.gz && \
	cd /tmp/ && \
	tar xzvf wiredtiger.tar.gz
	cd wiredtiger-2.9.1/ && \
	sh autogen.sh && \
	./configure && \
	make && \
	make install

get-deps-timberd:
	if [ -z `which glide` ]; then \
		curl https://glide.sh/get | sh; \
	fi

