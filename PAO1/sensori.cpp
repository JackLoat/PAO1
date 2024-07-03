#include "sensori.h"


void sensore::rinomina(const QString& n){
    nome = n;
}

sensore::~sensore(){}

void sensore::sensorToWI(QListWidgetItem& item){
    //metti nome, tipo, stanza, data nelle informazioni di item
    // nome come testo, tipo come icona, stanza e datacreazione come tooltip
    // puntatore a sensore come data

    item.setText(nome);
    item.setToolTip("Stanza: "+stanza+"\nData creazione: "+data_creazione.toString());
    item.setData(Qt::UserRole, QVariant::fromValue(this));

    QString percorso = "/home/student/Desktop/asset/icon_sensor.jpeg"; //MODIFICA PRIMA DELLA CONSEGNA
    QPixmap pixmap(percorso);
    QIcon icon(pixmap);
    item.setIcon(icon);
}


QString sensore::getNome(){
    return nome;
}

QDate sensore::getDataC(){
    return data_creazione;
}

QString sensore::getTipo(){
    return tipo;
}

QString sensore::getStanza(){
    return stanza;
}

collezione* sensore::getCollezione(){
    return ptrCollezione;
}

QString collezione::getNome() const{
    return nome;
}

QString collezione::getPath() const{
    return path;
}

void collezione::add_sensore(sensore *s){
    lista_sensori.push_back(s);
}

void collezione::rm_sensore(sensore *s){
    lista_sensori.removeOne(s);
}
