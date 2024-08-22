#ifndef COLLEZIONE_H
#define COLLEZIONE_H

#include <QString>
#include <QList>

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

#endif // COLLEZIONE_H
