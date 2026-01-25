FROM ubuntu:24.04

RUN apt-get update && \
    apt-get install -y clang cmake make git && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN clang++ -std=c++20 -O2 -Wall -o smart_array_clang 5.3.1_SmartArray_v2.cpp

CMD ["./smart_array_clang"]