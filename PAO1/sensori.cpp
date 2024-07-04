#include "sensori.h"


void sensore::rinomina(const QString& n){
    nome = n;
}

sensore::~sensore(){}

void sensore::sensorToWI(QListWidgetItem& item){
    //metti nome, tipo, stanza, data nelle informazioni di item
    // nome come testo, tipo come icona, stanza e datacreazione come tooltip
    // puntatore a sensore come data

    item.setText(nome);
    item.setToolTip("Stanza: "+stanza+"\nData creazione: "+data_creazione.toString());
    item.setData(Qt::UserRole, QVariant::fromValue(this));

    QString percorso = "/home/student/Desktop/asset/icon_sensor.jpeg"; //MODIFICA PRIMA DELLA CONSEGNA
    QPixmap pixmap(percorso);
    QIcon icon(pixmap);
    item.setIcon(icon);
}


QString sensore::getNome(){
    return nome;
}

QDate sensore::getDataC(){
    return data_creazione;
}

QString sensore::getTipo(){
    return tipo;
}

QString sensore::getStanza(){
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

QString collezione::getNome() const{
    return nome;
}

QString collezione::getPath() const{
    return path;
}

void collezione::add_sensore(sensore *s){
    lista_sensori.push_back(s);
}

void collezione::rm_sensore(sensore *s){
    lista_sensori.removeOne(s);
}

void sensore::aggiorna_file(const QString& oldName){ //da chiamare dopo che i campi sono già stati modificati
    QString path = ptrCollezione->getPath();
    QFile file(path);

    if(!file.open(QIODevice::ReadWrite|QIODevice::Text)){
        qDebug()<<"Impossibile aprire file: "<<file.errorString();
        return;
    }

    QTextStream in(&file);
    QStringList fileContent;        //salva linea per linea il contenuto del file
                                //quando il loop trova la linea giusta, la modifica e poi la appende qua

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

    file.resize(0); //cancella il file e riscrive il nuovo contenuto
    QTextStream out(&file);
    for (const QString& line : fileContent){
        out << line << "\n";
    }

    file.close();

}
