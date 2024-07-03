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

    if (nome_file.isEmpty())
        return;

    QFile file(nome_file);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, tr("Error"), tr("Impossibile aprire il file: ") + file.errorString());
        return;
    }

    ui->mostra_sensori->clear();
    ui->box_sensore->reset();

    //estrarre nome collezione
    QFileInfo fileInfo(nome_file);
    QString nome_collezione = fileInfo.completeBaseName();

    ui->nome_collezione->setText(nome_collezione);

    collezione* collPtr = new collezione(nome_collezione,nome_file);

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

        if(tipo=="temperatura") sensor = new sensore_temp(nome,dataCreazione,tipo,stanza,collPtr);
        else if(tipo=="fumo") sensor = new sensore_fumo(nome,dataCreazione,tipo,stanza,collPtr);
        else if(tipo=="aria") sensor = new sensore_aria(nome,dataCreazione,tipo,stanza,collPtr);
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

