#ifndef SENSORI_H
#define SENSORI_H

#include <QString>
#include <QDate>
#include <QListWidgetItem>
#include <QVector>
#include <QFile>
#include <QRandomGenerator>
#include "chartBox.h"

class sensore;


class collezione{

private:

    QString nome;
    QList<sensore*> lista_sensori;
    QString path;

public:

    collezione(const QString& n="collezione_senza_nome",const QString& p="percorso_mancante");
    ~collezione();
    void add_sensore(sensore* s);
    void rm_sensore(sensore* s);
    const QString& getNome() const;
    const QString& getPath() const;

};

class sensore{

private:

    QString nome;
    QDate data_creazione;
    QString tipo;
    QString stanza;
    collezione* ptrCollezione;
    QIcon* icona;

protected:

    void setIcona(const QString& path);

public:

    sensore(const QString& n="Sensore_senza_nome", const QDate& d=QDate::currentDate(), const QString& t="tipo_mancante", const QString& s="", collezione* c=nullptr, const QString& pathIcona = ":/resources/resources/asset/icon_sensor.jpeg");
    sensore(const sensore& copia);
    virtual ~sensore();

    const QString& getNome() const;
    void setNome(const QString& newNome);
    const QDate& getDataC() const;
    const QString& getTipo() const;
    void setTipo(const QString& newTipo);
    const QString& getStanza() const;
    void setStanza(const QString& newStanza);
    const QIcon* getIcona() const;
    collezione* getCollezione();

    void sensorToWI(QListWidgetItem& item);
    void aggiorna_file(const QString& oldName) const;
    virtual void genera_dati(const int& n=7) =0;
    virtual chartBox* setup_box_grafo(QWidget* parent=nullptr) =0;

};

class sensore_temp: public sensore{

protected:

    QVector<double>* vettore_dati;
    double min;
    double max;

public:

    sensore_temp(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c, const QString& p = ":/resources/resources/asset/icona_sensore_temperatura");
    sensore_temp(const sensore& copia);
    ~sensore_temp() override;

    const double& getMin() const;
    const double& getMax() const;
    void setMin(const double& newMin);
    void setMax(const double& newMax);
    const QVector<double>* getDati() const;

    void genera_dati(const int& n=7) override;
    chartBox* setup_box_grafo(QWidget* parent=nullptr) override;

};

class sensore_fumo: public sensore{

protected:

    QVector<bool>* vettore_trigger;

public:

    sensore_fumo(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c, const QString& p = ":/resources/resources/asset/icona_sensore_fumo");
    sensore_fumo(const sensore& copia);
    ~sensore_fumo() override;

    const QVector<bool>* getTrigger() const;

    void genera_dati(const int& n=7) override;
    chartBox* setup_box_grafo(QWidget* parent=nullptr) override;

};

class sensore_aria: public sensore_temp{

protected:

    QVector<bool>* vettore_trigger;
    double soglia;

public:
    sensore_aria(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c, const QString& p = ":/resources/resources/asset/icona_sensore_qualità_aria");
    sensore_aria(const sensore& copia);
    ~sensore_aria() override;

    const double& getSoglia() const;
    void setSoglia(const double& s);
    const QVector<bool>* getTrigger() const;

    void genera_dati(const int& n=7) override;
    chartBox* setup_box_grafo(QWidget* parent=nullptr) override;

};

class sensore_vent: public sensore_aria{

protected:

    QVector<double>* vettore_direz;

public:

    sensore_vent(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c, const QString& p = ":/resources/resources/asset/icona_sensore_vento");
    sensore_vent(const sensore& copia);
    ~sensore_vent() override;

    const QVector<double>* getDirez() const;

    chartBox* setup_box_grafo(QWidget* parent) override;
    void genera_dati(const int& n=7) override;

};

#endif // SENSORI_H
