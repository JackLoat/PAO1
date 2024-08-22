#include "charttemp.h"
#include "sensorefumo.h"
#include "sensorevent.h"

chartTemp::chartTemp(QWidget* parent, sensore* sensor):chartBox(parent,sensor){

    hmin = new QLabel("Min:",this);
    hmax = new QLabel("Max:",this);

    min = new QLineEdit(this);
    max = new QLineEdit(this);

    formLayout2 = new QHBoxLayout();

    formLayout2->addWidget(hmin);
    formLayout2->addWidget(min);
    formLayout2->addWidget(hmax);
    formLayout2->addWidget(max);

    mainLayout->removeWidget(chartPlaceHolder);
    mainLayout->addLayout(formLayout2);
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

    //setta parametri necessari in base ai campi del widget
    int n = PeriodoDati[this->combo_dati->currentText()];

    sensore_temp* tmpSensore;
    if(dynamic_cast<const sensore_temp*>(ptrSensore)){
        tmpSensore = static_cast<sensore_temp*>(const_cast<sensore*>(ptrSensore));
    }
    else{
        QMessageBox::critical(this,"Errore","Si è verificato un errore!");
        return;
    }

    bool minOk;
    bool maxOk;

    double min = this->min->text().toDouble(&minOk);
    double max = this->max->text().toDouble(&maxOk);

    if(minOk && maxOk){
        if(min<=max){
            tmpSensore->setMin(this->min->text().toDouble());
            tmpSensore->setMax(this->max->text().toDouble());
        }
        else{
            QMessageBox::warning(this,"Errore nei dati","Si richiede min<=max");
        }
    }
    else{
        QMessageBox::warning(this,"Errore nei dati","min e max devono essere numeri reali");
        return;
    }
    tmpSensore->genera_dati(n);

    //estrae dati dal sensore
    const QVector <double>* vettore_dati = tmpSensore->getDati();

    //crea il qchart
    QChart* chart = new QChart();

    int currentDay = QDate::currentDate().dayOfYear();
    QBarSet* set = new QBarSet("Dati");
    if(n==7){
        for (double value : *vettore_dati){
            *set<<value;
        }
    }
    else if(n==28){
        for(int i=0; i<4; i++){
            double somma = 0;
            for(int j=0; j<7; j++){
                somma += vettore_dati->at(i*7+j);
            }
            *set<<(somma/7);
        }
    }
    else{
        QVector<int> GiorniPerMese = {31,28,31,30,31,30,31,31,30,31,30,31};
        int inizio = 0;
        for(int giorniInMese : GiorniPerMese){
            double somma = std::accumulate(vettore_dati->begin() + inizio, vettore_dati->begin() + inizio + giorniInMese, 0.0);
            *set<<(somma/giorniInMese);
            inizio+=giorniInMese;
        }

    }

    QBarSeries* series = new QBarSeries();
    series->append(set);

    chart->addSeries(series);
    chart->legend()->hide();

    QStringList customLabels;
    if(n==7){
        for(int i=0; i<n; ++i){
            QDate date(1,1,1);
            date = date.addDays(currentDay+i-1-7);
            customLabels.append(date.toString("dd/MM"));
        }
        chart->setTitle("Temperatura media giornaliera");
    }
    else if(n==28){
        customLabels<<"Settimana 1"<<"Settimana 2"<<"Settimana 3"<<"Settimana 4";
        chart->setTitle("Temperatura media settimanale");
    }
    else{
        customLabels = {"Gen","Feb","Mar","Apr","Mag","Giu","Lug","Ago","Set","Ott","Nov","Dic"};
        chart->setTitle("Temperatura media mensile");
    }

    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->setTitleText("Giorni");
    axisX->append(customLabels);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("°C");
    chart->addAxis(axisY,Qt::AlignLeft);
    series->attachAxis(axisY);

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


