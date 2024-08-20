#include "sensori.h"

collezione::collezione(const QString& n,const QString& p):nome(n),path(p){}


collezione::~collezione(){
    for(auto sensore:lista_sensori){
        delete sensore;
    }
    lista_sensori.clear();
}


void collezione::add_sensore(sensore *s){
    lista_sensori.push_back(s);
}


void collezione::rm_sensore(sensore *s){
    lista_sensori.removeOne(s);
}


sensore::sensore(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c/*, const QString& p*/):
    nome(n),data_creazione(d),tipo(t),stanza(s),ptrCollezione(c)
{
    //icona = new QIcon(p);
}


sensore_temp::sensore_temp(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c/*, const QString& p*/):sensore(n,d,t,s,c/*,p*/){
    min = -15;
    max = 40;
    vettore_dati = nullptr;
}


sensore_fumo::sensore_fumo(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c/*, const QString& p*/):sensore(n,d,t,s,c/*,p*/){
    vettore_trigger = nullptr;
}


sensore_aria::sensore_aria(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c/*, const QString& p*/):sensore_temp(n,d,t,s,c/*,p*/){
    soglia=50;
    min=0;
    max=150;
    vettore_trigger = nullptr;
}


sensore_vent::sensore_vent(const QString& n, const QDate& d, const QString& t, const QString& s, collezione* c/*, const QString& p*/):sensore_aria(n,d,t,s,c/*,p*/){
    min = 1;
    max = 60;
    soglia = 35;
    vettore_direz = nullptr;
}


sensore::sensore(const sensore& copia){
    nome = copia.nome;
    data_creazione = copia.data_creazione;
    tipo = copia.tipo;
    stanza = copia.stanza;
    ptrCollezione = copia.ptrCollezione;
}


sensore_temp::sensore_temp(const sensore& copia):sensore(copia){
    min = -15;
    max = 40;
    //setIcona(":/resources/resources/asset/icona_sensore_temperatura");
    vettore_dati = nullptr;
}


sensore_fumo::sensore_fumo(const sensore& copia):sensore(copia){
    //setIcona(":/resources/resources/asset/icona_sensore_fumo");
    vettore_trigger = nullptr;
}


sensore_aria::sensore_aria(const sensore& copia):sensore_temp(copia){
    soglia = 50;
    min = 0;
    max = 150;
    //setIcona(":/resources/resources/asset/icona_sensore_qualità_aria");
    vettore_trigger = nullptr;
}


sensore_vent::sensore_vent(const sensore& copia):sensore_aria(copia){
    min = 1;
    max = 60;
    soglia = 35;
    //setIcona(":/resources/resources/asset/icona_sensore_vento");
    vettore_direz = nullptr;
}


sensore::~sensore(){
    //delete icona;
    ptrCollezione->rm_sensore(this);
}


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


const QString& collezione::getNome() const{
    return nome;
}


const QString& collezione::getPath() const{
    return path;
}


const QVector<double>* sensore_temp::getDati() const{
    return vettore_dati;
}


const QVector<bool>* sensore_fumo::getTrigger() const{
    return vettore_trigger;
}


const QVector<bool>* sensore_aria::getTrigger() const{
    return vettore_trigger;
}


const QVector<double>* sensore_vent::getDirez() const{
    return vettore_direz;
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


const double& sensore_temp::getMin() const{
    return min;
}


const double& sensore_temp::getMax() const{
    return max;
}


void sensore_temp::setMin(const double& newMin){
    min = newMin;
}


void sensore_temp::setMax(const double& newMax){
    max = newMax;
}


const double& sensore_aria::getSoglia() const{
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


//salva in vettore_trigger un vettore di n bool distribuiti casualmente
void sensore_fumo::genera_dati(const int &n){
    vettore_trigger = new QVector<bool>(n);
    for(int i=0; i<n; ++i){
        (*vettore_trigger)[i] = (QRandomGenerator::global()->bounded(0,2)==1);
    }
}


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

//la chiamata a sensore_aria compila vettore_dati e vettore_trigger:
    //in vettore_trigger segna con true le posizioni in cui in vettore dati un valore va oltre la soglia;
//poi salva in vettore_direz le direzioni casuali medie del vento per ogni giorno
void sensore_vent::genera_dati(const int& n){
    sensore_aria::genera_dati(n);

    vettore_direz = new QVector<double>(n);
    for(int i=0;i<n;i++){
        (*vettore_direz)[i] = QRandomGenerator::global()->generateDouble()*(2*3.14);
    }
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
void sensore_temp::accept(visitor_grafico* visitor){
    //qDebug()<<"sensore_temp::accept";
    visitor->visit(this);
}

void sensore_fumo::accept(visitor_grafico* visitor){
    //qDebug()<<"sensore_fumo::accept";
    visitor->visit(this);
}

void sensore_aria::accept(visitor_grafico* visitor){
    //qDebug()<<"sensore_aria::accept";
    visitor->visit(this);
}

void sensore_vent::accept(visitor_grafico* visitor){
    //qDebug()<<"sensore_vent::accept";
    visitor->visit(this);
}
