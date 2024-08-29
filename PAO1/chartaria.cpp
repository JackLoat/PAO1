#include "chartaria.h"
#include "sensorefumo.h"
#include "sensorevent.h"

chartAria::chartAria(QWidget* parent, sensore* sensor):chartTemp(parent,sensor){

    hsoglia = new QLabel("Soglia di sicurezza:",this);
    hsoglia->setStyleSheet("color: #007bff;");
    soglia = new QLineEdit(this);
    soglia->setStyleSheet(
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
    soglia->setMinimumHeight(38);

    formLayout->addWidget(hsoglia);
    formLayout->addWidget(soglia);

}


chartAria::~chartAria(){

    delete hsoglia;
    delete soglia;

}


void chartAria::on_crea_grafico_clicked(){
        //test
    int n = PeriodoDati[combo_dati->currentText()];

    //settare dati del visitor
        //da rimuovere
    //visitor->setPeriodoDati(PeriodoDati[combo_dati->currentText()]);

        //da rimuovere
    //setta parametri necessari in base ai campi del widget
//    int n = PeriodoDati[combo_dati->currentText()];
/*
    sensore_aria* tmpSensore;
    if(dynamic_cast<const sensore_aria*>(ptrSensore)){
        tmpSensore = static_cast<sensore_aria*>(const_cast<sensore*>(ptrSensore));
    }
    else{
        QMessageBox::critical(this,"Errore","Si è verificato un errore!");
        return;
    }
*/
    visitor_dati* visitor;
    bool minOk;
    bool maxOk;
    bool sOk;
    double min = this->min->text().toDouble(&minOk);
    double max = this->max->text().toDouble(&maxOk);
    double soglia = this->soglia->text().toDouble(&sOk);

    if(minOk && maxOk && sOk){
        if(min <= soglia && soglia <= max){
                //da rimuovere
//            tmpSensore->setMin(this->min->text().toDouble());
//            tmpSensore->setMax(this->max->text().toDouble());
//            tmpSensore->setSoglia(this->soglia->text().toDouble());

                //test
            //costruire visitor
            visitor = new visitor_dati(n, min, max, soglia);
                //da rimuovere
//            visitor->setMin(min);
//            visitor->setMax(max);
//            visitor->setSoglia(soglia);
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

            //QMessageBox::warning(this,"Errore nei dati","Si richiede min<=soglia<=max");
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
        //QMessageBox::warning(this,"Errore nei dati","Min, max e soglia devono essere numeri reali");
        return;
    }
        //test
    ptrSensore->accept(visitor);

        //da rimuovere
/*
    tmpSensore->genera_dati(n);

    //estrai dati
    const QVector<double>* vettore_dati = tmpSensore->getDati();
    const QVector<bool>* vettore_trigger = tmpSensore->getTrigger();
*/
    //crea il qchart
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


