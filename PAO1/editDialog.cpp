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

void editDialog::acceptChanges(){
    accept();
}

