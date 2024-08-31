#include "sensorearia.h"
#include "visitor_dati.h"
#include "visitor_grafico.h"

sensore_aria::sensore_aria(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c/*, const QString& p*/):sensore_temp(n,d,t,s,c/*,p*/){
    soglia=50;
    min=0;
    max=150;
    vettore_trigger = nullptr;
}


sensore_aria::sensore_aria(const sensore& copia):sensore_temp(copia){
    soglia = 50;
    min = 0;
    max = 150;
    vettore_trigger = nullptr;
}

sensore_aria::~sensore_aria(){
    delete vettore_trigger;
}


const QVector<bool>* sensore_aria::getTrigger() const{
    return vettore_trigger;
}

const double& sensore_aria::getSoglia() const{
    return soglia;
}


void sensore_aria::setSoglia(const double& s){
    soglia = s;
}

//la chiamata a sensore_temp(genera_dati) salva in vettore_dati n double casuali tra max e min,
//poi salva in vettore_trigger tutti gli indici di vettore_dati in cui vettore_dati[i]>s
void sensore_aria::genera_dati(const int &n){
    sensore_temp::genera_dati(n);

    vettore_trigger = new QVector<bool>(n);
    for(int i=0; i<n; ++i){
        if((*vettore_dati)[i]>soglia) (*vettore_trigger)[i]=1;
        else (*vettore_trigger)[i]=0;
    }
}


void sensore_aria::accept(visitor_grafico* visitor){
    visitor->visit(this);
}


void sensore_aria::accept(visitor_dati* visitor){
    visitor->visit(this);
}
