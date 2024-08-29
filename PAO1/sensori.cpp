#include "sensori.h"
#include "collezione.h"
//#include "visitor.h"

sensore::sensore(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c/*, const QString& p*/):
    nome(n),data_creazione(d),tipo(t),stanza(s),ptrCollezione(c)
{
    //icona = new QIcon(p);
}

sensore::sensore(const sensore& copia){
    nome = copia.nome;
    data_creazione = copia.data_creazione;
    tipo = copia.tipo;
    stanza = copia.stanza;
    ptrCollezione = copia.ptrCollezione;
}



sensore::~sensore(){
    //delete icona;
    ptrCollezione->rm_sensore(this);
}


        //da eliminare e gestire nell'interfaccia
/*
void sensore::sensorToWI(QListWidgetItem& item){
    qDebug()<<"!!! inizio sensor2wi";
    //setta i campi di item con i dati del sensore
    item.setText(nome);
    item.setToolTip("Stanza: "+stanza+"\nData creazione: "+data_creazione.toString()+"\nTipo: "+tipo);
    item.setData(Qt::UserRole, QVariant::fromValue(this));
    item.setIcon(*icona);
}
*/

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

/*
const QIcon* sensore::getIcona() const{
    return icona;
}

void sensore::setIcona(const QString& path){
    icona = new QIcon(path);
}
*/

collezione* sensore::getCollezione(){
    return ptrCollezione;
}


void sensore::aggiorna_file(const QString& oldName) const{ //aggiorna il file dopo che i campi del sensore sono stati modificati

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


        //da eliminare e gestire con visitor_grafico
/*
chartBox* sensore_temp::setup_box_grafo(QWidget* parent){
    qDebug()<<"sensore_temp::setup_box_grafo";
    return new chartTemp(parent,this);
}


chartBox* sensore_fumo::setup_box_grafo(QWidget* parent){
    qDebug()<<"sensore_fumo::setup_box_grafo";
    return new chartBox(parent,this);
}


chartBox* sensore_aria::setup_box_grafo(QWidget* parent){
    qDebug()<<"sensore_aria::setup_box_grafo";
    return new chartAria(parent,this);
}


chartBox* sensore_vent::setup_box_grafo(QWidget* parent){
    qDebug()<<"sensore_vent::setup_box_grafo";
    return new chartVent(parent,this);
}
*/

//metodi accept


