#include "sensorefumo.h"
#include "visitor_grafico.h"
#include "visitor_dati.h"

sensore_fumo::sensore_fumo(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c/*, const QString& p*/):sensore(n,d,t,s,c/*,p*/){
    vettore_trigger = nullptr;
}

sensore_fumo::sensore_fumo(const sensore& copia):sensore(copia){
    vettore_trigger = nullptr;
}

sensore_fumo::~sensore_fumo(){
    delete vettore_trigger;
}

const QVector<bool>* sensore_fumo::getTrigger() const{
    return vettore_trigger;
}

//salva in vettore_trigger un vettore di n bool distribuiti casualmente
void sensore_fumo::genera_dati(const int &n){
    vettore_trigger = new QVector<bool>(n);
    for(int i=0; i<n; ++i){
        (*vettore_trigger)[i] = (QRandomGenerator::global()->bounded(0,2)==1);
    }
}

void sensore_fumo::accept(visitor_grafico* visitor){
    visitor->visit(this);
}

void sensore_fumo::accept(visitor_dati* visitor){
    visitor->visit(this);
}
