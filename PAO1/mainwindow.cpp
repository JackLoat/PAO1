#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("SpiderSensors");
    showMaximized();

    carica_collezione = new QPushButton("Carica collezione",this);
    carica_collezione->setStyleSheet(
                "QPushButton {"
                "   color: white;"
                "   border-radius: 19px;"
                "   background-color: #007bff;"
                "   padding: 2px;"
                "   min-height: 38px;"
                "}"
                "QPushButton:hover {"
                "   background-color: #0056b3;"
                "}"
                "QPushButton:pressed {"
                "   background-color: #003d7a;"
                "}"
    );
    QIcon icona_carica(":/resources/resources/asset/icona_carica");
    carica_collezione->setIcon(icona_carica);
    carica_collezione->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    nome_collezione = new QLabel("Nome collezione",this);
    nome_collezione->setStyleSheet("color: #0071e3; padding: 3px 1px 3px 1px;");
    nome_collezione->setAlignment(Qt::AlignCenter);
    QFont font = nome_collezione->font();
    font.setPointSize(18);
    nome_collezione->setFont(font);

    rimuovi_collezione = new QPushButton("Rimuovi collezione", this);
    rimuovi_collezione->setStyleSheet(
                "QPushButton {"
                "   color: white;"
                "   border-radius: 19px;"
                "   background-color: #ff4c4c;"
                "   padding: 2px;"
                "   min-height: 38px;"
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
    QIcon icona_rimuovi(":/resources/resources/asset/icona_rimuovi");
    rimuovi_collezione->setIcon(icona_rimuovi);
    rimuovi_collezione->setDisabled(true);
    rimuovi_collezione->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QGraphicsDropShadowEffect *shadowBarraRicerca = new QGraphicsDropShadowEffect;
    shadowBarraRicerca->setBlurRadius(15);
    shadowBarraRicerca->setOffset(2,2);
    shadowBarraRicerca->setColor(Qt::gray);

    barra_ricerca = new QLineEdit(this);
    barra_ricerca->setClearButtonEnabled(true);
    barra_ricerca->setPlaceholderText("Ricerca...");
    barra_ricerca->setGraphicsEffect(shadowBarraRicerca);
    barra_ricerca->setStyleSheet(
                "color: #007bff;"
                "border-radius: 19px;"
                "padding: 2px;"
                "width: auto;"
                "height: auto;"
    );
    QIcon icona_ricerca(":/resources/resources/asset/icona_ricerca");
    QAction *iconAction = new QAction(icona_ricerca, "", barra_ricerca);
    barra_ricerca->addAction(iconAction, QLineEdit::LeadingPosition);

    mostra_sensori = new QListWidget(this);
    mostra_sensori->setStyleSheet(
                "QListWidget {"
                "   border: 1px solid #d7d6d5;"
                "   border-radius: 10px;"
                "   padding: 5px;"
                "}"
                "QListWidget::item {"
                "   background-color: white;"
                "   color: #007bff;"
                "   padding: 5px;"
                "   border-radius: 5px;"
                "}"
                "QListWidget::item:selected {"
                "   border: 1px solid grey;"
                "   color: #007bff;"
                "}"
                "QToolTip {"
                "background-color: white;"
                "color: grey;"
                "border: 1px solid grey;"
                "padding: 2px;"
                "border-radius: 5px;"
                "}"

                "QScrollBar:horizontal {"
                "border: 1px solid #d7d6d5;"
                "background: white;"
                "height: 12px;"
                "border-radius: 6px;"
                "}"
                "QScrollBar:vertical {"
                "border: 1px solid #d7d6d5;"
                "background: white;"
                "width: 12px;"
                "border-radius: 6px;"
                "}"

                "QScrollBar::handle:horizontal {"
                "background: grey;"
                "border-radius: 5px;"
                "}"
                "QScrollBar::handle:vertical {"
                "background: grey;"
                "border-radius: 5px;"
                "}"

                "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {"
                "background: white;"
                "border-radius: 5px"
                "}"
                "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
                "background: white;"
                "border-radius: 5px;"
                "}"
    );
    mostra_sensori->setIconSize(QSize(32,32));

    QGraphicsDropShadowEffect *shadowAggiungiSensore = new QGraphicsDropShadowEffect;
    shadowAggiungiSensore->setBlurRadius(15);
    shadowAggiungiSensore->setOffset(2,2);
    shadowAggiungiSensore->setColor(Qt::gray);

    aggiungi_sensore = new QPushButton("",this);
    aggiungi_sensore->setStyleSheet(
                "QPushButton {"
                "   color: white;"
                "   border-radius: 19px;"
                "   background-color: #007bff;"
                "   padding: 2px;"
                "   width: auto;"
                "   height: auto;"
                "}"
                "QPushButton:hover {"
                "   background-color: #0056b3;"
                "}"
                "QPushButton:pressed {"
                "   background-color: #003d7a;"
                "}"
    );
    QIcon icona_aggiungi(":/resources/resources/asset/icona_aggiungi");
    aggiungi_sensore->setIcon(icona_aggiungi);
    aggiungi_sensore->setMinimumSize(38,38);
    aggiungi_sensore->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    aggiungi_sensore->setGraphicsEffect(shadowAggiungiSensore);

    QWidget* container = new QWidget(this);
    QGridLayout* gridLayout = new QGridLayout(container);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    QWidget* buttonLayer = new QWidget();
    QGridLayout* buttonLayout = new QGridLayout(buttonLayer);
    buttonLayout->setContentsMargins(0, 0, 25, 25);
    buttonLayout->addWidget(aggiungi_sensore, 0, 0, 1, 1, Qt::AlignBottom | Qt::AlignRight);

    gridLayout->addWidget(mostra_sensori,0,0,1,1);
    gridLayout->addWidget(buttonLayer, 0, 0, Qt::AlignBottom | Qt::AlignRight);

    box_sensore = new sensorBox(this);
    chartContainer = new QWidget(this);

    QSplitter* rightSplitter = new QSplitter(Qt::Vertical, this);
    rightSplitter->addWidget(box_sensore);
    rightSplitter->addWidget(chartContainer);

    QList<int> rightSizes;
    rightSizes << height()/6 << height()*5/6;
    rightSplitter->setSizes(rightSizes);

    QVBoxLayout* sinistra = new QVBoxLayout();
    sinistra->addWidget(carica_collezione);
    sinistra->addWidget(nome_collezione);
    sinistra->addWidget(barra_ricerca);

    sinistra->addWidget(container);
    sinistra->addWidget(rimuovi_collezione);

    QWidget* leftWidget = new QWidget;
    leftWidget->setLayout(sinistra);

    QWidget* rightWidget = new QWidget;
    QVBoxLayout* rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->addWidget(rightSplitter);

    QSplitter* splitter = new QSplitter(this);
    splitter->addWidget(leftWidget);
    splitter->addWidget(rightWidget);
    QList<int> sizes;
    sizes << width()/8 << 7*width()/8;
    splitter->setSizes(sizes);

    ui->centralwidget->setLayout(new QVBoxLayout);
    ui->centralwidget->layout()->addWidget(splitter);
    ui->centralwidget->setStyleSheet("QSplitter {background-color: white;}");

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
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Conferma eliminazione");
    msgBox.setText("Vuoi eliminare questa collezione? Non sarà più recuperabile");
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

    QMessageBox::StandardButton reply = static_cast<QMessageBox::StandardButton>(msgBox.exec());

    if (reply == QMessageBox::No) return;

    collezione* collPtr = reinterpret_cast<collezione*>(mostra_sensori->property("puntatoreCollezione").value<void*>());

    //elimina file
    QString path = collPtr->getPath();
    if(!QFile::remove(path)){
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Errore");
        msgBox.setText("Impossibile eliminare il file contenente la collezione.");
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

    QPixmap pixmap(":/resources/resources/asset/icona_sensore_"+sensor->getTipo());
    box_sensore->setIcona(pixmap.scaled(64,64, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    //salva un puntatore al sensore e all'item nelle proprietà della sensorBox
    box_sensore->setProperty("PuntatoreSensore", QVariant::fromValue(static_cast<void*>(sensor)));
    box_sensore->setProperty("PuntatoreItem", QVariant::fromValue(static_cast<void*>(item)));

    //chiama il setup del mostra_grafico e aggiorna il layout con la chartBox ottenuta
    visitor_grafico* visitor = new visitor_grafico;
    sensor->accept(visitor);
    chartBox* box_grafo = visitor->getWidget();

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

    //ulteriore controllo che il file esista e abbia estensione e formato corretti
    QFile file(nome_file);
    if(!file.exists()){
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Errore");
        msgBox.setText("Il file selezionato non esiste.");
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

    QFileInfo fileInfo(nome_file);
    QString estensione = fileInfo.suffix();
    if (estensione.compare("txt", Qt::CaseInsensitive) != 0) {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Il file scelto deve essere in formato '.txt'.");
        msgBox.setIcon(QMessageBox::Warning);
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

    if(!checkFormat(nome_file)){
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Il file scelto non è nel formato corretto.");
        msgBox.setIcon(QMessageBox::Warning);
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

    barra_ricerca->setText("");

    fileToWidgetList(nome_file);

}


void MainWindow::fileToWidgetList(const QString& path){

    if (path.isEmpty()) return;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("Error"));
        msgBox.setText(tr("Impossibile aprire il file: ") + file.errorString());
        msgBox.setIcon(QMessageBox::Warning);
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
            QMessageBox msgBox(this);
            msgBox.setWindowTitle(tr("Error"));
            msgBox.setText(tr("Formato file errato."));
            msgBox.setIcon(QMessageBox::Warning);
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

        item->setText(sensor->getNome());
        item->setToolTip("Stanza: "+sensor->getStanza()+"\nDataCreazione: "+sensor->getDataC().toString()+"\nTipo: "+sensor->getTipo());
        item->setData(Qt::UserRole, QVariant::fromValue(sensor));

        item->setIcon(*(new QIcon(":/resources/resources/asset/icona_sensore_"+sensor->getTipo())));

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
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Errore");
            msgBox.setText("Impossibile creare il file.");
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
        file.close();
    }
    else{
        //il file esiste già, bisogna controllare che sia nel formato corretto
        if(!checkFormat(path)){
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Errore");
            msgBox.setText("Il file scelto non è nel formato corretto.");
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
    }

    //aggiungo in coda a file la stringa del nuovo sensore
    if(!file.open(QIODevice::Append | QIODevice::Text)){
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Errore");
        msgBox.setText("Impossibile aprire il file per la modifica.");
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
