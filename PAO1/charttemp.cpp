#include "charttemp.h"
#include "sensorefumo.h"
#include "sensorevent.h"

chartTemp::chartTemp(QWidget* parent, sensore* sensor):chartBox(parent,sensor){

    hmin = new QLabel("Min:",this);
    hmin->setStyleSheet(
        "color: #007bff;"
    );

    hmax = new QLabel("Max:",this);
    hmax->setStyleSheet("color: #007bff;");

    min = new QLineEdit(this);
    min->setStyleSheet(
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
    min->setMinimumHeight(38);

    max = new QLineEdit(this);
    max->setStyleSheet(
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
    max->setMinimumHeight(38);

    formLayout2 = new QHBoxLayout();

    formLayout->addWidget(hmin);
    formLayout->addWidget(min);
    formLayout->addWidget(hmax);
    formLayout->addWidget(max);

    //mainLayout->removeWidget(chartPlaceHolder);
    //mainLayout->addLayout(formLayout2);
    mainLayout->addWidget(chartPlaceHolder);

}


chartTemp::~chartTemp(){

    delete hmin;
    delete hmax;
    delete min;
    delete max;

    delete formLayout2;

}


void chartTemp::on_crea_grafico_clicked(){
        //test
        //da rimuovere
    //setta campi visitor
//    visitor->setPeriodoDati(PeriodoDati[combo_dati->currentText()]);
    int n = PeriodoDati[combo_dati->currentText()];

        //da rimuovere
    //setta parametri necessari in base ai campi del widget
//    int n = PeriodoDati[this->combo_dati->currentText()];
/*
    sensore_temp* tmpSensore;
    if(dynamic_cast<const sensore_temp*>(ptrSensore)){
        tmpSensore = static_cast<sensore_temp*>(const_cast<sensore*>(ptrSensore));
    }
    else{
        QMessageBox::critical(this,"Errore","Si è verificato un errore!");
        return;
    }
*/

    visitor_dati* visitor;

    bool minOk;
    bool maxOk;

    double min = this->min->text().toDouble(&minOk);
    double max = this->max->text().toDouble(&maxOk);

    if(minOk && maxOk){
        if(min<=max){
//            tmpSensore->setMin(this->min->text().toDouble());
//            tmpSensore->setMax(this->max->text().toDouble());
                //test
            visitor = new visitor_dati(n,min,max);
                //da rimuovere
//            visitor->setMax(max);
//            visitor->setMin(min);
        }
        else{
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Errore nei dati");
            msgBox.setText("Si richiede min<=max.");
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
            //QMessageBox::warning(this,"Errore nei dati","Si richiede min<=max");
            return;
        }
    }
    else{
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Errore nei dati");
        msgBox.setText("Min e max devono essere numeri reali.");
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
        //QMessageBox::warning(this,"Errore nei dati","min e max devono essere numeri reali");
        return;
    }

    ptrSensore->accept(visitor);

//    tmpSensore->genera_dati(n);

    //estrae dati dal sensore
//    const QVector <double>* vettore_dati = tmpSensore->getDati();

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


