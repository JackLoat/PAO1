#ifndef SENSOREARIA_H
#define SENSOREARIA_H

#include "sensoretemp.h"

class sensore_aria: public sensore_temp{

protected:

    QVector<bool>* vettore_trigger;
    double soglia;

public:
    sensore_aria(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c/*, const QString& p = ":/resources/resources/asset/icona_sensore_qualità_aria"*/);
    sensore_aria(const sensore& copia);
    ~sensore_aria() override;

    const double& getSoglia() const;
    void setSoglia(const double& s);
    const QVector<bool>* getTrigger() const;

    void genera_dati(const int& n=7) override;
    //chartBox* setup_box_grafo(QWidget* parent=nullptr) override;    //da togliere e gestire col visitor

    //test
    void accept(visitor_grafico* visitor) override;
};

#endif // SENSOREARIA_H
