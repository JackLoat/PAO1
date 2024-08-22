#ifndef SENSOREVENT_H
#define SENSOREVENT_H

#include "sensorearia.h"

class sensore_vent: public sensore_aria{

protected:

    QVector<double>* vettore_direz;

public:

    sensore_vent(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c/*, const QString& p = ":/resources/resources/asset/icona_sensore_vento"*/);
    sensore_vent(const sensore& copia);
    ~sensore_vent() override;

    const QVector<double>* getDirez() const;

    //chartBox* setup_box_grafo(QWidget* parent) override;        //da togliere e gestire col visitor
    void genera_dati(const int& n=7) override;

    //test
    void accept(visitor_grafico* visitor) override;
};

#endif // SENSOREVENT_H
