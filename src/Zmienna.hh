#ifndef ZMIENNA_H
#define ZMIENNA_H
	
#include <string>


class Zmienna  
{
	private:
		std::string ID;
		///typ zeminnej (true = real; false = integer)
		bool typ  = false;	
		int valI = 0;
		float valF = 0.f;
		bool number = false;
	public:

		Zmienna(std::string nazwa);
		~Zmienna();
		std::string getDeclaration();

		void setID(std::string);
		void setType(bool type);
		std::string getID();
		bool getType();

		void setVal(int val);
		void setVal(float val);
		std::string getVal();

		bool isNumber();
};
#endif