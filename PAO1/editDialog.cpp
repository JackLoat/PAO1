#include "editDialog.h"

editDialog::editDialog(QWidget *parent): QDialog(parent){

    setWindowTitle("Modifica sensore");

    mainLayout = new QVBoxLayout(this);

    editNome = new QLineEdit(this);
    editNome->setPlaceholderText("Nome");
    //editNome->setGeometry(20,30,200,30);
    mainLayout->addWidget(editNome);

    editStanza = new QLineEdit(this);
    editStanza->setPlaceholderText("Stanza");
    //editStanza->setGeometry(20,70,200,30);
    mainLayout->addWidget(editStanza);

    //editTipo= new QLineEdit(this);
    //editTipo->setGeometry(20,110,200,30);

    comboTipo = new QComboBox(this);
    //comboTipo->setGeometry(20,110,200,30);
    comboTipo->addItem("Temperatura");
    comboTipo->addItem("Fumo");
    comboTipo->addItem("Vento");
    comboTipo->addItem("Aria");
    mainLayout->addWidget(comboTipo);

    buttonsLayout = new QHBoxLayout(this);

    okButton = new QPushButton("Ok", this);
    //okButton->setGeometry(50, 160, 80, 30);
    buttonsLayout->addWidget(okButton);

    cancelButton = new QPushButton("Annulla", this);
    //cancelButton->setGeometry(150, 160, 80, 30);
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
    //carica_collezione->setGeometry(50, 160, 80, 30);
    //QSize size_carica = carica_collezione->sizeHint();
    //carica_collezione->setMinimumSize(size_carica);
    buttonsLayout2->addWidget(carica_collezione);

    nuova_collezione = new QPushButton("Nuova collezione", this);
    //nuova_collezione->setGeometry(150,160,80,30);
    //QSize size_nuova = nuova_collezione->sizeHint();
    //nuova_collezione->setMinimumSize(size_nuova);
    buttonsLayout2->addWidget(nuova_collezione);

    mainLayout->addLayout(buttonsLayout2);
    mainLayout->addLayout(buttonsLayout);

    //okButton->setMinimumSize(size_carica);
    //cancelButton->setMinimumSize(size_nuova);

    connect(carica_collezione, &QPushButton::clicked, this, &nsDialog::on_carica_collezione_clicked);
    connect(nuova_collezione, &QPushButton::clicked, this, &nsDialog::on_nuova_collezione_clicked);
}

void editDialog::setLabelsText(const QString& nome, const QString& stanza, const QString& tipo){

    editNome->setText(nome);
    editStanza->setText(stanza);
    //editTipo->setText(tipo);
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

void editDialog::acceptChanges(){
    accept();
}

void nsDialog::accept(){
    //controlla che sia stato scelto un path
    if (path_collezione.isEmpty()){
        QMessageBox::warning(this, "Errore", "Prima di accettare bisogna scegliere una collezione");
        return;
    }

    //apri file
    QFile file(path_collezione);

    //se il path scelto non esiste vuol dire che vuole creare un nuovo file
    if(!file.exists()){
        QDir dir = QFileInfo(path_collezione).absoluteDir();
        if(!dir.exists()){
            if(!dir.mkpath(".")){
                qDebug()<<"Impossibile creare la directory:"<<dir.absolutePath();
            }
        }
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
            qDebug()<<"Impossibile creare il file:"<<file.errorString();
        }
        file.close();
    }

    //controlla se il nome scelto per il sensore non è già presente nel path scelto per la collezione
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, "Errore", "Impossibile aprire il file");
        return;
    }

    QTextStream in(&file);
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList elements = line.split(',');

        if(elements.size()>=2 && elements[1].trimmed()==editNome->text()){
            QMessageBox::warning(this, "Errore","Nella collezione c'è già un sensore con questo nome.");
            return;
        }
    }
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
    QString initialPath = "/home/student/Desktop/cartella_collezioni"; //MODIFICA PRIMA DELLA CONSEGNA!!!
    QString nome_file = QFileDialog::getOpenFileName(this,tr("Seleziona file"), initialPath, tr("Text Files (*.txt);;All Files (*)"));

    path_collezione = nome_file;
}

void nsDialog::on_nuova_collezione_clicked(){
    //chiede nome della collezione e dove salvarla
    QString initialPath = "/home/student/Desktop/cartella_collezioni"; //MODIFICA PRIMA DELLA CONSEGNA!!!
    QString nome_file = QFileDialog::getSaveFileName(this, tr("Crea collezione"), initialPath, tr("Text Files (*.txt)"));

    if(!nome_file.isEmpty()){
        if(!nome_file.endsWith(".txt", Qt::CaseInsensitive)){
            nome_file += ".txt";
        }
        path_collezione = nome_file;    //basta associare al nsDialog il path scelto
    }                                   //ci pensa l'override di exec a creare il file se necessario
                                        //in questo modo non serve cancellare il file se
                                        //dopo aver creato una nuova collezione l'utente annulla la creazione del sensore
}
