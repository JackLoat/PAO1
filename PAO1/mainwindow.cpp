#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("SpiderSensors");
    showMaximized();

    carica_collezione = new QPushButton("Carica collezione",this);
    nome_collezione = new QLabel("Nome collezione",this);
    rimuovi_collezione = new QPushButton("Rimuovi collezione", this);
    rimuovi_collezione->setDisabled(true);
    barra_ricerca = new QLineEdit(this);
    barra_ricerca->setClearButtonEnabled(true);
    barra_ricerca->setPlaceholderText("Ricerca...");
    mostra_sensori = new QListWidget(this);
    aggiungi_sensore = new QPushButton("Aggiungi sensore",this);

    box_sensore = new sensorBox(this);
    chartContainer = new QWidget(this);

    QSplitter* rightSplitter = new QSplitter(Qt::Vertical, this);
    rightSplitter->addWidget(box_sensore);
    rightSplitter->addWidget(chartContainer);

    QList<int> rightSizes;
    rightSizes << height()/3 << height()*2/3;
    rightSplitter->setSizes(rightSizes);

    QVBoxLayout* sinistra = new QVBoxLayout();
    sinistra->addWidget(carica_collezione);
    QHBoxLayout* layout = new QHBoxLayout();
        layout->addWidget(nome_collezione);
        layout->addWidget(rimuovi_collezione);
    sinistra->addLayout(layout);
    sinistra->addWidget(barra_ricerca);

    sinistra->addWidget(mostra_sensori);
    sinistra->addWidget(aggiungi_sensore);

    QWidget* leftWidget = new QWidget;
    leftWidget->setLayout(sinistra);

    QWidget* rightWidget = new QWidget;
    QVBoxLayout* rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->addWidget(rightSplitter);

    QSplitter* splitter = new QSplitter(this);
    splitter->addWidget(leftWidget);
    splitter->addWidget(rightWidget);
    QList<int> sizes;
    sizes << width()/3 << 2*width()/3;
    splitter->setSizes(sizes);

    ui->centralwidget->setLayout(new QVBoxLayout);
    ui->centralwidget->layout()->addWidget(splitter);

    connect(box_sensore, &sensorBox::removeItem, this, &MainWindow::onRemoveItem);
    connect(box_sensore, &sensorBox::resetChartBox, this, &MainWindow::resetChartBox);
    connect(carica_collezione, &QPushButton::clicked, this, &MainWindow::onCarica_collezione_clicked);
    connect(aggiungi_sensore, &QPushButton::clicked, this, &MainWindow::onAggiungi_sensore_clicked);
    connect(mostra_sensori, &QListWidget::itemClicked, this, &MainWindow::on_sensorClicked);
    connect(box_sensore, &sensorBox::modificaChartContainer, this, &MainWindow::onModificaChartContainer);
    connect(barra_ricerca, &QLineEdit::textChanged, this, &MainWindow::onRicerca);
    connect(rimuovi_collezione, &QPushButton::clicked, this, &MainWindow::onRimuoviCollezioneClicked);

    QShortcut* br_esc = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(br_esc, &QShortcut::activated, barra_ricerca, &QLineEdit::clear);

}


MainWindow::~MainWindow()
{
    delete carica_collezione;
    delete nome_collezione;
    delete rimuovi_collezione;
    delete mostra_sensori;
    delete aggiungi_sensore;
    delete box_sensore;
    delete chartContainer;
    delete barra_ricerca;
    delete ui;

}


void MainWindow::onRicerca(){

    QString nome = barra_ricerca->text();
    for(int i=0; i<mostra_sensori->count(); ++i){
        QListWidgetItem* item = mostra_sensori->item(i);
        bool matchText = item->text().contains(nome, Qt::CaseInsensitive);
        bool matchTT = item->toolTip().contains(nome, Qt::CaseInsensitive);
        bool match = matchText || matchTT;
        item->setHidden(!match);
    }

}


void MainWindow::onRimuoviCollezioneClicked(){

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Conferma eliminazione", "Vuoi eliminare questa collezione? Non sarà più recuperabile", QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::No) return;

    collezione* collPtr = reinterpret_cast<collezione*>(mostra_sensori->property("puntatoreCollezione").value<void*>());

    //elimina file
    QString path = collPtr->getPath();
    if(!QFile::remove(path)){
        QMessageBox::critical(this, "Errore","Impossibile eliminare il file contenente la collezione.");
        return;
    }

    //reset interfaccia
    box_sensore->reset();
    resetChartBox();
    mostra_sensori->clear();
    mostra_sensori->setProperty("puntatoreCollezione", QVariant());
    rimuovi_collezione->setDisabled(true);
    nome_collezione->setText("Nome collezione");

    //distruggi collezione
    delete collPtr;

}


void MainWindow::on_sensorClicked(QListWidgetItem* item){
    //mostra i dati del sensore selezionato sulla sensorBox

    //riabilita i pulsanti
    box_sensore->disabilitaModifica(false);
    box_sensore->disabilitaRimuovi(false);

    //recupera sensore dalle informazioni dell'item
    sensore* sensor = item->data(Qt::UserRole).value<sensore*>();

    //mostra i dati del sensore sulle label della sensorBox
    box_sensore->setTitle(sensor->getNome());
    box_sensore->setTipo(sensor->getTipo());
    box_sensore->setData(sensor->getDataC().toString("dd/MM/yyyy"));
    box_sensore->setStanza(sensor->getStanza());
    box_sensore->setColl(sensor->getCollezione()->getNome());
    QPixmap pixmap = sensor->getIcona()->pixmap(64,64);
    box_sensore->setIcona(pixmap);

    //salva un puntatore al sensore e all'item nelle proprietà della sensorBox
    box_sensore->setProperty("PuntatoreSensore", QVariant::fromValue(static_cast<void*>(sensor)));
    box_sensore->setProperty("PuntatoreItem", QVariant::fromValue(static_cast<void*>(item)));

    //chiama il setup del mostra_grafico e aggiorna il layout con la chartBox ottenuta
    chartBox* box_grafo = sensor->setup_box_grafo();
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(box_grafo);
    resetChartBox();
    chartContainer->setLayout(layout);

}


bool checkFormat(const QString& path){
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return false;
    }

    QStringList list = {"Fumo","Temperatura","Aria","Vento"};
    QTextStream in(&file);
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList fields = line.split(",", Qt::SkipEmptyParts);
        if (fields.size()!=4 ||
            !QDate::fromString(fields[3],"yyyy-MM-dd").isValid() ||
            !list.contains(fields[2])){
            return false;
        }
    }
    file.close();
    return true;

}


void MainWindow::onCarica_collezione_clicked(){

    QDir initialDir = QDir::home();
    initialDir.cdUp();
    QString initialPath = initialDir.absolutePath();
    QString nome_file = QFileDialog::getOpenFileName(this,tr("Seleziona file"), initialPath, tr("Text Files (*.txt)"));

    if(nome_file.isEmpty()){    //se l'utente esce senza scegliere un file si ritorna senza eseguire niente
        return;
    }

    //ulteriore controllo che il file esista e abbia estensione corretta
    QFile file(nome_file);
    if(!file.exists()){
        QMessageBox::critical(this, "Errore","Il file selezionato non esiste");
        return;
    }

    QFileInfo fileInfo(nome_file);
    QString estensione = fileInfo.suffix();
    if (estensione.compare("txt", Qt::CaseInsensitive) != 0) {
        QMessageBox::warning(this, "Warning","Il file scelto deve essere in formato '.txt'.");
        return;
    }

    if(!checkFormat(nome_file)){
        QMessageBox::warning(this, "Errore","Il file scelto non è nel formato corretto.");
        return;
    }

    barra_ricerca->setText("");

    fileToWidgetList(nome_file);

}


void MainWindow::fileToWidgetList(const QString& path){

    if (path.isEmpty()) return;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, tr("Error"), tr("Impossibile aprire il file: ") + file.errorString());
        return;
    }

    mostra_sensori->clear();
    delete reinterpret_cast<collezione*>(mostra_sensori->property("puntatoreCollezione").value<void*>());
    mostra_sensori->setProperty("puntatoreCollezione", QVariant());
    rimuovi_collezione->setDisabled(true);
    box_sensore->reset();
    resetChartBox();

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
        if(fields.size()!=4){
            QMessageBox::warning(this, tr("Error"), tr("Formato file errato"));
            nome_collezione->setText("Nome collezione");
            delete collPtr;
            file.close();
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
    mostra_sensori->setProperty("puntatoreCollezione",QVariant::fromValue(reinterpret_cast<void*>(collPtr)));

    file.close();

    rimuovi_collezione->setDisabled(false);

}


void MainWindow::onRemoveItem(QListWidgetItem* item){

    if(mostra_sensori && item){
        int row = mostra_sensori->row(item);
        if(row!=-1) delete mostra_sensori->takeItem(row);
    }

}


void MainWindow::onAggiungi_sensore_clicked(){

    nsDialog* ns = new nsDialog(this);

    if(ns->exec() == QDialog::Rejected) return; //se l'utente fa annulla non si fa niente

    QString path = ns->getPathColl();
    QFile file(path);

    //se ns->opt==1 bisogna creare una nuova collezione
    if(ns->getOptNuova()){
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QMessageBox::critical(this, "Errore", "Impossibile creare il file.");
        }
        file.close();
    }
    else{
        //il file esiste già, bisogna controllare che sia nel formato corretto
        if(!checkFormat(path)){
            QMessageBox::critical(this, "Errore","Il file scelto non è nel formato corretto.");
            return;
        }
    }

    //aggiungo in coda a file la stringa del nuovo sensore
    if(!file.open(QIODevice::Append | QIODevice::Text)){
        QMessageBox::critical(this, "Errore","Impossibile aprire il file per la modifica.");
        return;
    }

    QTextStream out(&file);
    QString stringa = ns->getStanza()+","+ns->getNome()+","+ns->getTipo()+","+QDate::currentDate().toString("yyyy-MM-dd");
    out<<stringa<<"\n";

    file.close();

    //caricare il file sulla lista mostra_sensori
    fileToWidgetList(path);
}


void MainWindow::onModificaChartContainer(chartBox* newChartBox){

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(newChartBox);
    resetChartBox();
    chartContainer->setLayout(layout);

}


void MainWindow::resetChartBox(){

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
}
