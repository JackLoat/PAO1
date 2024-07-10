#ifndef CHARTBOX_H
#define CHARTBOX_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QCategoryAxis>
#include <QStackedBarSeries>
#include <QLegendMarker>
#include <cmath>
#include <QLabel>
#include <QMap>
#include <QMessageBox>

class sensore;
//#include "sensori.h"

class chartBox : public QWidget {   //da usare per il sensore di fumo
    Q_OBJECT
public:
    chartBox(QWidget* parent=nullptr, const sensore* sensor=nullptr);
    virtual ~chartBox();
private slots:
    //void generateChart() funzione che genera il grafico esatto?

    virtual void on_crea_grafico_clicked();

protected:
    const sensore* ptrSensore;
    //QChartView * chartView;
    QWidget* chartPlaceHolder;
    QPushButton* crea_grafico;
    QComboBox* combo_dati;

    QVBoxLayout* mainLayout;
    QHBoxLayout* formLayout;
};

class chartTemp : public chartBox{  //aggiunge min e max
    Q_OBJECT
public:
    chartTemp(QWidget* parent=nullptr, const sensore* sensor=nullptr);
    ~chartTemp() override;
private slots:
    //void generateChart() funzione che genera il grafico esatto?
    virtual void on_crea_grafico_clicked() override;

protected:
    QLabel* hmin;
    QLabel* hmax;
    QLineEdit* min;
    QLineEdit* max;

    QHBoxLayout* formLayout2;
};

class chartAria : public chartTemp{//aggiunge soglia, forse basterà questo anche per il vento
  Q_OBJECT
public:
    chartAria(QWidget* parent=nullptr, const sensore* sensor=nullptr);
    ~chartAria() override;
private slots:
    //void generateChart() funzione che genera il grafico esatto?
    void on_crea_grafico_clicked() override;

protected:
    QLabel* hsoglia;
    QLineEdit* soglia;
};


class chartVent : public chartAria{
    Q_OBJECT
public:
    chartVent(QWidget* parent=nullptr, const sensore* sensor=nullptr);
    ~chartVent() override;
private slots:
    void on_crea_grafico_clicked() override;
};

#endif // CHARTBOX_H
