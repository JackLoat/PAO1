#ifndef SENSORI_H
#define SENSORI_H

#include <QString>
#include <QDate>
#include <QListWidgetItem>
#include <QVector>
#include <QFile>
#include <QRandomGenerator>

//#include "chartBox.h"
//#include "visitor.h"
class visitor_grafico;
//#include "collezione.h"
class collezione;

class sensore{

private:

    QString nome;
    QDate data_creazione;
    QString tipo;
    QString stanza;
    collezione* ptrCollezione;
    //QIcon* icona;               //da rimuovere

protected:

    //void setIcona(const QString& path);

public:

    sensore(const QString& n="Sensore_senza_nome", const QDate& d=QDate::currentDate(), const QString& t="tipo_mancante", const QString& s="", collezione* c=nullptr/*, const QString& pathIcona = ":/resources/resources/asset/icon_sensor.jpeg"*/);
    sensore(const sensore& copia);
    virtual ~sensore();

    const QString& getNome() const;
    void setNome(const QString& newNome);
    const QDate& getDataC() const;
    const QString& getTipo() const;
    void setTipo(const QString& newTipo);
    const QString& getStanza() const;
    void setStanza(const QString& newStanza);
    //const QIcon* getIcona() const;                  //da togliere visto che icona non deve esistere
    collezione* getCollezione();

    void aggiorna_file(const QString& oldName) const;
    virtual void genera_dati(const int& n=7) =0;

    // sensorToWI(QListWidgetItem& item);             //da togliere

    //virtual chartBox* setup_box_grafo(QWidget* parent=nullptr) =0;  //da togliere e gestire col visitor (?)
    //test
    virtual void accept(visitor_grafico* visitor) =0;
};

#endif // SENSORI_H
