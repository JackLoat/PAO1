#ifndef SENSORETEMP_H
#define SENSORETEMP_H

#include "sensori.h"

class sensore_temp: public sensore{

protected:

    QVector<double>* vettore_dati;
    double min;
    double max;

public:

    sensore_temp(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c/*, const QString& p = ":/resources/resources/asset/icona_sensore_temperatura"*/);
    sensore_temp(const sensore& copia);
    ~sensore_temp() override;

    const double& getMin() const;
    const double& getMax() const;
    void setMin(const double& newMin);
    void setMax(const double& newMax);
    const QVector<double>* getDati() const;

    void genera_dati(const int& n=7) override;
    //chartBox* setup_box_grafo(QWidget* parent=nullptr) override;    //da togliere e gestire col visitor

    //test
    void accept(visitor_grafico* visitor) override;

};

#endif // SENSORETEMP_H
