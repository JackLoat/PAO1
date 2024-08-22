#include "chartBox.h"
#include "sensorefumo.h"
#include "sensorevent.h"

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

