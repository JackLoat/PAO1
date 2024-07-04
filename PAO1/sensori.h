#ifndef SENSORI_H
#define SENSORI_H

#include <QString>
#include <QDate>
#include <QListWidgetItem>
#include <QVector>
#include <QFile>

class sensore;

class collezione{
private:
    QString nome;
    QList<sensore*> lista_sensori;
    QString path;
public:
    collezione(const QString& n="collezione_senza_nome",const QString& p="percorso_mancante"):nome(n),path(p){}

    void add_sensore(sensore* s);
    void rm_sensore(sensore* s);

    QString getNome() const;

    QString getPath() const;


};

class sensore{
private:
    QString nome;
    QDate data_creazione;
    QString tipo;                       //valuta se cambiarla con una enum
    QString stanza;
    collezione* ptrCollezione;
public:
    sensore(const QString& n="Sensore_senza_nome", const QDate& d=QDate::currentDate(), const QString& t="tipo_mancante", const QString& s="", collezione* c=nullptr):
        nome(n),data_creazione(d),tipo(t),stanza(s),ptrCollezione(c) {}

    virtual QVector<double> genera_dati(const int& giorni) const =0; //-> vedi come gestirla con Qtcharts o qualsiasi libreria per generare grafici e allarmi
                                //VEDI TIPO DI RITORNO

    void rinomina(const QString& n="Sensore_senza_nome");

    void sensorToWI(QListWidgetItem& item);

    QString getNome();
    void setNome(const QString& newNome);
    QDate getDataC();
    QString getTipo();
    void setTipo(const QString& newTipo);
    QString getStanza();
    void setStanza(const QString& newStanza);

    collezione* getCollezione();
    void aggiorna_file(const QString& oldName);

    virtual ~sensore();
};

class sensore_temp: public sensore{
public:
    sensore_temp(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c):sensore(n,d,t,s,c){}

    QVector<double> genera_dati(const int& giorni) const override{
        QVector<double> a(giorni);
        return a;
    }
};

class sensore_fumo: public sensore{
public:
    sensore_fumo(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c):sensore(n,d,t,s,c){}

    QVector<double> genera_dati(const int& giorni) const override{
        QVector<double> a(giorni);
        return a;
    }
};

class sensore_aria: public sensore{
public:
    sensore_aria(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c):sensore(n,d,t,s,c){}

    QVector<double> genera_dati(const int& giorni) const override{
        QVector<double> a(giorni);
        return a;
    }
};

class sensore_vent: public sensore_aria{
public:
    sensore_vent(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c):sensore_aria(n,d,t,s,c){}

    QVector<double> genera_dati(const int& giorni) const override{
        QVector<double> a(giorni);
        return a;
    }
};


#endif // SENSORI_H
