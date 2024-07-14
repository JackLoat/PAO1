#include "chartBox.h"
#include "sensori.h"

chartBox::chartBox(QWidget* parent, sensore* sensor):QWidget(parent){

    ptrSensore = sensor;
    crea_grafico = new QPushButton("Genera dati",this);
    combo_dati = new QComboBox(this);
    chartPlaceHolder = new QWidget(this);

    combo_dati->addItem("Ultima settimana");
    combo_dati->addItem("Ultimo mese");
    combo_dati->addItem("Ultimo anno");

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


chartAria::chartAria(QWidget* parent, sensore* sensor):chartTemp(parent,sensor){

    hsoglia = new QLabel("Soglia di sicurezza:",this);
    soglia = new QLineEdit(this);

    formLayout->addWidget(hsoglia);
    formLayout->addWidget(soglia);

}


chartVent::chartVent(QWidget* parent, sensore* sensor):chartAria(parent,sensor){}


chartBox::~chartBox(){

    delete chartPlaceHolder;
    delete crea_grafico;
    delete combo_dati;

    delete formLayout;
    delete mainLayout;


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


QMap<QString, int> PeriodoDati = {
    {"Ultima settimana", 7},
    {"Ultimo mese", 28},
    {"Ultimo anno", 365}
};


void chartBox::on_crea_grafico_clicked(){

    //setta parametri necessari in base ai campi del widget
    int n = PeriodoDati[combo_dati->currentText()];

    //fa generare i dati al sensore e estrae il vettore_trigger
    ptrSensore->genera_dati(n);

    const QVector<bool>* vettore_trigger;
    if(dynamic_cast<sensore_fumo*>(ptrSensore)){
        vettore_trigger = static_cast<sensore_fumo*>(ptrSensore)->getTrigger();
    }
    else{
        QMessageBox::critical(this,"Errore","Si è verificato un errore!");
        return;
    }

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
                if((*vettore_trigger)[i*7+j]) countTrue++;
            }
            *set<<countTrue;

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
                if ((*vettore_trigger)[index++]) countTrue++;
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


//soluzione poco elegante ma veloce da implementare e serve solo a mantenere più pulito la funzione seguente
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

    //setta parametri necessari in base ai campi del widget
    int n = PeriodoDati[combo_dati->currentText()];

    sensore_vent* tmpSensore;
    if(dynamic_cast<const sensore_vent*>(ptrSensore)){
        tmpSensore = static_cast<sensore_vent*>(const_cast<sensore*>(ptrSensore));
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

    //estrae dati dal sensore
    const QVector<double>* vettore_dati = tmpSensore->getDati();
    const QVector<bool>* vettore_trigger = tmpSensore->getTrigger();
    const QVector<double>* vettore_direz = tmpSensore->getDirez();

    //crea grafico
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
            //double dir = 0;
            double dirX = 0;
            double dirY = 0;

            for(int j=0; j<7; j++){
                double velocità = vettore_dati->at(i*7+j);
                double dir = vettore_direz->at(i*7+j);
                somma += velocità;
                dirX += velocità * std::cos(dir);
                dirY += velocità * std::sin(dir);
            }

            dummyCount.append(somma/7);

            set->append(dummyCount);
            //double avg_dir = dir/7;
            double avg_dir = std::atan2(dirY,dirX);
            if(avg_dir<0) avg_dir += 2*M_PI;
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

            double somma = 0;
            double dirX = 0;
            double dirY = 0;

            for(int j=0; j<GiorniPerMese[i]; j++){
                double velocità = vettore_dati->at(inizio+j);
                double dir = vettore_direz->at(inizio+j);
                somma += velocità;
                dirX += velocità * std::cos(dir);
                dirY += velocità * std::sin(dir);
            }

            dummyCount.append(somma/GiorniPerMese[i]);
            double avg_dir = std::atan2(dirY, dirX);
            if(avg_dir<0) avg_dir+= 2*M_PI;

            set->append(dummyCount);
            inizio+=GiorniPerMese[i];
            set->setColor(mappaColori(avg_dir));
            serieBarre->append(set);
        }
        chart->setTitle("Velocità e direzione media mensile del vento");
    }

    chart->addSeries(serieBarre);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    for(QLegendMarker* marker : chart->legend()->markers()){
        marker->setVisible(false);
    }

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

    int ValoriAnomali = vettore_trigger->count(true);

    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->setTitleText("Giorni oltre la soglia di velocità: "+QString::number(ValoriAnomali));
    axisX->append(customLabels);
    chart->addAxis(axisX, Qt::AlignBottom);
    serieBarre->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("[km/h]");
    axisY->setRange(min-1, max);
    chart->addAxis(axisY,Qt::AlignLeft);
    serieBarre->attachAxis(axisY);

    QLineSeries* thresholdLine = new QLineSeries();
    thresholdLine->append(-0.5, soglia);
    thresholdLine->append(n - 0.5, soglia);
    QPen pen(Qt::red);
    pen.setBrush(Qt::black);
    pen.setWidth(2);
    thresholdLine->setPen(pen);
    thresholdLine->setName("Soglia: " + QString::number(soglia) +" km/h");

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
