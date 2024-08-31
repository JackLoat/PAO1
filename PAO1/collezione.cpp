#include "collezione.h"
#include "sensori.h"

collezione::collezione(const QString& n,const QString& p):nome(n),path(p){}


collezione::~collezione(){
    for(auto sensore:lista_sensori){
        delete sensore;
    }
    lista_sensori.clear();
}


void collezione::add_sensore(sensore *s){
    lista_sensori.push_back(s);
}


void collezione::rm_sensore(sensore *s){
    lista_sensori.removeOne(s);
}

const QString& collezione::getNome() const{
    return nome;
}


const QString& collezione::getPath() const{
    return path;
}
