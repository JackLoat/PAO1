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
    hsoglia = new QLabel("Soglia di sicurezza:",this);
    soglia = new QLineEdit(this);

    formLayout->addWidget(hsoglia);
    formLayout->addWidget(soglia);

    //collegare il genera_dati alla funzione di generazione del grafico di sensore_temp
    //connect(crea_grafico, &QPushButton::clicked, this, &chartAria::on_crea_grafico_clicked);
}

QMap<QString, int> PeriodoDati = {
    {"Ultima settimana", 7},
    {"Ultimo mese", 28},
    {"Ultimo anno", 365}
};

chartVent::chartVent(QWidget* parent, const sensore* sensor):chartAria(parent,sensor){
    //qDebug()<<"costurisco chartVent";
    //collegare il crea_graifco alla funzione di generazione del grafico di
    //connect(crea_grafico, &QPushButton::clicked, this, &chartVent::on_crea_grafico_clicked);
}

chartBox::~chartBox(){
    delete chartPlaceHolder;
    delete crea_grafico;
    delete combo_dati;

    delete mainLayout;
    delete formLayout;
}

chartTemp::~chartTemp(){
    delete hmin;
    delete hmax;
    delete min;
    delete max;

    delete formLayout2;
}

chartAria::~chartAria(){
    delete hsoglia;
    delete soglia;
}

chartVent::~chartVent(){}


/*
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
*/

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
    chart->legend()->hide();
    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    QValueAxis *axisY = new QValueAxis();

    QBarSeries *serie = new QBarSeries();
    if(n==28){
        QBarSet * set = new QBarSet("Settiane");
        for(int i=0; i<4; ++i){
            int countTrue=0;
            for (int j=0; j<7; ++j){
                if((*vettore_trigger)[i*7+j]){
                    countTrue++;
                }
            }
            *set <<countTrue;
        }
        set->setColor(Qt::red);
        serie->append(set);
        chart->setTitle("Numero allarmi sensore di fumo per settimana");
        axisX->append({"Settimana 1","Settimana 2","Settimana 3","Settimana 4"});
    }
    else if(n==365){
        QBarSet * set = new QBarSet("Mesi");
        QVector<QString> months = {"Gen","Feb","Mar","Apr","Mag","Giu","Lug","Ago","Set","Ott","Nov","Dic"};
        QVector<int> GiorniPerMese = {31,28,31,30,31,30,31,31,30,31,30,31};

        int currentMonth = QDate::currentDate().month()-1;

        QVector<QString> reorderedMonths;
        QVector<int> reorderedGiorniMese;
        for(int i=0; i<12; i++){
            int monthIndex = (currentMonth + i) %12;
            reorderedMonths.append(months[monthIndex]);
            reorderedGiorniMese.append(GiorniPerMese[monthIndex]);
        }

        int index = 0;
        for (int i=0; i<12; ++i){
            int monthIndex = (currentMonth+i)%12;
            int countTrue=0;
            for(int j=0; j<reorderedGiorniMese[monthIndex]; ++j){
                if ((*vettore_trigger)[index++]){
                    countTrue++;
                }
            }
            *set<<countTrue;
        }
        set->setColor(Qt::red);
        serie->append(set);
        chart->setTitle("Numero allarmi sensore di fumo per mese");
        axisX->append(reorderedMonths);
    }
    else{//n=7
        QVector<QString> days = {"Lun","Mar","Mer","Gio","Ven","Sab","Dom"};
        int currentDay = QDate::currentDate().dayOfWeek()%7;
        QVector<QString> reorderedDays;
        for(int i=0; i<7; i++){
            int dayIndex = (currentDay + i) %7;
            reorderedDays.append(days[dayIndex]);
        }


        QBarSet* set = new QBarSet("Giorni");
        for(int i=0; i<7; i++){
            if(vettore_trigger->at(i)){
                *set<<1;
            }
            else{
                *set<<0;
            }
        }
        set->setColor(Qt::red);
        serie->append(set);
        chart->setTitle("Giorni della settimana in cui è scattato l'allarme");
        axisX->append(reorderedDays);
        axisY->setGridLineVisible(false);
        axisY->setVisible(false);
    }

    chart->addSeries(serie);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    serie->attachAxis(axisX);
    serie->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart, chartPlaceHolder);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setGeometry(chartPlaceHolder->rect());
    chartView->show();

    //mainLayout->removeWidget(chartPlaceHolder);
    //mainLayout->addWidget(chartView);
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
    //chart->createDefaultAxes();

    //cambia nomi etichette asse x
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

/*
    QCategoryAxis* axisX = new QCategoryAxis();
    axisX->setTitleText("Giorni");
    axisX->setLabelsVisible(true);
    for(int i=0; i<n; ++i){
        if(customLabels[i] != ""){
            axisX->append(customLabels[i],i+0.5);
            //qDebug()<<customLabels[i];
        }
    }
    //axisX->setRange(0,n);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

*/

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("°C");
    chart->addAxis(axisY,Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart, chartPlaceHolder);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setGeometry(chartPlaceHolder->rect());
    chartView->show();

    //mainLayout->removeWidget(chartPlaceHolder);
    //mainLayout->addWidget(chartView);
}

void chartAria::on_crea_grafico_clicked(){
    //n, min, max, soglia
    int n = PeriodoDati[this->combo_dati->currentText()];
    sensore_aria* tmpSensore = dynamic_cast<sensore_aria*>(const_cast<sensore*>(ptrSensore));

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
            qDebug() << min <<","<<soglia<<","<<max;
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
    //chart->legend()->setAlignment(Qt::AlignLeft);
    chart->legend()->setAlignment(Qt::AlignBottom);

    //chart->createDefaultAxes();

    //cambia nomi etichette asse x
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

/*
    QCategoryAxis* axisX = new QCategoryAxis();
    axisX->setTitleText("Giorni");
    axisX->setLabelsVisible(true);
    for(int i=0; i<n; ++i){
        if(customLabels[i] != ""){
            axisX->append(customLabels[i],i+0.5);
            //qDebug()<<customLabels[i];
        }
    }
    //axisX->setRange(0,n);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

*/

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("[µg/m^3]");
    axisY->setRange(min-1,max);
    chart->addAxis(axisY,Qt::AlignLeft);
    series->attachAxis(axisY);

    // Create the threshold line
    QLineSeries* thresholdLine = new QLineSeries();
    thresholdLine->append(-0.5, soglia);
    thresholdLine->append(n - 0.5, soglia);
    QPen pen(Qt::red);
    pen.setWidth(2);
    pen.setBrush(Qt::black);
    thresholdLine->setPen(pen);
    thresholdLine->setName("Soglia: " + QString::number(soglia) +" µg/m^3");

    // Add threshold line to the chart
    chart->addSeries(thresholdLine);
    thresholdLine->attachAxis(axisX);
    thresholdLine->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart, chartPlaceHolder);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setGeometry(chartPlaceHolder->rect());
    chartView->show();

    //mainLayout->removeWidget(chartPlaceHolder);
    //mainLayout->addWidget(chartView);
}

QColor mappaColori(double dir){
    double x = M_PI/8;
    if ((dir < x && dir >= 0) || (dir>=15*x && dir <= 16*x) ){
        return Qt::red;
    }
    else if(dir >= x && dir < 3*x){
        return QColor(255,165,0);
    }
    else if(dir >= 3*x && dir < 5*x){
        return Qt::yellow;
    }
    else if(dir >= 5*x && dir < 7*x){
        return Qt::green;
    }
    else if(dir >= 7*x && dir < 9*x){
        return Qt::darkGreen;
    }
    else if(dir >= 9*x && dir < 11*x){
        return Qt::cyan;
    }
    else if(dir >= 11*x && dir < 13*x){
        return Qt::blue;
    }
    else if(dir >= 13*x && dir < 15*x){
        return Qt::magenta;
    }
    else return Qt::gray;
}

void chartVent::on_crea_grafico_clicked(){
    //n, min, max, soglia
    int n = PeriodoDati[this->combo_dati->currentText()];
    sensore_vent* tmpSensore = dynamic_cast<sensore_vent*>(const_cast<sensore*>(ptrSensore));

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
        QMessageBox::warning(this,"Errore nei dati","min e max devono essere numeri reali");
        return;
    }

    tmpSensore->genera_dati(n);

    //estrai dati
    QVector<double>* vettore_dati = tmpSensore->getDati();
    QVector<bool>* vettore_trigger = tmpSensore->getTrigger();
    QVector<double>* vettore_direz = tmpSensore->getDirez();


    //crea grafico
    //crea il qchart
    QChart* chart = new QChart();

    int currentDay = QDate::currentDate().dayOfYear();

    QStringList customLabels;
    QStackedBarSeries *serieBarre = new QStackedBarSeries();

    if(n==7){
        QList<double> dummyCount;
        for (int i=0; i<n; i++){
            QDate date(1,1,1);
            date = date.addDays(currentDay+i-1-7);
            customLabels.append(date.toString("dd/MM"));

            QBarSet *set = new QBarSet(customLabels[i]);
            if(i>0) dummyCount.replace(i-1,0);
            dummyCount<<vettore_dati->at(i);
            set->append(dummyCount);
            //*set<<vettore_dati->at(i);
            set->setColor(mappaColori(vettore_direz->at(i)));
            serieBarre->append(set);
        }
        chart->setTitle("Velocità e direzione media giornaliera del vento");
    }
    else if(n==28){
        QList<double> dummyCount;
        customLabels<<"Settimana 1"<<"Settimana 2"<<"Settimana 3"<<"Settimana 4";
        for(int i=0; i<4; i++){
            QBarSet *set = new QBarSet(customLabels[i]);
            if(i>0)dummyCount.replace(i-1,0);
            double somma = 0;
            double dir = 0;
            for(int j=0; j<7; j++){
                somma += vettore_dati->at(i*7+j);
                dir += vettore_direz->at(i*7+j);
            }
            dummyCount.append(somma/7);
            set->append(dummyCount);
            //*set<<(somma/7);
            double avg_dir = dir/7;
            set->setColor(mappaColori(avg_dir));
            serieBarre->append(set);
        }
        chart->setTitle("Velocità e direzione media settimanale del vento");
    }
    else{
        QList<double> dummyCount;
        customLabels = {"Gen","Feb","Mar","Apr","Mag","Giu","Lug","Ago","Set","Ott","Nov","Dic"};
        QVector<int> GiorniPerMese = {31,28,31,30,31,30,31,31,30,31,30,31};
        int inizio = 0;

        for(int i=0; i<12; i++){
            QBarSet *set = new QBarSet(customLabels[i]);
            if(i>0)dummyCount.replace(i-1,0);

            double somma = std::accumulate(vettore_dati->begin() + inizio, vettore_dati->begin() + inizio + GiorniPerMese[i], 0.0);
            double avg_dir = std::accumulate(vettore_direz->begin() + inizio, vettore_direz->begin() + inizio + GiorniPerMese[i], 0.0);

            dummyCount.append(somma/GiorniPerMese[i]);
            //*set<<(somma/GiorniPerMese[i]);
            set->append(dummyCount);
            inizio+=GiorniPerMese[i];
            set->setColor(mappaColori(avg_dir/GiorniPerMese[i]));
            serieBarre->append(set);
        }
        chart->setTitle("Velocità e direzione media mensile del vento");
    }

    //QBarSeries* series = new QBarSeries();
    //creo set dei venti per modificare la legenda

    chart->addSeries(serieBarre);
    chart->legend()->setVisible(true);
    //chart->legend()->setAlignment(Qt::AlignLeft);
    chart->legend()->setAlignment(Qt::AlignBottom);

    //prima segno come non visible tutti gli elementi della legenda, poi aggiungo quelli personalizzati
    for(QLegendMarker* marker : chart->legend()->markers()){
        marker->setVisible(false);
    }

    //Setto barre vuote per modificare legenda
    qDebug()<<"1";
    QBarSet * setNord = new QBarSet("Nord");
    QBarSet * setNordEst = new QBarSet("NordEst");
    QBarSet * setEst= new QBarSet("Est");
    QBarSet * setSudEst= new QBarSet("SudEst");
    QBarSet * setSud= new QBarSet("Sud");
    QBarSet * setSudOvest = new QBarSet("SudOvest");
    QBarSet * setOvest = new QBarSet("Ovest");
    QBarSet * setNordOvest = new QBarSet("NordOvest");

    setNord->setColor(mappaColori(3.14/2));
    setNordEst->setColor(mappaColori(3.14/4));
    setEst->setColor(mappaColori(0));
    setSudEst->setColor(mappaColori(7*3.14/4));
    setSud->setColor(mappaColori(3*3.14/2));
    setSudOvest->setColor(mappaColori(5*3.14/4));
    setOvest->setColor(mappaColori(3.14));
    setNordOvest->setColor(mappaColori(3*3.14/4));

    setNord->append(0);
    setNordEst->append(0);
    setEst->append(0);
    setSudEst->append(0);
    setSud->append(0);
    setSudOvest->append(0);
    setOvest->append(0);
    setNordOvest->append(0);

    serieBarre->append(setNord);
    serieBarre->append(setNordEst);
    serieBarre->append(setEst);
    serieBarre->append(setSudEst);
    serieBarre->append(setSud);
    serieBarre->append(setSudOvest);
    serieBarre->append(setOvest);
    serieBarre->append(setNordOvest);

    qDebug()<<"2";

    //chart->createDefaultAxes();

    //cambia nomi etichette asse x
    /*
    QStringList customLabels;

    if(n==7){
        for(int i=0; i<n; ++i){
            QDate date(1,1,1);
            date = date.addDays(currentDay+i-1-7);
            customLabels.append(date.toString("dd/MM"));
        }
        chart->setTitle("Velocità medi giornaliera del vento");
    }
    else if(n==28){
        customLabels<<"Settimana 1"<<"Settimana 2"<<"Settimana 3"<<"Settimana 4";
        chart->setTitle("Velocità media settimanale del vento");
    }
    else{
        customLabels = {"Gen","Feb","Mar","Apr","Mag","Giu","Lug","Ago","Set","Ott","Nov","Dic"};
        chart->setTitle("Velocità media mensile del vento");
    }
*/
    int ValoriAnomali = vettore_trigger->count(true);

    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->setTitleText("Giorni oltre la soglia di velocità: "+QString::number(ValoriAnomali));
    axisX->append(customLabels);
    chart->addAxis(axisX, Qt::AlignBottom);
    serieBarre->attachAxis(axisX);

/*
    QCategoryAxis* axisX = new QCategoryAxis();
    axisX->setTitleText("Giorni");
    axisX->setLabelsVisible(true);
    for(int i=0; i<n; ++i){
        if(customLabels[i] != ""){
            axisX->append(customLabels[i],i+0.5);
            //qDebug()<<customLabels[i];
        }
    }
    //axisX->setRange(0,n);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

*/

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("[km/h]");
    axisY->setRange(min-1, max);
    chart->addAxis(axisY,Qt::AlignLeft);
    serieBarre->attachAxis(axisY);

    // Create the threshold line
    QLineSeries* thresholdLine = new QLineSeries();
    thresholdLine->append(-0.5, soglia);
    thresholdLine->append(n - 0.5, soglia);
    QPen pen(Qt::red);
    pen.setBrush(Qt::black);
    pen.setWidth(2);
    thresholdLine->setPen(pen);
    thresholdLine->setName("Soglia: " + QString::number(soglia) +" km/h");

    // Add threshold line to the chart
    chart->addSeries(thresholdLine);
    thresholdLine->attachAxis(axisX);
    thresholdLine->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart, chartPlaceHolder);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setGeometry(chartPlaceHolder->rect());
    chartView->show();

    //mainLayout->removeWidget(chartPlaceHolder);
    //mainLayout->addWidget(chartView);
}
