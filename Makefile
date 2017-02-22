.PHONY: all, build, install, uninstall, clean, get-deps, get-deps-lumberjackd, get-deps-timberd, get-deps-lumberjackd-build-deps, get-deps-lumberjackd-libuv, get-deps-lumberjackd-wt, get-deps-lumberjackd-bson, get-deps-lumberjackd-raft

PKG_MGR := apt-get

all: get-deps build

build: build-lumberjackd

build-lumberjackd:
	cp -r ./lumberjackd/vendor/ /usr/local/include/ && \
	mkdir ./build/ && \
	cp -r ./cmd/lumberjackd/ ./build/ && \
	cp -r ./lumberjackd/src/ ./build/ && \
	mkdir ./dist/ && \
	ls ./build/ && \
	g++ -std=c++14 -pthread -c ./build/vectored.cpp -o vectored.o && \
	g++ -std=c++14 -pthread -o ./dist/lumberjackd ./build/main.cpp && \
	rm -rf ./build/

install:
	# TODO

uinstall:
	# TODO

clean:
	# TODO

get-deps: get-deps-lumberjackd get-deps-timberd

get-deps-lumberjackd: get-deps-lumberjackd-build-deps get-deps-lumberjackd-libuv get-deps-lumberjackd-wt get-deps-lumberjackd-bson get-deps-lumberjackd-raft

get-deps-lumberjackd-build-deps:
	${PKG_MGR} install -y automake libtool cmake libmongoc-1.0-0

get-deps-lumberjackd-libuv:
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
	make install && \
	cd / && \
	rm -rf /tmp/libuv.tar.gz /tmp/libuv.tar.gz.sign /tmp/libuv-v1.9.1/

get-deps-lumberjackd-wt:
	curl -L -o /tmp/wiredtiger.tar.gz https://github.com/wiredtiger/wiredtiger/archive/2.9.1.tar.gz && \
	cd /tmp/ && \
	tar xzvf wiredtiger.tar.gz && \
	cd wiredtiger-2.9.1/ && \
	sh autogen.sh && \
	./configure && \
	make && \
	make install && \
	cd / && \
	rm -rf /tmp/wiredtiger.tar.gz /tmp/wiredtiger-2.9.1

get-deps-lumberjackd-bson:
	curl -L -o /tmp/libbson.tar.gz https://github.com/mongodb/libbson/archive/1.6.0.tar.gz && \
	cd /tmp && \
	tar xzvf libbson.tar.gz && \
	cd libbson-1.6.0/ && \
	sh autogen.sh && \
	./configure && \
	make && \
	make install && \
	cd / && \
	rm -rf /tmp/libbson.tar.gz /tmp/libbson-1.6.0/ && \
	curl -L -o /tmp/bson.tar.gz https://github.com/mongodb/mongo-cxx-driver/archive/r3.1.1.tar.gz && \
	cd /tmp && \
	tar xzvf bson.tar.gz && \
	cd mongo-cxx-driver-r3.1.1/build && \
	cmake -DCMAKE_BUILD_TYPE=Release -DBSONCXX_POLY_USE_BOOST=1 \
	    -DCMAKE_INSTALL_PREFIX=/usr/local ..

get-deps-lumberjackd-raft:
	curl -L -o /tmp/kudu.tar.gz https://github.com/apache/kudu/archive/1.2.0.tar.gz && \
	cd /tmp && \
	tar xzvf kudu.tar.gz && \
	cd kudu-1.2.0/ && \
	mkdir -p build/debug && \
	cd build/debug && \
	cmake ../.. && \
	make -j8

get-deps-timberd:
	if [ -z `which glide` ]; then \
		curl https://glide.sh/get | sh; \
	fi

