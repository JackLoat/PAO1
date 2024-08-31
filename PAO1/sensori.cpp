#include "sensori.h"
#include "collezione.h"

sensore::sensore(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c/*, const QString& p*/):
    nome(n),data_creazione(d),tipo(t),stanza(s),ptrCollezione(c) {}

sensore::sensore(const sensore& copia){
    nome = copia.nome;
    data_creazione = copia.data_creazione;
    tipo = copia.tipo;
    stanza = copia.stanza;
    ptrCollezione = copia.ptrCollezione;
}

sensore::~sensore(){
    ptrCollezione->rm_sensore(this);
}

const QString& sensore::getNome() const{
    return nome;
}


const QDate& sensore::getDataC() const{
    return data_creazione;
}


const QString& sensore::getTipo() const{
    return tipo;
}


const QString& sensore::getStanza() const{
    return stanza;
}


void sensore::setNome(const QString& newNome){
    nome = newNome;
}


void sensore::setStanza(const QString &newStanza){
    stanza = newStanza;
}


void sensore::setTipo(const QString &newTipo){
    tipo = newTipo;
}

collezione* sensore::getCollezione(){
    return ptrCollezione;
}


void sensore::aggiorna_file(const QString& oldName) const{
    //aggiorna il file dopo che i campi del sensore sono stati modificati

    QString path = ptrCollezione->getPath();
    QFile file(path);

    if(!file.open(QIODevice::ReadWrite|QIODevice::Text)){
        throw std::runtime_error("Impossibile aprire il file che contiene il sensore.");
        return;
    }

    QTextStream in(&file);
    QStringList fileContent;
    while(!in.atEnd()){
        QString line = in.readLine().trimmed();

        QStringList fields = line.split(",",Qt::SkipEmptyParts);

        if(fields.count()>=2 && fields.at(1).trimmed() == oldName){
            fields.replace(1,nome);
            fields.replace(0,stanza);
            fields.replace(2,tipo);
            line = fields.join(",");
        }

        fileContent.append(line);
    }

    file.resize(0);

    QTextStream out(&file);
    for (const QString& line : fileContent){
        out << line << "\n";
    }
    file.close();
}


