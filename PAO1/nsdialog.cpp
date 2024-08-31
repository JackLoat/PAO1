#include "nsdialog.h"

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
    );
    nuova_collezione->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    nuova_collezione->setMinimumHeight(38);
    buttonsLayout2->addWidget(nuova_collezione);

    mainLayout->addLayout(buttonsLayout2);
    mainLayout->addLayout(buttonsLayout);

    connect(carica_collezione, &QPushButton::clicked, this, &nsDialog::on_carica_collezione_clicked);
    connect(nuova_collezione, &QPushButton::clicked, this, &nsDialog::on_nuova_collezione_clicked);

}

bool nsDialog::getOptNuova() const{
    return optNuova;
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
    //controlla che l'estensione inserita dall'utente sia corretta
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
    //superati i controlli si può settare il campo dell'nsdialog
    path_collezione = nome_file;
    optNuova = 1;
}
