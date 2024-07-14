#ifndef CHARTBOX_H
#define CHARTBOX_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QMessageBox>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QStackedBarSeries>
#include <QLegendMarker>
#include <cmath>
#include <QLabel>
#include <QMap>


class sensore;


class chartBox : public QWidget {
    Q_OBJECT    

private slots:

    virtual void on_crea_grafico_clicked();

protected:

    sensore* ptrSensore;
    QWidget* chartPlaceHolder;
    QVBoxLayout* chartLayout;
    QPushButton* crea_grafico;
    QComboBox* combo_dati;

    QVBoxLayout* mainLayout;
    QHBoxLayout* formLayout;

public:

    chartBox(QWidget* parent=nullptr, sensore* sensor=nullptr);
    virtual ~chartBox();

};


class chartTemp : public chartBox{
    Q_OBJECT

private slots:

    virtual void on_crea_grafico_clicked() override;

protected:

    QLabel* hmin;
    QLabel* hmax;
    QLineEdit* min;
    QLineEdit* max;

    QHBoxLayout* formLayout2;

public:

    chartTemp(QWidget* parent=nullptr, sensore* sensor=nullptr);
    ~chartTemp() override;

};


class chartAria : public chartTemp{
    Q_OBJECT

private slots:

    void on_crea_grafico_clicked() override;

protected:

    QLabel* hsoglia;
    QLineEdit* soglia;

public:

    chartAria(QWidget* parent=nullptr, sensore* sensor=nullptr);
    ~chartAria() override;

};


class chartVent : public chartAria{
    Q_OBJECT

private slots:

    void on_crea_grafico_clicked() override;

public:

    chartVent(QWidget* parent=nullptr, sensore* sensor=nullptr);
    ~chartVent() override;

};

#endif // CHARTBOX_H
