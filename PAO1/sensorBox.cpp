#include "sensorBox.h"


sensorBox::sensorBox(QWidget *parent): QGroupBox(parent){

    Htipo = new QLabel("Tipo:", this);
    Htipo->setStyleSheet("color: #007bff;");
    HdataC = new QLabel("Data C:", this);
    HdataC->setStyleSheet("color: #007bff;");
    Hcollezione = new QLabel("Collezione:", this);
    Hcollezione->setStyleSheet("color: #007bff;");
    Hstanza = new QLabel("Stanza:", this);
    Hstanza->setStyleSheet("color: #007bff;");
    icona = new QLabel("", this);
    setTitle("Nome sensore");

    tipo = new QLabel(" ", this);
    tipo->setStyleSheet("color: #007bff;");
    dataC = new QLabel(" ", this);
    dataC->setStyleSheet("color: #007bff;");
    collezione = new QLabel(" ", this);
    collezione->setStyleSheet("color: #007bff;");
    stanza = new QLabel(" ", this);
    stanza->setStyleSheet("color: #007bff;");

    modifica = new QPushButton("", this);
    QIcon icona_modifica(":/resources/resources/asset/icona_modifica");
    modifica->setIcon(icona_modifica);

    modifica->setDisabled(true);
    modifica->setStyleSheet(
        "QPushButton {"
            "color: #007bff;"
            "background-color: white;"
            "border: 1px solid grey;"
            "border-radius: 19px;"
            "padding: 2px;"
        "}"
        "QPushButton:hover {"
            "background-color: #ecf2fc;"
            "border: 1px solid grey;"
        "}"
        "QPushButton:pressed {"
            "background-color: #d5e2f7;"
            "border: 1px solid grey;"
        "}"
        "QPushButton:disabled {"
            "background-color: #bdc3c7;"
            "color: #6c757d;"
            "border: 1px solid #d7d6d5;"
        "}"
    );
    modifica->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    modifica->setMinimumSize(38,38);

    rimuovi = new QPushButton("", this);
    rimuovi->setDisabled(true);

    rimuovi->setStyleSheet(
        "QPushButton {"
        "   color: white;"
        "   border-radius: 19px;"
        "   background-color: #ff4c4c;"
        "   padding: 2px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #ff6666;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #e63939;"
        "}"
        "QPushButton:disabled {"
        "   background-color: #cc9999;"
        "   color: #ffffff;"
        "}"
    );

    rimuovi->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    rimuovi->setMinimumSize(38,38);

    QIcon icona_rimuovi(":/resources/resources/asset/icona_rimuovi");
    rimuovi->setIcon(icona_rimuovi);

    QGridLayout *griglia = new QGridLayout;
    griglia->addWidget(Htipo, 0, 0);
    griglia->addWidget(tipo, 0, 1);

    QFrame *line1 = new QFrame();
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);
    line1->setStyleSheet("color: #d7d6d5;");

    griglia->addWidget(line1, 1, 0, 1, 2);

    griglia->addWidget(HdataC, 2, 0);
    griglia->addWidget(dataC, 2, 1);

    QFrame *line2 = new QFrame();
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);
    line2->setStyleSheet("color: #d7d6d5;");

    griglia->addWidget(line2, 3, 0 ,1, 2);

    griglia->addWidget(Hcollezione, 4, 0);
    griglia->addWidget(collezione, 4, 1);

    QFrame *line3 = new QFrame();
    line3->setFrameShape(QFrame::HLine);
    line3->setFrameShadow(QFrame::Sunken);
    line3->setStyleSheet("color: #d7d6d5;");

    griglia->addWidget(line3, 5, 0 ,1, 2);

    griglia->addWidget(Hstanza, 6, 0);
    griglia->addWidget(stanza, 6, 1);

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(icona);
    buttonLayout->addWidget(modifica, Qt::AlignRight);
    buttonLayout->addWidget(rimuovi, Qt::AlignRight);

    mainLayout = new QHBoxLayout;
    mainLayout->addLayout(griglia);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    this->setStyleSheet(
        "QGroupBox {"
            "font-size: 16pt;"
            "color: #007bff;"
            "border: 1px solid #d7d6d5;"
            "border-radius: 10px;"
            "margin-top: 28px;"
            "padding-left: 5px;"
        "}"
        "QGroupBox::title {"
            "subcontrol-origin: margin;"
        "}"
    );

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
        icona->setPixmap((new QIcon(":/resources/resources/asset/icona_sensore_"+sensor->getTipo()))->pixmap(64,64));
    }

    //aggiorna item in mostra_sensori
    void* itemPointerVoid = property("PuntatoreItem").value<void*>();
    QListWidgetItem* item = static_cast<QListWidgetItem*>(itemPointerVoid);
    item->setText(title());
    item->setToolTip("Stanza: "+stanza->text()+"\nData creazione: "+dataC->text());
    item->setData(Qt::UserRole, QVariant::fromValue(sensor));

    const QIcon* icona = new QIcon(":/resources/resources/asset/icona_sensore_"+sensor->getTipo());
    item->setIcon(*icona);

    //aggiorna chartbox
    visitor_grafico* visitor = new visitor_grafico;
    sensor->accept(visitor);
    chartBox* box_grafo = visitor->getWidget();
    emit modificaChartContainer(box_grafo);

    //aggiorna file
    try{
        sensor->aggiorna_file(oldName);
    }
    catch(const std::runtime_error &ex){
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Errore");
        msgBox.setText("Errore nell'aggiornamento del file.");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStyleSheet(
                    "QMessageBox { background-color: white;}"
                    "QLabel {color: #007bff;}"
                    "QPushButton{"
                    "   border-radius: 19px;"
                    "   padding: 2px;"
                    "   color: #007bff;"
                    "   background-color: white;"
                    "   border: 1px solid grey;"
                    "}"
                    "QPushButton:hover {"
                    "   background-color: #ecf2fc;"
                    "}"
                    "QPushButton:pressed {"
                    "   background-color: #d5e2f7;"
                    "}"
        );
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        okButton->setMinimumHeight(38);
        msgBox.exec();
    }
}

void sensorBox::onRimuoviClicked() {

    //finestra di conferma
    QMessageBox msgBox;
    msgBox.setWindowTitle("Conferma eliminazione");
    msgBox.setText("Vuoi eliminare questo sensore? Non sarà più recuperabile.");
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setStyleSheet(
                "QMessageBox { background-color: white;}"
                "QLabel {color: #007bff;}"
                "QPushButton{"
                "   min-height: 38px;"
                "   border-radius: 19px;"
                "   padding: 2px;"
                "   color: #007bff;"
                "   background-color: white;"
                "   border: 1px solid grey;"
                "}"
                "QPushButton:hover {"
                "   background-color: #ecf2fc;"
                "}"
                "QPushButton:pressed {"
                "   background-color: #d5e2f7;"
                "}"
    );

    // Mostra la QMessageBox e ottieni la risposta
    QMessageBox::StandardButton reply = static_cast<QMessageBox::StandardButton>(msgBox.exec());

    if (reply == QMessageBox::No) return;

    void* sensorPointerVoid = property("PuntatoreSensore").value<void*>();
    sensore* sensor = static_cast<sensore*>(sensorPointerVoid);
    if(!sensor) return;//se non c'è alcun sensore caricato sul box non fa niente

    //cancella il sensore dal file
    QString percorso = sensor->getCollezione()->getPath();
    QFile file(percorso);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Errore");
        msgBox.setText("Impossibile trovare il file del sensore.");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStyleSheet(
                    "QMessageBox { background-color: white;}"
                    "QLabel {color: #007bff;}"
                    "QPushButton{"
                    "   border-radius: 19px;"
                    "   padding: 2px;"
                    "   color: #007bff;"
                    "   background-color: white;"
                    "   border: 1px solid grey;"
                    "}"
                    "QPushButton:hover {"
                    "   background-color: #ecf2fc;"
                    "}"
                    "QPushButton:pressed {"
                    "   background-color: #d5e2f7;"
                    "}"
        );
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        okButton->setMinimumHeight(38);
        msgBox.exec();
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
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Errore");
        msgBox.setText("Errore nell'eliminazione del sensore.");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStyleSheet(
                    "QMessageBox { background-color: white;}"
                    "QLabel {color: #007bff;}"
                    "QPushButton{"
                    "   border-radius: 19px;"
                    "   padding: 2px;"
                    "   color: #007bff;"
                    "   background-color: white;"
                    "   border: 1px solid grey;"
                    "}"
                    "QPushButton:hover {"
                    "   background-color: #ecf2fc;"
                    "}"
                    "QPushButton:pressed {"
                    "   background-color: #d5e2f7;"
                    "}"
        );
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        okButton->setMinimumHeight(38);
        msgBox.exec();
            return;
    }
    QTextStream out(&file);
    out<<nuovo_contenuto;
    file.close();

    //rimuove l'item dalla lista ui->mostra_sensori
    void* itemPointerVoid = property("PuntatoreItem").value<void*>();
    QListWidgetItem* item = static_cast<QListWidgetItem*>(itemPointerVoid);
    emit removeItem(item);

    //svuota la chartBox
    emit resetChartBox();

    //rimuove il sensore dalla collezione
    sensor->getCollezione()->rm_sensore(sensor);

    //distrugge il sensore vero e proprio
    delete sensor;

    //svuota la sensorBox
    reset();

}
