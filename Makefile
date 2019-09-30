# Makefile pour TP1.
# Adaptez ce fichier au besoin (si vous ajouter des fichiers).
#
# Choisir l'une des deux configurations (-g: Debug | -O2: Release)
OPTIONS = -g -O0 -Wall
#OPTIONS = -O2 -Wall

all : tp1

tp1 : tp1.cpp point.o polygone.o empire.o
	g++ ${OPTIONS} -o tp1 tp1.cpp point.o polygone.o empire.o

point.o : point.cpp point.h
	g++ ${OPTIONS} -c point.cpp

polygone.o : polygone.cpp polygone.h point.h
	g++ ${OPTIONS} -c polygone.cpp

empire.o : empire.cpp polygone.h

clean:
	rm -rf tp1 *~ *.o

