#include "sensorBox.h"


sensorBox::sensorBox(QWidget *parent): QGroupBox(parent){

    Htipo = new QLabel("Tipo:", this);
    HdataC = new QLabel("Data C:", this);
    Hcollezione = new QLabel("Collezione:", this);
    Hstanza = new QLabel("Stanza:", this);
    icona = new QLabel("", this);

    tipo = new QLabel(" ", this);
    dataC = new QLabel(" ", this);
    collezione = new QLabel(" ", this);
    stanza = new QLabel(" ", this);

    modifica = new QPushButton("Modifica", this);
    modifica->setDisabled(true);
    rimuovi = new QPushButton("Rimuovi", this);
    rimuovi->setDisabled(true);

    QVBoxLayout *labelLayout = new QVBoxLayout;
    labelLayout->addWidget(tipo);
    labelLayout->addWidget(dataC);
    labelLayout->addWidget(collezione);
    labelLayout->addWidget(stanza);

    QVBoxLayout *headerLayout = new QVBoxLayout;
    headerLayout->addWidget(Htipo);
    headerLayout->addWidget(HdataC);
    headerLayout->addWidget(Hcollezione);
    headerLayout->addWidget(Hstanza);

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(icona);
    buttonLayout->addWidget(modifica);
    buttonLayout->addWidget(rimuovi);

    mainLayout = new QHBoxLayout;
    mainLayout->addLayout(headerLayout);
    mainLayout->addLayout(labelLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connectButtons();

}


void sensorBox::connectButtons() {

    connect(modifica, &QPushButton::clicked, this, &sensorBox::on_modifica_clicked);
    connect(rimuovi, &QPushButton::clicked, this, &sensorBox::onRimuoviClicked);

}

sensorBox::~sensorBox(){

    delete mainLayout;

    delete Htipo;
    delete HdataC;
    delete Hcollezione;
    delete Hstanza;

    delete tipo;
    delete dataC;
    delete collezione;
    delete stanza;
    delete icona;

    delete modifica;
    delete rimuovi;

}

void sensorBox::setTipo(const QString& t){
    tipo->setText(t);
}

void sensorBox::setData(const QString& d){
    dataC->setText(d);
}

void sensorBox::setColl(const QString& c){
    collezione->setText(c);
}

void sensorBox::setStanza(const QString& s){
    stanza->setText(s);
}

void sensorBox::setIcona(QPixmap p){
    icona->setPixmap(p);
}

QString sensorBox::getTipo() const{
    return tipo->text();
}

QString sensorBox::getData() const{
    return dataC->text();
}

QString sensorBox::getColl() const{
    return collezione->text();
}
QString sensorBox::getStanza() const{
    return stanza->text();
}

QPixmap sensorBox::getIcona() const{
    return icona->pixmap();
}

void sensorBox::disabilitaModifica(const bool& x){
    modifica->setDisabled(x);
}
void sensorBox::disabilitaRimuovi(const bool& x){
    rimuovi->setDisabled(x);
}



void sensorBox::reset(){

    setTitle("Nome sensore");
    tipo->setText("");
    dataC->setText("");
    stanza->setText("");
    collezione->setText("");
    QPixmap emptyPixMap;
    icona->setPixmap(emptyPixMap);
    setProperty("PuntatoreSensore",QVariant());
    setProperty("PuntatoreItem",QVariant());
    modifica->setDisabled(true);
    rimuovi->setDisabled(true);

}


void sensorBox::on_modifica_clicked() {

    QString oldName = title();

    editDialog ed(this);
    ed.setLabelsText(title(), stanza->text(), tipo->text());

    //se l'utente rifiuta la modifica non viene eseguita alcuna azione
    if(ed.exec() == QDialog::Rejected) return;

    //modificare i campi della sensorBox
    setTitle(ed.getNome());
    stanza->setText(ed.getStanza());
    tipo->setText(ed.getTipo());

    //aggiorna il sensore effettivo
    void* sensorVoid = property("PuntatoreSensore").value<void*>();
    sensore* sensor = static_cast<sensore*>(sensorVoid);
    sensor->setNome(title());
    sensor->setStanza(stanza->text());

    //azioni da eseguire se è stato modificato il tipo
    if(sensor->getTipo() != tipo->text()){
        sensor->setTipo(tipo->text());

        //crea un nuovo sensore del tipo giusto a partire dai dati del primo
        sensore* newSensor;
        if(tipo->text() == "Fumo") newSensor = new sensore_fumo(*sensor);
        else if(tipo->text() == "Temperatura") newSensor = new sensore_temp(*sensor);
        else if(tipo->text() == "Aria") newSensor = new sensore_aria(*sensor);
        else newSensor = new sensore_vent(*sensor);

        //modifica l'elemento nella collezione
        sensor->getCollezione()->rm_sensore(sensor);
        sensor->getCollezione()->add_sensore(newSensor);

        //elimina vecchio sensore
        delete sensor;
        sensor = newSensor;

        //completa aggiornamento sensor_box
        this->setProperty("PuntatoreSensore", QVariant::fromValue(static_cast<void*>(sensor)));
        qDebug()<<"inizio sensorBox::on modifica clicked set icona 1";
            //da rimuovere
        //icona->setPixmap(sensor->getIcona()->pixmap(64,64));
            //test
        icona->setPixmap((new QIcon(":/resources/resources/asset/icona_sensore_"+sensor->getTipo()))->pixmap(64,64));
        qDebug()<<"fine sensorBox::on modifica clicked set icona 1";
    }

    //aggiorna item in mostra_sensori
    void* itemPointerVoid = property("PuntatoreItem").value<void*>();
    QListWidgetItem* item = static_cast<QListWidgetItem*>(itemPointerVoid);
    item->setText(title());
    item->setToolTip("Stanza: "+stanza->text()+"\nData creazione: "+dataC->text());
    item->setData(Qt::UserRole, QVariant::fromValue(sensor));

    qDebug()<<"inizio sensorBox::onModificaClicked set icona 2";
        //da togliere
    //item->setIcon(*(sensor->getIcona()));
        //test
    const QIcon* icona = new QIcon(":/resources/resources/asset/icona_sensore_"+sensor->getTipo());
    item->setIcon(*icona);
    qDebug()<<"fine sensorBox::onModificaClicked set icona 2";

    //aggiorna chartbox
    //chartBox* box_grafo = sensor->setup_box_grafo();
    //qDebug()<<"inizio sensorBox::on_modifica_clicked::unire i puntini";     //test !!: unire i puntini

    visitor_grafico* visitor = new visitor_grafico();
    sensor->accept(visitor);
    chartBox* box_grafo = visitor->getWidget();
    //qDebug()<<"fine sensorBox::on_modifica_clicked::unire i puntini";
    //modifica chartContainer
    emit modificaChartContainer(box_grafo);

    //aggiorna file
    try{
        sensor->aggiorna_file(oldName);
    }
    catch(const std::runtime_error &ex){
        QMessageBox::critical(this,"Errore","Errore nell'aggiornamento del file.");
    }
}

void sensorBox::onRimuoviClicked() {

    //finestra di conferma
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Conferma eliminazione", "Vuoi eliminare questo sensore? Non sarà più recuperabile", QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::No) return;

    void* sensorPointerVoid = property("PuntatoreSensore").value<void*>();
    sensore* sensor = static_cast<sensore*>(sensorPointerVoid);
    if(!sensor) return;//se non c'è alcun sensore caricato sul box non fa niente

    //cancella il sensore dal file
    QString percorso = sensor->getCollezione()->getPath();
    QFile file(percorso);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Errore","Impossibile trovare il file del sensore.");
        return;
    }

    QString target = sensor->getNome();
    QTextStream in(&file);
    QString nuovo_contenuto;
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList parts = line.split(',');
        if (parts.size()>=4 && parts[1].trimmed()==target){
            continue;
        }
        nuovo_contenuto += line +"\n";
    }
    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            QMessageBox::critical(this,"Errore","Errore nell'eliminazione del sensore.");
            return;
    }
    QTextStream out(&file);
    out<<nuovo_contenuto;
    file.close();

    //rimuovi l'item dalla lista ui->mostra_sensori
    void* itemPointerVoid = property("PuntatoreItem").value<void*>();
    QListWidgetItem* item = static_cast<QListWidgetItem*>(itemPointerVoid);
    emit removeItem(item);

    //svuota la chartBox
    emit resetChartBox();

    //rimuovi il sensore dalla collezione
    sensor->getCollezione()->rm_sensore(sensor);

    //distruggi il sensore vero e proprio
    delete sensor;

    //svuota la sensorBox
    reset();

}
