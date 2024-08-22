#include "sensoretemp.h"
#include "visitor.h"

sensore_temp::sensore_temp(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c/*, const QString& p*/):sensore(n,d,t,s,c/*,p*/){
    min = -15;
    max = 40;
    vettore_dati = nullptr;
}

sensore_temp::sensore_temp(const sensore& copia):sensore(copia){
    min = -15;
    max = 40;
    //setIcona(":/resources/resources/asset/icona_sensore_temperatura");
    vettore_dati = nullptr;
}

sensore_temp::~sensore_temp(){
    delete vettore_dati;
}

const QVector<double>* sensore_temp::getDati() const{
    return vettore_dati;
}

const double& sensore_temp::getMin() const{
    return min;
}


const double& sensore_temp::getMax() const{
    return max;
}


void sensore_temp::setMin(const double& newMin){
    min = newMin;
}


void sensore_temp::setMax(const double& newMax){
    max = newMax;
}

//salva in vettore_dati un vettore di n double distribuiti casualmente tra min e max
void sensore_temp::genera_dati(const int& n){
    vettore_dati = new QVector<double>(n);
    for(int i=0; i<n; ++i){
        (*vettore_dati)[i] = min+QRandomGenerator::global()->generateDouble()*(max-min);
    }
}

void sensore_temp::accept(visitor_grafico* visitor){
    //qDebug()<<"sensore_temp::accept";
    visitor->visit(this);
}
