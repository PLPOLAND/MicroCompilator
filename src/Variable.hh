#ifndef ZMIENNA_H
#define ZMIENNA_H
	
#include <string>
#include <vector>

/**
 * @brief Klasa przechowująca informacje o zmiennej.
 * 
 */
class Variable  
{
	private:
		std::string ID;
		///typ zeminnej (true = real; false = integer)
		bool typ  = false;	
	public:

		Variable(std::string nazwa);
		~Variable();
		std::string getDeclaration();
		///setter
		void setID(std::string);
		///setter
		void setType(bool type);
		///getter
		std::string getID();
		///getter
		bool getType();

		/**
		 * @brief Znajduje zmienną w podanym kontenerze, według podanego id. Jeśli nie znajdzie odpowiedniej zmiennej zwraca nullptr
		 * 
		 * @param zmienne kontener z zmiennymi
		 * @param id id poszukiwanej zmiennej
		 * @return Zmienna* - wskaźnik na znalezioną zmienną
		 * @return nullptr - jeśli nie znaleziono zmiennej
		 */
		static Variable * findZmiennaOfId(std::vector<Variable*>* zmienne, std::string id);
};
#endif