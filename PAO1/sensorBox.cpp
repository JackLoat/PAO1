#include "sensorBox.h"


sensorBox::sensorBox(QWidget *parent)
    : QGroupBox(parent) {
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

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(headerLayout);
    mainLayout->addLayout(labelLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connectButtons();
}

void sensorBox::reset(){
    setTitle("Nome sensore");
    tipo->setText("");
    dataC->setText("");
    stanza->setText("");
    collezione->setText("");
    QPixmap emptyPixMap;
    qDebug()<<"setto empty pixmap sull'icona della sensorBox";
    icona->setPixmap(emptyPixMap);
    //reset propery
    setProperty("PuntatoreSensore",QVariant());
    setProperty("PuntatoreItem",QVariant());
    //disabilita pulsanti
    modifica->setDisabled(true);
    rimuovi->setDisabled(true);
}

void sensorBox::connectButtons() {
    connect(modifica, &QPushButton::clicked, this, &sensorBox::on_modifica_clicked);
    connect(rimuovi, &QPushButton::clicked, this, &sensorBox::onRimuoviClicked);
}

void sensorBox::on_modifica_clicked() {
    qDebug()<<"inizia on_modifica_clicked";
    QString oldName = title();

    editDialog ed(this);
    ed.setLabelsText(title(), stanza->text(), tipo->text());



    if(ed.exec() == QDialog::Accepted) {
        setTitle(ed.getNome());
        stanza->setText(ed.getStanza());
        tipo->setText(ed.getTipo());
        //dopo verrà aggiornato il puntatore se il tipo sensore è cambiato
        //viene modificata dopo anche l'icona
    }
    else return;

    //aggiorna sensore allocato nello heap
    void* sensorVoid = property("PuntatoreSensore").value<void*>();
    sensore* sensor = static_cast<sensore*>(sensorVoid);
    sensor->setNome(title());
    sensor->setStanza(stanza->text());

    qDebug()<<sensor->getIcona();

    //gestione tipo sensore
    if(sensor->getTipo() != tipo->text()){
        sensor->setTipo(tipo->text());

        //crea un nuovo sensore del tipo giusto a partire dai dati del primo
        sensore* newSensor;
        if(tipo->text() == "Fumo") newSensor = new sensore_fumo(*sensor);
        else if(tipo->text() == "Temperatura") newSensor = new sensore_temp(*sensor);
        else if(tipo->text() == "Aria") newSensor = new sensore_aria(*sensor);
        else newSensor = new sensore_vent(*sensor);

        qDebug()<<"costruito new sensor";

        //gestisci aggiornamento mostra_sensori
        //item->setData(Qt::UserRole, QVariant::fromValue();
        //oppuer
        //delete sensor; sensor = newSensor; e poi fuori dall'if si mette a prescindere sensor su setData();
        sensor->getCollezione()->rm_sensore(sensor);
        sensor->getCollezione()->add_sensore(newSensor);

        qDebug()<<sensor->getIcona();

        qDebug()<<"Porcodio";

        if(sensor){
            qDebug()<<"gianni";
            delete sensor;
        }

        qDebug()<<"diocane";

        sensor = newSensor;

        qDebug()<<"setproperty della sensor box";

        //gestisci aggiornamento sensor_box
        //bisogna aggiornare solo il puntatore con setProperty("PntatoreSensore")
        this->setProperty("PuntatoreSensore", QVariant::fromValue(static_cast<void*>(sensor)));

        //settare icona sensor_box
        icona->setPixmap(sensor->getIcona()->pixmap(64,64));

        qDebug()<<sensor->getIcona();

        //gestisci aggiornamento chart_box
        //forse si arrangia setup_box_grafo a distruggere quello vecchio e costruire quello nuovo una volta modificato sensor
    }

    qDebug()<<"finita parentesi del cambio tipo";
    //aggiorna item in mostra_sensori
    void* itemPointerVoid = property("PuntatoreItem").value<void*>();
    QListWidgetItem* item = static_cast<QListWidgetItem*>(itemPointerVoid);
    item->setText(title());
    item->setToolTip("Stanza: "+stanza->text()+"\nData creazione: "+dataC->text());
    //CAMBIA ICONA
    //oppure chiama sensortoWi su newSensor (o sensor=newSensor), passando item come parametro
    qDebug()<<"1";
    item->setIcon(*(sensor->getIcona()));
    qDebug()<<"2";
    //aggiorna icona della sensorbox
    qDebug()<<sensor->getIcona();
    //icona->setPixmap(sensor->getIcona()->pixmap(64,64));
    qDebug()<<"3";
    item->setData(Qt::UserRole, QVariant::fromValue(sensor));

       //aggiorna chartbox
    //prova semplicemente richiamando "setup_box_grafo".
    chartBox* box_grafo = sensor->setup_box_grafo();

    //modifica il layout di mainwindow->chartContainer:
    //opzione a) meglio non includere mainwindow.h
    //opzione b)serve farsu oassare un puntatore a chartcontainer
    //opzione c)chiama una qualche funzione di mainwindow che modifica la chartBox
                    //si emette un segnale
    emit modificaChartContainer(box_grafo);

    qDebug()<<"4";
    //aggiorna riga nel file.txt
    sensor->aggiorna_file(oldName);
    qDebug()<<"fine modifica";
}

void sensorBox::onRimuoviClicked() {
    //finestra di conferma
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Conferma eliminazione", "Vuoi eliminare questo sensore? Non sarà più recuperabile", QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::No) return;

    //qDebug() <<"rimuovi sensore premuto";

    // Azioni da eseguire quando button2 è cliccato
    //qDebug() << "Button 2 clicked!";

    void* sensorPointerVoid = property("PuntatoreSensore").value<void*>();
    sensore* sensor = static_cast<sensore*>(sensorPointerVoid);

    if(!sensor) return;//se non c'è alcun sensore caricato sul box non fa niente

    //cancella sensore dalla collezione
    //cancella sensore allocato in memoria
    //cancella sensore dal file .txt
    //resetta sensorBox
    //resetta chartBox
    QString percorso = sensor->getCollezione()->getPath();
    QFile file(percorso);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Impossibile aprire il file " << percorso;
            return;
    }

    QString target = sensor->getNome();
    QTextStream in(&file);
    QString nuovo_contenuto;
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList parts = line.split(',',Qt::SkipEmptyParts);

        if (parts.size()>=4 && parts[1].trimmed()==target){
            continue;
        }

        nuovo_contenuto += line +"\n";
    }
    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            qDebug() << "Impossibile aprire il file per la scrittura" << percorso;
            return;
    }

    QTextStream out(&file);
    out<<nuovo_contenuto;

    file.close();

    //qDebug()<<"Riga eliminata dal file CSV con successo.";

    //rimuovi l'item dalla lista ui->mostra_sensori
    void* itemPointerVoid = property("PuntatoreItem").value<void*>();
    QListWidgetItem* item = static_cast<QListWidgetItem*>(itemPointerVoid);

    //prova a usare elemento parent della sensorBox per accedere a ui, quindi da ui accedere a mostra_sensori
    /*
    MainWindow* mw = qobject_cast<MainWindow*>(this->parentWidget());

    if (mw){
        mw->ui->mostra_sensori->takeItem()
    }
    */

    //qDebug() <<"puntatoreItem: "<<item;

    //prova emettendo il segnale
    emit removeItem(item);

    //qDebug() <<"emesso removeItem";

    emit resetChartBox();

    sensor->getCollezione()->rm_sensore(sensor);
    delete sensor;
    reset();
}
