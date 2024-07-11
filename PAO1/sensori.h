#ifndef SENSORI_H
#define SENSORI_H

#include <QString>
#include <QDate>
#include <QListWidgetItem>
#include <QVector>
#include <QFile>
#include <QRandomGenerator>
#include <algorithm>
#include "chartBox.h"
#include <QCoreApplication>
#include <QDir>

//class chartBox;


class sensore;

class collezione{
private:
    QString nome;
    QList<sensore*> lista_sensori;
    QString path;
public:
    collezione(const QString& n="collezione_senza_nome",const QString& p="percorso_mancante");

    void add_sensore(sensore* s);
    void rm_sensore(sensore* s);

    QString getNome() const;

    QString getPath() const;

    ~collezione();//nb distrugge la collezione ma non i sensori puntati dalla lista, modifica se necessario.
};

class sensore{
private:
    QString nome;
    QDate data_creazione;
    QString tipo;                       //valuta se cambiarla con una enum
    QString stanza;
    collezione* ptrCollezione;
    QIcon* icona;
public:
    sensore(const QString& n="Sensore_senza_nome", const QDate& d=QDate::currentDate(), const QString& t="tipo_mancante", const QString& s="", collezione* c=nullptr, const QString& pathIcona = ":/resources/resources/asset/icon_sensor.jpeg");

    sensore(const sensore& copia);

    void rinomina(const QString& n="Sensore_senza_nome");

    void sensorToWI(QListWidgetItem& item);

    const QString& getNome();
    void setNome(const QString& newNome);
    const QDate& getDataC();
    const QString& getTipo();
    void setTipo(const QString& newTipo);
    const QString& getStanza();
    void setStanza(const QString& newStanza);

    const QIcon* getIcona();

    collezione* getCollezione();
    void aggiorna_file(const QString& oldName);

    virtual void genera_dati(const int& n=7) =0;
    virtual chartBox* setup_box_grafo(QWidget* parent=nullptr) const =0;

    virtual ~sensore();
protected:
    void setIcona(const QString& path);
};

class sensore_temp: public sensore{
protected:
    QVector<double>* vettore_dati;
    double min;
    double max;

public:
    sensore_temp(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c, const QString& p = ":/resources/resources/asset/icona_sensore_temperatura");
    sensore_temp(const sensore& copia);

    //void genera_dati(QVector<double>& vettore_dati, const int& n=7, const double& min=-15, const double& max=40) const;
    void genera_dati(const int& n=7) override;
    chartBox* setup_box_grafo(QWidget* parent=nullptr) const override;

    double getMin();
    double getMax();
    void setMin(const double& newMin);
    void setMax(const double& newMax);

    QVector<double>* getDati();

    ~sensore_temp() override;
};

class sensore_fumo: public sensore{
protected:
    QVector<bool>* vettore_trigger;

public:
    sensore_fumo(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c, const QString& p = ":/resources/resources/asset/icona_sensore_fumo");
    sensore_fumo(const sensore& copia);

    //void genera_dati(QVector<bool>& vettore_trigger, const int& n=7) const;
    void genera_dati(const int& n=7) override;
    chartBox* setup_box_grafo(QWidget* parent=nullptr) const override;

    QVector<bool>* getTrigger();

    ~sensore_fumo() override;
};

class sensore_aria: public sensore_temp{
protected:
    QVector<bool>* vettore_trigger;
    double soglia;

public:
    sensore_aria(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c, const QString& p = ":/resources/resources/asset/icona_sensore_qualità_aria");
    sensore_aria(const sensore& copia);

    //void genera_dati(QVector<double>& vettore_dati, QVector<bool>& vettore_trigger, const int& n=7, const double& min=0, const double& max=150, const double& soglia=50) const;
    void genera_dati(const int& n=7) override;
    chartBox* setup_box_grafo(QWidget* parent=nullptr) const override;

    double getSoglia();
    void setSoglia(const double& s);

    QVector<bool>* getTrigger();

    ~sensore_aria() override;
};

class sensore_vent: public sensore_aria{
protected:
    QVector<double>* vettore_direz;

public:
    sensore_vent(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c, const QString& p = ":/resources/resources/asset/icona_sensore_vento");
    sensore_vent(const sensore& copia);

    //void genera_dati(QVector<double>& vettore_dati, QVector<bool>& vettore_trigger, QVector<double>& vettore_direz, const int& n=7, const double& min=1, const double& max=60, const double& soglia=35) const;
    void genera_dati(const int& n=7) override;
    //chartBox* setup_box_grafo(QWidget* parent=nullptr) const override;

    QVector<double>* getDirez();

    chartBox* setup_box_grafo(QWidget* parent) const override;

    ~sensore_vent() override;
};

#endif // SENSORI_H
