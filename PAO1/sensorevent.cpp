#include "sensorevent.h"
#include "visitor_grafico.h"
#include "visitor_dati.h"

sensore_vent::sensore_vent(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c/*, const QString& p*/):sensore_aria(n,d,t,s,c/*,p*/){
    min = 1;
    max = 60;
    soglia = 35;
    vettore_direz = nullptr;
}


sensore_vent::sensore_vent(const sensore& copia):sensore_aria(copia){
    min = 1;
    max = 60;
    soglia = 35;
    vettore_direz = nullptr;
}

sensore_vent::~sensore_vent(){
    delete vettore_direz;
}


const QVector<double>* sensore_vent::getDirez() const{
    return vettore_direz;
}

//la chiamata a sensore_aria compila vettore_dati e vettore_trigger:
    //in vettore_trigger segna con true le posizioni in cui in vettore dati un valore va oltre la soglia;
//poi salva in vettore_direz le direzioni casuali medie del vento per ogni giorno
void sensore_vent::genera_dati(const int& n){
    sensore_aria::genera_dati(n);

    vettore_direz = new QVector<double>(n);
    for(int i=0;i<n;i++){
        (*vettore_direz)[i] = QRandomGenerator::global()->generateDouble()*(2*3.14);
    }
}


void sensore_vent::accept(visitor_grafico* visitor){
    visitor->visit(this);
}


void sensore_vent::accept(visitor_dati* visitor){
    visitor->visit(this);
}
