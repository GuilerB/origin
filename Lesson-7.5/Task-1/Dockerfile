FROM ubuntu:16.04
RUN apt-get update && apt-get install -y g++ nano

# Копируем исходный файл в контейнер
COPY Test.cpp /app/Test.cpp

WORKDIR /app
RUN g++ -o Test Test.cpp

CMD ["./Test"]