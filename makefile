compile:
	cd ./src; g++ -c main.cpp Scanner.cpp Symbol.cpp Parser.cpp ParserErr.cpp ParseException.cpp InterCodeGenerator.cpp Variable.cpp ; g++ -o ../translator main.o Scanner.o Symbol.o Parser.o ParserErr.o ParseException.o InterCodeGenerator.o Variable.o
clean:
	rm -f src/*.o

distclean: clean
	rm -f $(OBJFile)