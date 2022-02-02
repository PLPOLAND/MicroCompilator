#include "Zmienna.hh"  
	
Zmienna::Zmienna(std::string nazwa)
{
    this->ID = nazwa;
}
	
Zmienna::~Zmienna()
{
	
}

void Zmienna::setID(std::string id){
    this->ID = id;
}
void Zmienna::setType(bool type){
    this->typ = type;
}
std::string Zmienna::getID(){
    return this->ID;
}
bool Zmienna::getType(){
    return this->typ;
}
std::string Zmienna::getDeclaration(){
    std::string tmp = "";
    tmp += !this->getType() ? "integer" : "real";
    tmp += " ";
    tmp += this->getID();
    return tmp;
}

void Zmienna::setVal(int val){
    if (!typ)
    {
        this->valI = val;
        this->number = true;
    }
    else
        throw new std::exception();
}
void Zmienna::setVal(float val){
    if (typ)
    {
        this->valF = val;
        this->number = true;
    }
    else
        throw new std::exception();
}
std::string Zmienna::getVal(){
    if (typ)
    {
        return std::to_string(valF);
    }
    else{
        return std::to_string(valI);
    }
    
}

bool Zmienna::isNumber(){
    return number;
}