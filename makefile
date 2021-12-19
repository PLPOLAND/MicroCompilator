compile:
	cd ./src; g++ -c main.cpp Scanner.cpp Symbol.cpp Parser.cpp ; g++ -o ../parser main.o Scanner.o Symbol.o Parser.o
clean:
	rm -f src/*.o

distclean: clean
	rm -f $(OBJFile)