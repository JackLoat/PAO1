#include "editDialog.h"

editDialog::editDialog(QWidget *parent): QDialog(parent){

    setWindowTitle("Modifica sensore");

    mainLayout = new QVBoxLayout(this);

    editNome = new QLineEdit(this);
    editNome->setPlaceholderText("Nome");
    mainLayout->addWidget(editNome);

    editStanza = new QLineEdit(this);
    editStanza->setPlaceholderText("Stanza");
    mainLayout->addWidget(editStanza);

    comboTipo = new QComboBox(this);
    comboTipo->addItem("Temperatura");
    comboTipo->addItem("Fumo");
    comboTipo->addItem("Vento");
    comboTipo->addItem("Aria");
    mainLayout->addWidget(comboTipo);

    buttonsLayout = new QHBoxLayout();
    okButton = new QPushButton("Ok", this);
    buttonsLayout->addWidget(okButton);
    cancelButton = new QPushButton("Annulla", this);
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
    buttonsLayout2->addWidget(carica_collezione);

    nuova_collezione = new QPushButton("Nuova collezione", this);
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
        QMessageBox::warning(this, "Errore", "Prima di accettare bisogna compilare tutti i campi e scegliere una collezione.");
        return;
    }

    //se il file esiste già significa che l'utente scelto "carica collezione"
    //controlla se il nome scelto per il sensore non è già presente nel path scelto per la collezione
    QFile file(path_collezione);
    if(file.exists() && !file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, "Errore", "Impossibile aprire il file");
        return;
    }

    QTextStream in(&file);
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList elements = line.split(',');

        if(elements.size()>=2 && elements[1].trimmed()==editNome->text()){
            QMessageBox::warning(this, "Errore", "Nella collezione c'è già un sensore con questo nome.");
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
        QMessageBox::critical(this, "Errore","Il file selezionato non esiste");
        return;
    }

    QFileInfo fileInfo(nome_file);
    QString estensione = fileInfo.suffix();
    if (estensione.compare("txt", Qt::CaseInsensitive) != 0) {
        QMessageBox::warning(this, "Warning","Il file scelto deve essere in formato '.txt'.");
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
        QMessageBox::warning(this, "Warning","Il file scelto deve essere in formato '.txt'.");
        return;
    }
    //superati i controlli si può settare il campo dell'nsdialog
    path_collezione = nome_file;
    optNuova = 1;
}
