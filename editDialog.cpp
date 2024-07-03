#include "editDialog.h"

editDialog::editDialog(QWidget *parent): QDialog(parent){

    setWindowTitle("Modifica sensore");

    editNome = new QLineEdit(this);
    editNome->setGeometry(20,30,200,30);

    editStanza = new QLineEdit(this);
    editStanza->setGeometry(20,70,200,30);

    //editTipo= new QLineEdit(this);
    //editTipo->setGeometry(20,110,200,30);

    comboTipo = new QComboBox(this);
    comboTipo->setGeometry(20,110,200,30);
    comboTipo->addItem("Temperatura");
    comboTipo->addItem("Fumo");
    comboTipo->addItem("Vento");
    comboTipo->addItem("Aria");

    okButton = new QPushButton("Ok", this);
    okButton->setGeometry(50, 160, 80, 30);

    cancelButton = new QPushButton("Annulla", this);
    cancelButton->setGeometry(150, 160, 80, 30);

    connect(okButton, &QPushButton::clicked, this, &editDialog::acceptChanges);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
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
