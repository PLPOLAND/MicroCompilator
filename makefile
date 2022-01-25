compile:
	cd ./src; g++ -c main.cpp Scanner.cpp Symbol.cpp Parser.cpp ParserErr.cpp ParseException.cpp ; g++ -o ../parser main.o Scanner.o Symbol.o Parser.o ParserErr.o ParseException.o
clean:
	rm -f src/*.o

distclean: clean
	rm -f $(OBJFile)