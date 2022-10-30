FROM debian

WORKDIR /app

RUN apt-get update
RUN apt-get -y install clang
RUN apt-get -y install libboost-all-dev

COPY crow.deb crow.deb
RUN dpkg -i crow.deb

COPY src src

RUN clang++ -o main -std=c++17 -lpthread src/main.cpp src/game/*.cpp

CMD ["./main"]
EXPOSE 4000
