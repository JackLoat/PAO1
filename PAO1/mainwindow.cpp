#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sensori.h"
#include "sensorBox.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("SpiderSensors");

    //tentativo di connettere sensorBox on rimuovi clicked alla list mostra_sensori
    connect(ui->box_sensore, &sensorBox::removeItem, this, &MainWindow::onRemoveItem);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sensorClicked(QListWidgetItem* item){
    //riabilita i pulsanti
    ui->box_sensore->modifica->setDisabled(false);
    ui->box_sensore->rimuovi->setDisabled(false);

    sensore* sensor = item->data(Qt::UserRole).value<sensore*>();

    //mostra i dati del sensore su un'altra label
    //modifica in modo da mostrare i dati sulla groupbox "box_sensore"
    ui->box_sensore->setTitle(sensor->getNome());

    ui->box_sensore->tipo->setText(sensor->getTipo());
    ui->box_sensore->dataC->setText(sensor->getDataC().toString("dd/MM/yyyy"));
    ui->box_sensore->stanza->setText(sensor->getStanza());
    ui->box_sensore->collezione->setText(sensor->getCollezione()->getNome());

    QPixmap pixmap("/home/student/Desktop/asset/icon_sensor.jpeg");    //MODIFICA PRIMA DELLA CONSEGNA!!!
    QLabel* lab_icona = ui->box_sensore->icona;
    lab_icona->setPixmap(pixmap.scaled(lab_icona->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    ui->box_sensore->setProperty("PuntatoreSensore", QVariant::fromValue(static_cast<void*>(sensor)));
    ui->box_sensore->setProperty("PuntatoreItem", QVariant::fromValue(static_cast<void*>(item)));
    //qDebug()<<"puntatore item: "<<item;
}

void MainWindow::on_carica_collezione_clicked(){

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

    ui->mostra_sensori->clear();
    ui->box_sensore->reset();

    //estrarre nome collezione
    QFileInfo fileInfo(path);
    QString nome_collezione = fileInfo.completeBaseName();

    ui->nome_collezione->setText(nome_collezione);

    collezione* collPtr = new collezione(nome_collezione,path);

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
        else if(tipo=="Gumo") sensor = new sensore_fumo(nome,dataCreazione,tipo,stanza,collPtr);
        else if(tipo=="Aria") sensor = new sensore_aria(nome,dataCreazione,tipo,stanza,collPtr);
        else sensor = new sensore_vent(nome,dataCreazione,tipo,stanza,collPtr);

        QListWidgetItem* item = new QListWidgetItem();
        sensor->sensorToWI(*item);

        collPtr->add_sensore(sensor);

        ui->mostra_sensori->addItem(item);
    }

    file.close();

    connect(ui->mostra_sensori, &QListWidget::itemClicked, this, &MainWindow::on_sensorClicked);
}

void MainWindow::onRemoveItem(QListWidgetItem* item){

    //qDebug() << "segnale removeitem ricevuto";

    if(ui->mostra_sensori && item){
        int row = ui->mostra_sensori->row(item);
        if(row!=-1) delete ui->mostra_sensori->takeItem(row);
        //qDebug() << "takeitem eseguito";
    }
    //qDebug() << "fine on remove item";
}

void MainWindow::on_Aggiungi_sensore_clicked(){

    nsDialog* ns = new nsDialog(this);

    sensore* sensor;
    collezione* coll;

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
