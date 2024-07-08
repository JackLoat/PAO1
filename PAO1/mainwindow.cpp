#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("SpiderSensors");

    carica_collezione = new QPushButton("Carica collezione",this);
    nome_collezione = new QLabel("Nome collezione",this);
    mostra_sensori = new QListWidget(this);
    aggiungi_sensore = new QPushButton("Aggiungi sensore",this);

    box_sensore = new sensorBox(this);
    chartContainer = new QWidget(this);

    //QVBoxLayout* destra = new QVBoxLayout();
    QSplitter* rightSplitter = new QSplitter(Qt::Vertical, this);
    rightSplitter->addWidget(box_sensore);
    rightSplitter->addWidget(chartContainer);

    QList<int> rightSizes;
    rightSizes << height()/2 << height()/2;
    rightSplitter->setSizes(rightSizes);

    QVBoxLayout* sinistra = new QVBoxLayout();
    sinistra->addWidget(carica_collezione);
    /*
    QHBoxLayout* browseLayout = new QHBoxLayout(this);
    browseLayout->addWidget(ui->textBrowser);
    browseLayout->addWidget(ui->Cerca_sensore);
    */
    //sinistra->addLayout(browseLayout);
    sinistra->addWidget(nome_collezione);
    sinistra->addWidget(mostra_sensori);
    sinistra->addWidget(aggiungi_sensore);

    //contenitore per la colonna sinistra
    QWidget* leftWidget = new QWidget;
    leftWidget->setLayout(sinistra);
    //contenitore per la colonna destra
    QWidget* rightWidget = new QWidget;
    QVBoxLayout* rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->addWidget(rightSplitter);

    //splitter per dividere la colonna sinistra dal resto della finestra
    QSplitter* splitter = new QSplitter(this);
    splitter->addWidget(leftWidget);
    splitter->addWidget(rightWidget);
    QList<int> sizes;
    sizes << width()/3 << 2*width()/3;
    splitter->setSizes(sizes);

    //mainLayout->addLayout(sinistra);
    //mainLayout->addLayout(destra);

    //crea layout
/*
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    //setCentralWidget(splitter);
    mainLayout->addWidget(splitter);
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
*/

    ui->centralwidget->setLayout(new QVBoxLayout);
    ui->centralwidget->layout()->addWidget(splitter);

    //connetti tutti i pulsanti
    //tentativo di connettere sensorBox on rimuovi clicked alla list mostra_sensori
    connect(box_sensore, &sensorBox::removeItem, this, &MainWindow::onRemoveItem);
    connect(carica_collezione, &QPushButton::clicked, this, &MainWindow::onCarica_collezione_clicked);
    connect(aggiungi_sensore, &QPushButton::clicked, this, &MainWindow::onAggiungi_sensore_clicked);
    connect(mostra_sensori, &QListWidget::itemClicked, this, &MainWindow::on_sensorClicked);
    connect(box_sensore, &sensorBox::modificaChartContainer, this, &MainWindow::onModificaChartContainer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sensorClicked(QListWidgetItem* item){
    //riabilita i pulsanti
    box_sensore->modifica->setDisabled(false);
    box_sensore->rimuovi->setDisabled(false);

    //recupera sensore dalle informazioni dell'item
    sensore* sensor = item->data(Qt::UserRole).value<sensore*>();

    //mostra i dati del sensore sulle label
    box_sensore->setTitle(sensor->getNome());

    box_sensore->tipo->setText(sensor->getTipo());
    box_sensore->dataC->setText(sensor->getDataC().toString("dd/MM/yyyy"));
    box_sensore->stanza->setText(sensor->getStanza());
    box_sensore->collezione->setText(sensor->getCollezione()->getNome());

    QPixmap pixmap("/home/student/Desktop/asset/icon_sensor.jpeg");    //MODIFICA PRIMA DELLA CONSEGNA!!!
    QLabel* lab_icona = box_sensore->icona;
    lab_icona->setPixmap(pixmap.scaled(lab_icona->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    //salva un puntatore al sensore e all'item nelle proprietà
    box_sensore->setProperty("PuntatoreSensore", QVariant::fromValue(static_cast<void*>(sensor)));
    box_sensore->setProperty("PuntatoreItem", QVariant::fromValue(static_cast<void*>(item)));
    //qDebug()<<"puntatore item: "<<item;

    //chiama il setup del mostra_grafico e aggiorna il layout per la boxGrafo che hai ottenuto
    qDebug()<<"on sensor clicked chiama sensor->setup_box_grafo";
    chartBox* box_grafo = sensor->setup_box_grafo();
    //const chartBox& box_grafo = new chartBox(this); //rimuovi quando viene implementata setup_box_grafo
    //chartBox* x = const_cast<chartBox*>(&box_grafo);

    //qDebug()<<"aggiungo il layout al widget";
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(box_grafo);
    if(chartContainer->layout() != nullptr){
        QLayout* oldLayout = chartContainer->layout();
        QLayoutItem * item;
        while((item = oldLayout->takeAt(0)) != nullptr){
            if (item->widget()){
                item->widget()->setParent(nullptr);
            }
            delete item;
        }
        delete oldLayout;
    }
    chartContainer->setLayout(layout);

}

void MainWindow::onCarica_collezione_clicked(){

    QString initialPath = "/home/student/Desktop/cartella_collezioni"; //MODIFICA PRIMA DELLA CONSEGNA!!!
    QString nome_file = QFileDialog::getOpenFileName(this,tr("Seleziona file"), initialPath, tr("Text Files (*.txt);;All Files (*)"));

    fileToWidgetList(nome_file);
}

void MainWindow::fileToWidgetList(const QString& path){
    if (path.isEmpty())
        return;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, tr("Error"), tr("Impossibile aprire il file: ") + file.errorString());
        return;
    }

    mostra_sensori->clear();
    box_sensore->reset();

    qDebug()<<"in teoria adesso svuoto la chart box";
    if(chartContainer->layout() != nullptr){
        QLayout* oldLayout = chartContainer->layout();
        QLayoutItem *item;
        while((item = oldLayout->takeAt(0)) != nullptr){
            delete item->widget();
            delete item;
        }
        delete oldLayout;
    }

    //estrarre nome collezione
    QFileInfo fileInfo(path);
    QString nome_coll = fileInfo.completeBaseName();

    nome_collezione->setText(nome_coll);

    collezione* collPtr = new collezione(nome_coll,path);

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();

        //parsing linea
        QStringList fields = line.split(",");
        if(fields.size()<4){
            QMessageBox::warning(this, tr("Error"), tr("Formato file errato"));
            return;
        }

        QString stanza = fields[0].trimmed();
        QString nome = fields[1].trimmed();
        QString tipo = fields[2].trimmed();
        QDate dataCreazione = QDate::fromString(fields[3].trimmed(),"yyyy-MM-dd");

        sensore *sensor;

        if(tipo=="Temperatura") sensor = new sensore_temp(nome,dataCreazione,tipo,stanza,collPtr);
        else if(tipo=="Fumo") sensor = new sensore_fumo(nome,dataCreazione,tipo,stanza,collPtr);
        else if(tipo=="Aria") sensor = new sensore_aria(nome,dataCreazione,tipo,stanza,collPtr);
        else sensor = new sensore_vent(nome,dataCreazione,tipo,stanza,collPtr);

        QListWidgetItem* item = new QListWidgetItem();
        sensor->sensorToWI(*item);

        collPtr->add_sensore(sensor);

        mostra_sensori->addItem(item);
    }

    file.close();

    //connect(mostra_sensori, &QListWidget::itemClicked, this, &MainWindow::on_sensorClicked);
}

void MainWindow::onRemoveItem(QListWidgetItem* item){

    //qDebug() << "segnale removeitem ricevuto";

    if(mostra_sensori && item){
        int row = mostra_sensori->row(item);
        if(row!=-1) delete mostra_sensori->takeItem(row);
        //qDebug() << "takeitem eseguito";
    }
    //qDebug() << "fine on remove item";
}

void MainWindow::onAggiungi_sensore_clicked(){

    nsDialog* ns = new nsDialog(this);

    //sensore* sensor;
    //collezione* coll;

    //durante l'esecuzione vengono modificati i campi del qdialog
    //l'override di nsDialog::accept() ha già controllato che
    //non esista un altro sensore con lo stesso nome nello stesso file.

    //duarente exec() vengono eseguiti carica_collezione e/o nuova_collezione
    //se l'utente preme prima uno e poi l'altro non farà altro che sovrascrivere path_collezione

    //se l'utente sceglie "nuova_collezione" e conferma, l'override di accept crea il file

    //se l'utente fa annulla bisogna eliminare eventuali file creati
    //controlla se ns->getPathColl() (che per forza esiste perché se n'è occupato accept()) è un file.txt vuoto
    //se sì elimina il file,  se no fa return e basta
    if(ns->exec() == QDialog::Rejected){

        QFile file(ns->getPathColl());

        if(!file.exists()){
            qDebug()<<"il file non esiste: " <<ns->getPathColl();
        }

        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug()<<"Impossibile aprire il file per la lettura:"<<file.errorString();
        }

        QTextStream in(&file);
        QString content = in.readAll();
        file.close();
        if(content.isEmpty()){
            if(!file.remove()){
                qDebug()<<"Impossibile eliminare il file:"<<file.errorString();
            }
        }

        return;
    }

    //se l'utente accetta:
    //non serve creare collezione o inizializzare il sensore.
    //è sufficiente salvare la stringa del il sensore in memoria, poi "fileToWidgetList" pensa a ricreare il sensore da zero

    else{

        QString path = ns->getPathColl();
        //salva il sensore nel file.txt e carica la collezione sul mostra_sensori

        QString stringa = ns->getStanza()+","+ns->getNome()+","+ns->getTipo()+","+QDate::currentDate().toString("yyyy-MM-dd");

        QFile file(path);
        if(file.open(QIODevice::Append | QIODevice::Text)){
            QTextStream out(&file);
            out << stringa<<"\n";
            file.close();
        }
        else{
            qWarning()<<"Could not open file:"<<path;
        }
        //carica la collezione sul mostra_sensori
        fileToWidgetList(path);
    }
}

void MainWindow::onModificaChartContainer(chartBox* newChartBox){
    qDebug()<<"mainwindow esegue modifica container";
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(newChartBox);
    if(chartContainer->layout() != nullptr){
        QLayout* oldLayout = chartContainer->layout();
        QLayoutItem * item;
        while((item = oldLayout->takeAt(0)) != nullptr){
            if (item->widget()){
                item->widget()->setParent(nullptr);
            }
            delete item;
        }
        delete oldLayout;
    }
    chartContainer->setLayout(layout);
}


/*
void MainWindow::on_Genera_dati_clicked()
{
    //bisogna in qualche modo modificare i campi del sensore per poter generare i dati



    int n = PeriodoDati[ui->comboDati->currentText()];

    void* sensorVoid = ui->box_sensore->property("PuntatoreSensore").value<void*>();
    sensore* sensor = static_cast<sensore*>(sensorVoid);
    if(dynamic_cast<sensore_fumo*>(sensor)){
        QVector<bool> vettore_trigger;
        sensore_fumo* sf = static_cast<sensore_fumo*>(sensor);
        sf->genera_dati(vettore_trigger,n);
        //genera widget grafico adatto
    }
    else{//il tipo dinamico del sensore è o deriva da sensore_temp
            //richiedi input min, max
        QVector<double> vettore_dati;
        double min; //=...
        double max; //=...
        if(dynamic_cast<sensore_aria*>(sensor)){//sensor è aria o vento
            //richiedi input soglia
            double soglia; //=...
            QVector<bool> vettore_trigger;

            if(dynamic_cast<sensore_vent*>(sensor)){//sensor è vento
                QVector<double> vettore_direz;
                sensore_vent* sv = static_cast<sensore_vent*>(sensor);
                sv->genera_dati(vettore_dati,vettore_trigger,vettore_direz,n,min,max,soglia);
                //genera widget grafico adatto
            }
            else{//sensor è aria
                sensore_aria* sa = static_cast<sensore_aria*>(sensor);
                sa->genera_dati(vettore_dati,vettore_trigger,n,min,max,soglia);
                //genera widget grafico adatto
            }
        }
        else{//sensor è temp
            sensore_temp* st = static_cast<sensore_temp*>(sensor);
            st->genera_dati(vettore_dati,n,min,max);
            //genera widget grafico adatto
        }
    }
}

*/
