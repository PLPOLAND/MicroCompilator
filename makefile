compile:
	cd ./src; g++ -c main.cpp Scanner.cpp Symbol.cpp; g++ -o ../scanner main.o Scanner.o Symbol.o
clean:
	rm -f src/*.o

distclean: clean
	rm -f $(OBJFile)