#include "chartvent.h"
#include "sensorevent.h"
#include "sensorefumo.h"

chartVent::chartVent(QWidget* parent, sensore* sensor):chartAria(parent,sensor){}

chartVent::~chartVent(){}


void chartVent::on_crea_grafico_clicked(){

    int n = PeriodoDati[combo_dati->currentText()];

    visitor_dati* visitor;
    bool minOk;
    bool maxOk;
    bool sOk;
    double min = this->min->text().toDouble(&minOk);
    double max = this->max->text().toDouble(&maxOk);
    double soglia = this->soglia->text().toDouble(&sOk);

    if(minOk && maxOk && sOk){
        if(min <= soglia && soglia <= max){
            visitor = new visitor_dati(n,min,max,soglia);
        }
        else{
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Errore nei dati");
            msgBox.setText("Si richiede min<=soglia<=max.");
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
    }
    else{
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Errore nei dati");
        msgBox.setText("Min, max e soglia devono essere numeri reali.");
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

    //visitor imposta parametri necessari sul sensore, chiama generazione dati e costruisce grafico
    ptrSensore->accept(visitor);

    //aggiunge il grafico all'interfaccia
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


