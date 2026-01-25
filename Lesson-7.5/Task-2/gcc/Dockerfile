FROM gcc:latest

WORKDIR /app

COPY . .

RUN g++ -std=c++17 -O2 -o smartarray 5.3.1_SmartArray_v2.cpp

CMD ["./smartarray"]