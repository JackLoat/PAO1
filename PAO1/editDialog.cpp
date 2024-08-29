#include "editDialog.h"

editDialog::editDialog(QWidget *parent): QDialog(parent){

    setWindowTitle("Modifica sensore");

    mainLayout = new QVBoxLayout(this);

    editNome = new QLineEdit(this);
    editNome->setPlaceholderText("Nome");
    editNome->setStyleSheet(
                "QLineEdit {"
                "color: #007bff;"
                "border: 1px solid #d7d6d5;"
                "border-radius: 10px;"
                "padding: 5px;"
                "}"
                "QLineEdit:focus {"
                "border: 1px solid #007bff;"
                "}"
    );

    mainLayout->addWidget(editNome);

    editStanza = new QLineEdit(this);
    editStanza->setPlaceholderText("Stanza");
    editStanza->setStyleSheet(
                "QLineEdit {"
                "color: #007bff;"
                "border: 1px solid #d7d6d5;"
                "border-radius: 10px;"
                "padding: 5px;"
                "}"
                "QLineEdit:focus {"
                "border: 1px solid #007bff;"
                "}"
    );
    mainLayout->addWidget(editStanza);

    comboTipo = new QComboBox(this);
    comboTipo->addItem("Temperatura");
    comboTipo->addItem("Fumo");
    comboTipo->addItem("Vento");
    comboTipo->addItem("Aria");
    comboTipo->setStyleSheet(
                "QComboBox{"
                    "color: #007bff;"
                    "border-radius: 10px;"
                    "background-color: white;"
                    "border: 1px solid #d7d6d5;"
                    "padding: 2px;"
                "}"
                "QComboBox:hover {"
                    "background-color: #ecf2fc;"
                "}"
                "QComboBox:pressed {"
                    "background-color: #d5e2f7;"
                "}"
                "QComboBox::drop-down{"
                    "color: #007bff;"
                    "background-color: transparent;"
                    "border-radius: 10px;"
                    "border: none;"
                    "subcontrol-origin: padding;"
                    "subcontrol-position: top right;"
                    "width: 20px;"
                "}"
                "QComboBox::down-arrow {"
                    "image: url(:/resources/resources/asset/icona_dropdown);"
                    "width: 14px;"
                    "height: 14px;"
                "}"
    );
    comboTipo->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    comboTipo->setMinimumHeight(38);

    comboTipo->view()->setStyleSheet(
                "QListView {"
                "background-color: white;"
                "border: none;"
                "border-radius: 10px;"
                "padding 5px;"
                "}"
                "QListView::item {"
                "padding: 5px 10px;"
                "}"
                "QListView::item:hover{"
                "background-color: #ecf2fc;"
                "}"
                "QListView::item:selected {"
                "background-color: #d5e2f7;"
                "color: #007bff;"
                "}"
    );

    mainLayout->addWidget(comboTipo);

    buttonsLayout = new QHBoxLayout();
    okButton = new QPushButton("Ok", this);
    okButton->setStyleSheet(
                "QPushButton {"
                "   color: white;"
                "   border-radius: 19px;"
                "   background-color: #007bff;"
                "   padding: 2px 4px;"
                //"   width: auto;"
                //"   height: auto;"
                "}"
                "QPushButton:hover {"
                "   background-color: #0056b3;"
                "}"
                "QPushButton:pressed {"
                "   background-color: #003d7a;"
                "}"
    );
    okButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    okButton->setMinimumHeight(38);

    buttonsLayout->addWidget(okButton);
    cancelButton = new QPushButton("Annulla", this);
    cancelButton->setStyleSheet(
        "QPushButton {"
            "color: #007bff;"
            "background-color: white;"
            "border: 1px solid grey;"
            "border-radius: 19px;"
            "padding: 4px 8px;"
            //"width: auto;"
            //"height: auto;"
        "}"
        "QPushButton:hover {"
            "background-color: #ecf2fc;"
            "border: 1px solid grey;"
        "}"
        "QPushButton:pressed {"
            "background-color: #d5e2f7;"
            "border: 1px solid grey;"
        "}"
    );
    cancelButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    cancelButton->setMinimumHeight(38);

    buttonsLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonsLayout);

    connect(okButton, &QPushButton::clicked, this, &editDialog::acceptChanges);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

}


nsDialog::nsDialog(QWidget* parent):editDialog(parent){

    setWindowTitle("Crea sensore");

    mainLayout->removeItem(buttonsLayout);

    buttonsLayout2 = new QHBoxLayout();

    carica_collezione = new QPushButton("Carica collezione", this);
    carica_collezione->setStyleSheet(
        "QPushButton {"
            "color: #007bff;"
            "background-color: white;"
            "border: 1px solid grey;"
            "border-radius: 19px;"
            "padding: 4px 8px;"
            //"width: auto;"
            //"height: auto;"
        "}"
        "QPushButton:hover {"
            "background-color: #ecf2fc;"
            "border: 1px solid grey;"
        "}"
        "QPushButton:pressed {"
            "background-color: #d5e2f7;"
            "border: 1px solid grey;"
        "}"
    );
    carica_collezione->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    carica_collezione->setMinimumHeight(38);
    buttonsLayout2->addWidget(carica_collezione);

    nuova_collezione = new QPushButton("Nuova collezione", this);
    nuova_collezione->setStyleSheet(
        "QPushButton {"
            "color: #007bff;"
            "background-color: white;"
            "border: 1px solid grey;"
            "border-radius: 19px;"
            "padding: 4px 8px;"
            //"width: auto;"
            //"height: auto;"
        "}"
        "QPushButton:hover {"
            "background-color: #ecf2fc;"
            "border: 1px solid grey;"
        "}"
        "QPushButton:pressed {"
            "background-color: #d5e2f7;"
            "border: 1px solid grey;"
        "}"
    );
    nuova_collezione->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    nuova_collezione->setMinimumHeight(38);
    buttonsLayout2->addWidget(nuova_collezione);

    mainLayout->addLayout(buttonsLayout2);
    mainLayout->addLayout(buttonsLayout);

    connect(carica_collezione, &QPushButton::clicked, this, &nsDialog::on_carica_collezione_clicked);
    connect(nuova_collezione, &QPushButton::clicked, this, &nsDialog::on_nuova_collezione_clicked);

}


void editDialog::setLabelsText(const QString& nome, const QString& stanza, const QString& tipo){

    editNome->setText(nome);
    editStanza->setText(stanza);
    comboTipo->setCurrentText(tipo);

}


QString editDialog::getNome() const{
    return editNome->text();
}


QString editDialog::getStanza() const{
    return editStanza->text();
}


QString editDialog::getTipo() const{
    return comboTipo->currentText();
}

bool nsDialog::getOptNuova() const{
    return optNuova;
}


void editDialog::acceptChanges(){
    accept();
}

void nsDialog::accept(){

    //controlla che tutti i campi siano compilati
    if (path_collezione.isEmpty() || editNome->text().isEmpty() || editStanza->text().isEmpty()){
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Errore");
        msgBox.setText("Prima di accettare bisogna compilare tutti i campi e scegliere una collezione.");
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
        //QMessageBox::warning(this, "Errore", "Prima di accettare bisogna compilare tutti i campi e scegliere una collezione.");
        return;
    }

    //se il file esiste già significa che l'utente scelto "carica collezione"
    //controlla se il nome scelto per il sensore non è già presente nel path scelto per la collezione
    QFile file(path_collezione);
    if(file.exists() && !file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Errore");
        msgBox.setText("Impossibile aprire il file.");
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
        //QMessageBox::warning(this, "Errore", "Impossibile aprire il file");
        return;
    }

    QTextStream in(&file);
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList elements = line.split(',');

        if(elements.size()>=2 && elements[1].trimmed()==editNome->text()){
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Errore");
            msgBox.setText("Nella collezione c'è già un sensore con questo nome.");
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
            //QMessageBox::warning(this, "Errore", "Nella collezione c'è già un sensore con questo nome.");
            file.close();
            return;
        }
    }
    file.close();
    QDialog::accept();
}


const QString& nsDialog::getPathColl() const{
    return path_collezione;
}


void nsDialog::setPathColl(const QString& path){
    path_collezione = path;
}


void nsDialog::on_carica_collezione_clicked(){  //richiede di selezionare dal file system
                                                //lo usa per settare QString path_collezione;
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
        //QMessageBox::critical(this, "Errore","Il file selezionato non esiste");
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
        //QMessageBox::warning(this, "Warning","Il file scelto deve essere in formato '.txt'.");
        return;
    }

    //passati tutti i controlli si può aggiornare il campo dell'nsDialog
    path_collezione = nome_file;
    optNuova = 0;
}


void nsDialog::on_nuova_collezione_clicked(){
    //chiede nome della collezione e dove salvarla

    QDir initialDir = QDir::home();
    initialDir.cdUp();
    QString initialPath = initialDir.absolutePath();
    QString nome_file = QFileDialog::getSaveFileName(this, tr("Crea collezione"), initialPath, tr("Text Files (*.txt)"));

    //se l'utente esce senza selezionare un file si ritorna senza fare niente
    if(nome_file.isEmpty()){
        return;
    }
    //controlla che l'esrensione inserita dall'utente sia corretta
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
        //QMessageBox::warning(this, "Warning","Il file scelto deve essere in formato '.txt'.");
        return;
    }
    //superati i controlli si può settare il campo dell'nsdialog
    path_collezione = nome_file;
    optNuova = 1;
}
