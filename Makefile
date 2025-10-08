# Makefile pour le projet Puissance 4

# Compilateur
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Nom de l'exécutable
TARGET = game

# Sources et objets
SRCS = main.cpp board.cpp neurone.cpp network.cpp networkOperation.cpp trainer.cpp
OBJS = $(SRCS:.cpp=.o)

# Règle par défaut
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation des fichiers .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild complet
rebuild: clean all

# Exécuter le jeu
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean rebuild run