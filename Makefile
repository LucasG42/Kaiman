TARGET=main
CC=g++
OBJS= main.o Person.o Date.o

all: build clean

build: $(OBJS)
	@echo "Compilando arquivos..."
	@$(CC) -o $(TARGET) $(OBJS)
 
main.o: main.cpp
	@$(CC) -c main.cpp -o main.o
 
Person.o: modules/DAO/sources/Person.cpp
	@$(CC) -c modules/DAO/sources/Person.cpp  -o Person.o
 
Date.o: main.cpp
	@$(CC) -c modules/DAO/sources/Date.cpp -o Date.o

clean:
	@echo "Limpando..."
	@rm -f *.o
