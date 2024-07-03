#include "sensorBox.h"


sensorBox::sensorBox(QWidget *parent)
    : QGroupBox(parent) {
    tipo = new QLabel("Tipo: ", this);
    dataC = new QLabel("Data C: ", this);
    collezione = new QLabel("Collezione: ", this);
    stanza = new QLabel("Stanza: ", this);
    icona = new QLabel("Icona", this);

    modifica = new QPushButton("Modifica", this);
    rimuovi = new QPushButton("Rimuovi", this);

    QVBoxLayout *labelLayout = new QVBoxLayout;
    labelLayout->addWidget(tipo);
    labelLayout->addWidget(dataC);
    labelLayout->addWidget(collezione);
    labelLayout->addWidget(stanza);
    labelLayout->addWidget(icona);

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(modifica);
    buttonLayout->addWidget(rimuovi);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(labelLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connectButtons();

}

void sensorBox::reset(){
    setTitle("Nome sensore");
    tipo->setText("Tipo: ");
    dataC->setText("Data C: ");
    stanza->setText("Stanza: ");
    collezione->setText("Collezione: ");
    QPixmap emptyPixMap;
    icona->setPixmap(emptyPixMap);
    //reset propery
    setProperty("PuntatoreSensore",QVariant());
}

void sensorBox::connectButtons() {
    connect(modifica, &QPushButton::clicked, this, &sensorBox::on_modifica_clicked);
    connect(rimuovi, &QPushButton::clicked, this, &sensorBox::onRimuoviClicked);
}

void sensorBox::on_modifica_clicked() {
    // Azioni da eseguire quando button1 è cliccato
    qDebug() << "Button 1 clicked!";
}

void sensorBox::onRimuoviClicked() {

    qDebug() <<"rimuovi sensore premuto";

    // Azioni da eseguire quando button2 è cliccato
    //qDebug() << "Button 2 clicked!";

    void* sensorPointerVoid = property("PuntatoreSensore").value<void*>();
    sensore* sensor = static_cast<sensore*>(sensorPointerVoid);

    if(!sensor) return;//se non c'è alcun sensore caricato sul box non fa niente

    //cancella sensore dalla collezione
    //cancella sensore allocato in memoria
    //cancella sensore dal file .txt
    //resetta sensorBox
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

    sensor->getCollezione()->rm_sensore(sensor);
    delete sensor;
    reset();


    reset();
}
