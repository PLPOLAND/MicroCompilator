#include "Variable.hh"  
	
Variable::Variable(std::string nazwa)
{
    this->ID = nazwa;
}
	
Variable::~Variable()
{
	
}

void Variable::setID(std::string id){
    this->ID = id;
}
void Variable::setType(bool type){
    this->typ = type;
}
std::string Variable::getID(){
    return this->ID;
}
bool Variable::getType(){
    return this->typ;
}
std::string Variable::getDeclaration(){
    std::string tmp = "";
    tmp += !this->getType() ? "integer" : "real";
    tmp += " ";
    tmp += this->getID();
    return tmp;
}

Variable *Variable::findZmiennaOfId(std::vector<Variable *> *zmienne, std::string id)
{
    for (auto zmienna : *zmienne)
    {
        if (zmienna->getID() == id)
        {
            return zmienna;
        }
    }
    return nullptr;
}