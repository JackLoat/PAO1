#include "chartBox.h"
#include "sensori.h"

chartBox::chartBox(QWidget* parent, const sensore* sensor):QWidget(parent){
    //qDebug()<<"Costruisco chartBox";

    ptrSensore = sensor;
    crea_grafico = new QPushButton("Genera dati",this);
    combo_dati = new QComboBox(this);
    //chartView = new QChartView(new QChart(), this); //placeholder per il grafico
    chartPlaceHolder = new QWidget(this);

    combo_dati->addItem("Ultima settimana");
    combo_dati->addItem("Ultimo mese");
    combo_dati->addItem("Ultimo anno");

        //qDebug()<<"step1";
    mainLayout = new QVBoxLayout(); //per qualche motivo se si mette this come parent crasha
        //qDebug()<<"step2";
    //QHBoxLayout* topLayout = new QVBoxLayout(this);
    formLayout = new QHBoxLayout();

    formLayout->addWidget(crea_grafico);
    formLayout->addWidget(combo_dati);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(chartPlaceHolder);

    //qDebug()<<"step3";
    if(this->layout() != nullptr){
        QLayout *oldLayout = this->layout();
        QLayoutItem *item;
        while((item = oldLayout->takeAt(0)) != nullptr){
            delete item->widget();
            delete item;
        }
        delete oldLayout;
    }
    //qDebug()<<"step4";
    setLayout(mainLayout);

    //collegare il genera_dati alla funzione di generazione del grafico di sensore_fumo
    connect(crea_grafico, &QPushButton::clicked, this, &chartBox::on_crea_grafico_clicked);
}

chartTemp::chartTemp(QWidget* parent, const sensore* sensor):chartBox(parent,sensor){
    //qDebug()<<"Costruisco chartTemp";
    hmin = new QLabel("Min:",this);
    hmax = new QLabel("Max:",this);

    min = new QLineEdit(this);
    max = new QLineEdit(this);

    //qDebug()<<"step5";
    formLayout2 = new QHBoxLayout();

    formLayout2->addWidget(hmin);
    formLayout2->addWidget(min);
    formLayout2->addWidget(hmax);
    formLayout2->addWidget(max);

    mainLayout->removeWidget(chartPlaceHolder);
    mainLayout->addLayout(formLayout2);
    mainLayout->addWidget(chartPlaceHolder);

    //collegare il genera_dati alla funzione di generazione del grafico di sensore_temp
    //connect(crea_grafico, &QPushButton::clicked, this, &chartTemp::on_crea_grafico_clicked);
}

chartAria::chartAria(QWidget* parent, const sensore* sensor):chartTemp(parent,sensor){
    //qDebug()<<"Costruisco chartAria";
    hsoglia = new QLabel("Soglia:",this);
    soglia = new QLineEdit(this);

    formLayout->addWidget(hsoglia);
    formLayout->addWidget(soglia);

    //collegare il genera_dati alla funzione di generazione del grafico di sensore_temp
    //connect(crea_grafico, &QPushButton::clicked, this, &chartAria::on_crea_grafico_clicked);
}

QMap<QString, int> PeriodoDati = {
    {"Ultima settimana", 7},
    {"Ultimo mese", 30},
    {"Ultimo anno", 365}
};

chartVent::chartVent(QWidget* parent, const sensore* sensor):chartAria(parent,sensor){
    //qDebug()<<"costurisco chartVent";
    //collegare il crea_graifco alla funzione di generazione del grafico di
    //connect(crea_grafico, &QPushButton::clicked, this, &chartVent::on_crea_grafico_clicked);
}


void chartBox::on_crea_grafico_clicked(){
    qDebug()<<"genera grafo cliccato, chartbox";
}
void chartTemp::on_crea_grafico_clicked(){
    qDebug()<<"genera grafo cliccato, charttemp";
}
void chartAria::on_crea_grafico_clicked(){
    qDebug()<<"genera grafo cliccato, chartaria";
}
void chartVent::on_crea_grafico_clicked(){
    qDebug()<<"genera grafo cliccato, chartvent";
}

/*
void chartBox::on_crea_grafico_clicked(){
    //setta i campi del sensore in base ai campi del widgte
    //al sensore di fumo basta n
    //al temp serve n, min e max
    //a aria serve n, min, max e soglia
    //a vent serve n,min,max,soglia

    //n va passato come parametro a genera_dati
    //chiama generazione dati

    int n = PeriodoDati[this->combo_dati->currentText()];

    sensore_fumo* tmpSensore = dynamic_cast<sensore_fumo*>(const_cast<sensore*>(ptrSensore));

    if(tmpSensore){
        tmpSensore->genera_dati(n);
    }
        //estrai i dati
    //da fumo si prende vettore_trigger
    //da temp si prende vettore_dati
    //da aria si prende vettore_dati e vettore_trigger
    //da vento si prende vettore_dati, vettore_trigger e vettore_direz
    QVector<bool>* vettore_trigger = tmpSensore->getTrigger();

    //crea grafico
    QChart* chart = new QChart();
    chart->setTitle("Allarmi sensore di fumo");
    QBarSeries *series = new QBarSeries();

    QBarSet *set = new QBarSet("Allarmi");

    foreach (int allarme, vettore_trigger){
        *set << allarme;
    }

    series->append(set);
    chart->addSeries(series);

    QStringList categories;
    QDateTime oggi = QDateTime::currentDateTime();
    for (int i=n-1; i>=0; --i){
        QDateTime data = oggi.addDays(-i);
        categories << data.toString("dd");
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis();

    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisY);

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    mainLayout->removeWidget(chartPlaceHolder);
    mainLayout->addWidget(chartView);

}

void chartTemp::on_crea_grafico_clicked(){
    //n, min, max
    int n = PeriodoDati[this->combo_dati->currentText()];
    sensore_temp* tmpSensore = dynamic_cast<sensore_temp*>(const_cast<sensore*>(ptrSensore));

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

    //estrai dati dal sensore
    QVector <double>* vettore_dati = tmpSensore->getDati();

    //crea il qchart
    QVector<QPointF> points;
    for (int i=0; i<n; ++i){
        points.append(QPointF(i,(*vettore_dati)[i]));
    }

    QLineSeries *serie = new QLineSeries();
    serie->replace(points);
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(serie);
    chart->createDefaultAxes();
    chart->setTitle("Tempertura media giornaliera");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    mainLayout->removeWidget(chartPlaceHolder);
    mainLayout->addWidget(chartView);
}

void chartAria::on_crea_grafico_clicked(){
    //n, min, max, soglia
    int n = PeriodoDati[this->combo_dati->currentText()];
    sensore_aria* tmpSensore = dynamic_cast<sensore_aria*>(const_cast<sensore*>(ptrSensore));

    bool minOk;
    bool maxOk;
    bool sOk;
    double min = this->min->text().toDouble(&minOk);
    double max = this->min->text().toDouble(&maxOk);
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
        QMessageBox::warning(this,"Errore nei dati","min e max devono essere numeri reali");
        return;
    }

    tmpSensore->genera_dati(n);

    //estrai dati
    QVector<double>* vettore_dati = tmpSensore->getDati();
    QVector<bool>* vettore_trigger = tmpSensore->getTrigger();

    //crea qchart
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->setTitle("Qualità dell'aria con giorni con aria insalubre evidenziati");

    QScatterSeries *normalSeries = new QScatterSeries();
    normalSeries->setMarkerSize(10);
    QScatterSeries *triggerSeries = new QScatterSeries();
    triggerSeries->setMarkerSize(10);

    for(int i=0; i<n; ++i){
        QPointF point(i, (*vettore_dati)[i]);
        if((*vettore_trigger)[i]){
            triggerSeries->append(point);
        }
        else{
            normalSeries->append(point);
        }
    }

    normalSeries->setColor(Qt::blue);
    triggerSeries->setColor(Qt::red);

    chart->addSeries(normalSeries);
    chart->addSeries(triggerSeries);

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setTitleText("Index");
    chart->axes(Qt::Vertical).first()->setTitleText("Value");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    mainLayout->removeWidget(chartPlaceHolder);
    mainLayout->addWidget(chartView);

}


void chartVent::on_crea_grafico_clicked(){
    //n, min, max, soglia
    int n = PeriodoDati[this->combo_dati->currentText()];
    sensore_vent* tmpSensore = dynamic_cast<sensore_vent*>(const_cast<sensore*>(ptrSensore));

    bool minOk;
    bool maxOk;
    bool sOk;
    double min = this->min->text().toDouble(&minOk);
    double max = this->min->text().toDouble(&maxOk);
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
        QMessageBox::warning(this,"Errore nei dati","min e max devono essere numeri reali");
        return;
    }

    tmpSensore->genera_dati(n);

    //estrai dati
    QVector<double>* vettore_dati = tmpSensore->getDati();
    QVector<bool>* vettore_trigger = tmpSensore->getTrigger();
    QVector<double>* vettore_direz = tmpSensore->getDirez();

    //crea grafico
    QBarSet *barSet = new QBarSet("Velocità media del vento");
    for(int i=0; i<n; ++i){
        *barSet<<vettore_dati->at(i);
    }

    QBarSeries* barSeries = new QBarSeries();
    barSeries->append(barSet);

    QChart* chart = new QChart();
    chart->addSeries(barSeries);
    chart->setTitle("velocità media del giornaliera vento");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    QDateTime oggi = QDateTime::currentDateTime();
    for (int i=n-1; i>=0; --i){
        QDateTime data = oggi.addDays(-i);
        categories << data.toString("dd");
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX,Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Velocità media (km/h)");
    chart->addAxis(axisY,Qt::AlignLeft);
    barSeries->attachAxis(axisY);

    //aggiungere punti rossi per il superamento della soglia
    QScatterSeries *scatterSeries = new QScatterSeries();
    for(int i=0; i<n; ++i){
        if(vettore_trigger->at(i)){
            scatterSeries->append(i,vettore_dati->at(i));
        }
    }
    scatterSeries->setMarkerSize(10);
    scatterSeries->setColor(Qt::red);
    chart->addSeries(scatterSeries);
    scatterSeries->attachAxis(axisX);
    scatterSeries->attachAxis(axisY);

    //aggiungere frecce per la direzione del vento
    QLineSeries *lineSeries = new QLineSeries();
    for (int i=0; i<n;i++){
        double xStart = i;
        double yStart = vettore_dati->at(i);
        double xEnd = i+0.5 *qCos(vettore_direz->at(i));
        double yEnd = vettore_dati->at(i)+0.5*qSin(vettore_direz->at(i));

        lineSeries->append(QPointF(xStart,yStart));
        lineSeries->append(QPointF(xEnd,yEnd));
    }
    lineSeries->setColor(Qt::darkGreen);
    chart->addSeries(lineSeries);
    lineSeries->attachAxis(axisX);
    lineSeries->attachAxis(axisY);

    //impostazioni aggiunive grafico
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    //visualizzazione grafico
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    mainLayout->removeWidget(chartPlaceHolder);
    mainLayout->addWidget(chartView);
}
*/
