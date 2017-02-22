FROM golang:1.8-stretch
COPY . /opt/src/
WORKDIR /opt/src/
RUN apt-get update && apt-get install -y curl build-essential
ENTRYPOINT ["make"]
