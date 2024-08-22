#include "chartaria.h"
#include "sensorefumo.h"
#include "sensorevent.h"

chartAria::chartAria(QWidget* parent, sensore* sensor):chartTemp(parent,sensor){

    hsoglia = new QLabel("Soglia di sicurezza:",this);
    soglia = new QLineEdit(this);

    formLayout->addWidget(hsoglia);
    formLayout->addWidget(soglia);

}




chartAria::~chartAria(){

    delete hsoglia;
    delete soglia;

}








void chartAria::on_crea_grafico_clicked(){

    //setta parametri necessari in base ai campi del widget
    int n = PeriodoDati[combo_dati->currentText()];

    sensore_aria* tmpSensore;
    if(dynamic_cast<const sensore_aria*>(ptrSensore)){
        tmpSensore = static_cast<sensore_aria*>(const_cast<sensore*>(ptrSensore));
    }
    else{
        QMessageBox::critical(this,"Errore","Si è verificato un errore!");
        return;
    }

    bool minOk;
    bool maxOk;
    bool sOk;
    double min = this->min->text().toDouble(&minOk);
    double max = this->max->text().toDouble(&maxOk);
    double soglia = this->soglia->text().toDouble(&sOk);

    if(minOk && maxOk && sOk){
        if(min <= soglia && soglia <= max){
            tmpSensore->setMin(this->min->text().toDouble());
            tmpSensore->setMax(this->max->text().toDouble());
            tmpSensore->setSoglia(this->soglia->text().toDouble());
        }
        else{
            QMessageBox::warning(this,"Errore nei dati","Si richiede min<=soglia<=max");
            return;
        }
    }
    else{
        QMessageBox::warning(this,"Errore nei dati","Min, max e soglia devono essere numeri reali");
        return;
    }

    tmpSensore->genera_dati(n);

    //estrai dati
    const QVector<double>* vettore_dati = tmpSensore->getDati();
    const QVector<bool>* vettore_trigger = tmpSensore->getTrigger();

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
                somma += vettore_dati->at(i*4+j);
            }
            *set<<(somma/4);
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
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QStringList customLabels;
    if(n==7){
        for(int i=0; i<n; ++i){
            QDate date(1,1,1);
            date = date.addDays(currentDay+i-1-7);
            customLabels.append(date.toString("dd/MM"));
        }
        chart->setTitle("Concentrazione media giornaliera di PM10");
    }
    else if(n==28){
        customLabels<<"Settimana 1"<<"Settimana 2"<<"Settimana 3"<<"Settimana 4";
        chart->setTitle("Concentrazione media settimanale di PM10");
    }
    else{
        customLabels = {"Gen","Feb","Mar","Apr","Mag","Giu","Lug","Ago","Set","Ott","Nov","Dic"};
        chart->setTitle("Concentrazione media mensile di PM10");
    }

    int ValoriAnomali = vettore_trigger->count(true);
    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->setTitleText("Giorni oltre la soglia: "+QString::number(ValoriAnomali));
    axisX->append(customLabels);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("[µg/m^3]");
    axisY->setRange(min-1,max);
    chart->addAxis(axisY,Qt::AlignLeft);
    series->attachAxis(axisY);

    QLineSeries* thresholdLine = new QLineSeries();
    thresholdLine->append(-0.5, soglia);
    thresholdLine->append(n - 0.5, soglia);
    QPen pen(Qt::red);
    pen.setWidth(2);
    pen.setBrush(Qt::black);
    thresholdLine->setPen(pen);
    thresholdLine->setName("Soglia: " + QString::number(soglia) +" µg/m^3");

    chart->addSeries(thresholdLine);
    thresholdLine->attachAxis(axisX);
    thresholdLine->attachAxis(axisY);

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


