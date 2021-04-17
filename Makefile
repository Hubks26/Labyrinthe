CC = g++
EXEC = Labirynth
FLAGS = -Wall -Werror -pedantic
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
STD = -std=c++17
S = src
O = obj
B = bin

all: $(O) $(B) $(O)/Main.o
	$(CC) $(O)/*.o -o $(B)/$(EXEC) $(LIBS)

$(O)/Main.o: $(O)/Engine.o
	$(CC) $(S)/Main.cpp -c -o $(O)/Main.o $(STD) $(FLAGS)

$(O)/Engine.o: $(O)/Labirynth.o
	$(CC) $(S)/Engine.cpp -c -o $(O)/Engine.o $(STD) $(FLAGS)

$(O)/Labirynth.o: $(O)/ColorGenerator.o
	$(CC) $(S)/Labirynth.cpp -c -o $(O)/Labirynth.o $(STD) $(FLAGS)

$(O)/ColorGenerator.o:
	$(CC) $(S)/ColorGenerator.cpp -c -o $(O)/ColorGenerator.o $(STD) $(FLAGS)

clean: $(O) $(B)
	rm -r $(O)
	rm -r $(B)

$(O):
	mkdir $(O)

$(B):
	mkdir $(B)
