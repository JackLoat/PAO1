#include "chartBox.h"
#include "sensorefumo.h"
#include "sensorevent.h"

chartBox::chartBox(QWidget* parent, sensore* sensor):QWidget(parent){

    ptrSensore = sensor;
    crea_grafico = new QPushButton("Genera dati",this);
    crea_grafico->setStyleSheet(
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
    crea_grafico->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    crea_grafico->setMinimumHeight(38);

    combo_dati = new QComboBox(this);
    combo_dati->setStyleSheet(
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
/*                "QComboBox QAbstractItemView {"
                    "border: none;"
                    "background-color: white;"
                    "selection-background-color: #ecf2fc;"
                    "selection-color: #007bff;"
                    "border-radius: 10px;"
                    "outline: none;"
                    "margin: 0px;"
                    "padding: 0px;"
                "}"
                "QComboBox QAbstractItemView::item{"
                    "padding: 5px 10px;"
                    "background-color: transparent;"
                    "border: none;"
                "}"
                "QComboBox QAbstractItemView::item:hover {"
                    "background-color: #ecf2fc;"
                    "color: #007bff;"
                "}"
                "QComboBox QAbstractItemView::item:selected {"
                    "background-color: #d5e2f7;"
                    "color: #007bff;"
                "}"
                "QComboBox QAbstractItemView::item:first {"
                    "border-top-left-radius: 10px;"
                    "border-top-right-radius: 10px;"
                    "border-top: none;"
                "}"
                "QComboBox QAbstractItemView::item:last {"
                    "border-bottom-left-radius: 10px;"
                    "border-bottom-right-radius: 10px;"
                    "border-bottom: none;"
                "}"*/
    );
    combo_dati->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    combo_dati->setMinimumHeight(38);


    combo_dati->addItem("Ultima settimana");
    combo_dati->addItem("Ultimo mese");
    combo_dati->addItem("Ultimo anno");

    combo_dati->view()->setStyleSheet(
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

    chartPlaceHolder = new QWidget(this);


    mainLayout = new QVBoxLayout();

    formLayout = new QHBoxLayout();

    chartLayout = new QVBoxLayout(chartPlaceHolder);

    formLayout->addWidget(crea_grafico);
    formLayout->addWidget(combo_dati);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(chartPlaceHolder);

    setLayout(mainLayout);

    connect(crea_grafico, &QPushButton::clicked, this, &chartBox::on_crea_grafico_clicked);

}




chartBox::~chartBox(){

    delete chartPlaceHolder;
    delete crea_grafico;
    delete combo_dati;

    delete formLayout;
    delete mainLayout;


}

QMap<QString, int> PeriodoDati = {
    {"Ultima settimana", 7},
    {"Ultimo mese", 28},
    {"Ultimo anno", 365}
};

void chartBox::on_crea_grafico_clicked(){
        //da modificare: crea visitor, setta i parametri del visitor, estrai il QChart* chart dal visitor
            //alla fine usare chart per creare QChatView* chartview e aggiungerlo al layout

    //test
    int n = PeriodoDati[combo_dati->currentText()];
    visitor_dati* visitor = new visitor_dati(n);
    //setta campi del visitor

    //da rimuovere
    //setta parametri necessari in base ai campi del widget
//    int n = PeriodoDati[combo_dati->currentText()];

    //fa generare i dati al sensore e estrae il vettore_trigger
//    ptrSensore->genera_dati(n);
/*
    const QVector<bool>* vettore_trigger;
    if(dynamic_cast<sensore_fumo*>(ptrSensore)){
        vettore_trigger = static_cast<sensore_fumo*>(ptrSensore)->getTrigger();
    }
    else{
        QMessageBox::critical(this,"Errore","Si è verificato un errore!");
        return;
    }
*/
        //test
    //chiamare accept
    ptrSensore->accept(visitor);

    //crea grafico
    QChart* chart = visitor->getChart();

    QChartView* chartView = new QChartView(chart);
    if(chartLayout->count()>0){
        QLayoutItem* item = chartLayout->takeAt(0);
        if (item){
            delete item->widget();
            delete item;
        }
    }
    chartLayout->addWidget(chartView);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->show();

}

