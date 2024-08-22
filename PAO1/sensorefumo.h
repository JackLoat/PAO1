#ifndef SENSOREFUMO_H
#define SENSOREFUMO_H

#include "sensori.h"

class sensore_fumo: public sensore{

protected:

    QVector<bool>* vettore_trigger;

public:

    sensore_fumo(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c/*, const QString& p = ":/resources/resources/asset/icona_sensore_fumo"*/);
    sensore_fumo(const sensore& copia);
    ~sensore_fumo() override;

    const QVector<bool>* getTrigger() const;

    void genera_dati(const int& n=7) override;
    //chartBox* setup_box_grafo(QWidget* parent=nullptr) override;        //da togliere e gestire col visitor

    //test
    void accept(visitor_grafico* visitor) override;

};

#endif // SENSOREFUMO_H
