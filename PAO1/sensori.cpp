#include "sensori.h"

collezione::collezione(const QString& n,const QString& p):nome(n),path(p){}

collezione::~collezione(){
    lista_sensori.clear();
}//nb non distrugge i sensori contenuti nella lista, modifica se necessario.

sensore::sensore(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c):
    nome(n),data_creazione(d),tipo(t),stanza(s),ptrCollezione(c) {}

sensore_temp::sensore_temp(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c):sensore(n,d,t,s,c){
    min = -15;
    max = 40;
}

sensore_fumo::sensore_fumo(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c):sensore(n,d,t,s,c){}

sensore_aria::sensore_aria(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c):sensore_temp(n,d,t,s,c){
    soglia=50;
    min=0;
    max=150;
}

sensore_vent::sensore_vent(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c):sensore_aria(n,d,t,s,c){
    min = 1;
    max = 60;
    soglia = 35;
}

sensore::~sensore(){}

sensore_temp::~sensore_temp(){
    delete vettore_dati;
}

sensore_fumo::~sensore_fumo(){
    delete vettore_trigger;
}

sensore_aria::~sensore_aria(){
    delete vettore_trigger;
}

sensore_vent::~sensore_vent(){
    delete vettore_direz;
}


void sensore::rinomina(const QString& n){
    nome = n;
}

//sensore::~sensore(){}

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

QVector<double>* sensore_temp::getDati(){
    return vettore_dati;
}

QVector<bool>* sensore_fumo::getTrigger(){
    return vettore_trigger;
}

QVector<bool>* sensore_aria::getTrigger(){
    return vettore_trigger;
}

QVector<double>* sensore_vent::getDirez(){
    return vettore_direz;
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


double sensore_temp::getMin(){
    return min;
}

double sensore_temp::getMax(){
    return max;
}

void sensore_temp::setMin(const double& newMin){
    min = newMin;
}

void sensore_temp::setMax(const double& newMax){
    max = newMax;
}

double sensore_aria::getSoglia(){
    return soglia;
}

void sensore_aria::setSoglia(const double& s){
    soglia = s;
}

//salva in vettore_dati un vettore di n double distribuiti casualmente tra min e max
void sensore_temp::genera_dati(const int& n){
    vettore_dati = new QVector<double>(n);
    for(int i=0; i<n; ++i){
        (*vettore_dati)[i] = min+QRandomGenerator::global()->generateDouble()*(max-min);
    }
}
/*
void sensore_temp::genera_dati(QVector<double> &vettore_dati, const int &n, const double &min, const double &max) const{

    if(vettore_dati.size() != n) {
        qDebug() << "Vettore di dimensione sbagliata";
        return;
    }

    for(int i=0; i<n; ++i){
        vettore_dati[i] = min + QRandomGenerator::global()->generateDouble()*(max-min);
    }
}
*/

//salva in vettore_trigger un vettore di n bool distribuiti casualmente
void sensore_fumo::genera_dati(const int &n){
    vettore_trigger = new QVector<bool>(n);
    for(int i=0; i<n; ++i){
        (*vettore_trigger)[i] = (QRandomGenerator::global()->bounded(0,2)==1);
    }
}
/*
void sensore_fumo::genera_dati(QVector<bool> &vettore_trigger, const int &n) const{
    if(vettore_trigger.size() != n){
        qDebug()<<"Vettore di dimensione sbagliata";
        return;
    }

    for(int i=0; i<n; ++i){
        vettore_trigger[i] = (QRandomGenerator::global()->bounded(0,2)==1);
    }
}
*/

//la chiamata a sensore_temp(genera_dati) salva in vettore_dati n double casuali tra max e min,
//poi salva in vettore_trigger tutti gli indici di vettore_dati in cui vettore_dati[i]>s
void sensore_aria::genera_dati(const int &n){
    sensore_temp::genera_dati(n);

    vettore_trigger = new QVector<bool>(n);
    for(int i=0; i<n; ++i){
        if((*vettore_dati)[i]>soglia) (*vettore_trigger)[i]=1;
        else (*vettore_trigger)[i]=0;
    }
}
/*
void sensore_aria::genera_dati(QVector<double> &vettore_dati, QVector<bool> &vettore_trigger, const int &n, const double &min, const double &max, const double& soglia) const{

    sensore_temp::genera_dati(vettore_dati,n,min,max);  //compila vettore_dati

    for(int i=0; i<n; ++i){
        if(vettore_dati[i]>soglia) vettore_trigger[i]=1;
        else vettore_trigger[i]=0;
    }
}
*/

//la chiamata a sensore_aria compila vettore_dati e vettore_trigger
    //chiama sensore_temp che salva in vettore_dati n double casuali tra max e min,
    //salva in vettore_trigger tutti gli indici di vettore_dati che vanno oltre la soglia,
//poi salva in vettore_direz le direzioni casuali medie del vento per ogni giorno
void sensore_vent::genera_dati(const int& n){
    sensore_aria::genera_dati(n);

    vettore_direz = new QVector<double>(n);
    for(int i=0;i<n;i++){
        (*vettore_direz)[i] = QRandomGenerator::global()->generateDouble()*(2*3.14);
    }
}
/*
void sensore_vent::genera_dati(QVector<double> &vettore_dati, QVector<bool> &vettore_trigger, QVector<double> &vettore_direz, const int &n, const double &min, const double &max, const double &soglia) const{

    sensore_aria::genera_dati(vettore_dati, vettore_trigger, n, min, max, soglia);

    for(int i=0; i<n; ++i){
        vettore_direz[i] = 0 + QRandomGenerator::global()->generateDouble()*(2*3.14);
    }
}
*/

//crea una QGroupBox(?) che abbia spazio per: comboGiorni, min, max, chart, pushButton "genera_dati"
chartBox* sensore_temp::setup_box_grafo(QWidget* parent) const{
    //qDebug()<<"sensore_temp::setup_box_grafo";
    return new chartTemp(parent,this);
}

//crea qgb con: pushButton "genera_dati", comboGiorni, e chart
chartBox* sensore_fumo::setup_box_grafo(QWidget* parent) const{
    //qDebug()<<"sensore_fumo::setup_box_grafo";
    return new chartBox(parent,this);
}

//crea qgb con: pushButton "genera_d", comboGiorni, chart, min, max, soglia
chartBox* sensore_aria::setup_box_grafo(QWidget* parent) const{
    //qDebug()<<"sensore_aria::setup_box_grafo";
    return new chartAria(parent,this);
}

//crea qgb con: pushButton "genera_d", comboGiorni, chart, min, max, soglia (e qualcosa per mostrare i venti?)
chartBox* sensore_vent::setup_box_grafo(QWidget* parent) const{
    //qDebug()<<"sensore_vent::setup_box_grafo";
    return new chartVent(parent,this);
}
