#ifndef CHARTBOX_H
#define CHARTBOX_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QAbstractItemView>
#include <QLabel>
#include <QMap>

#include "visitor_dati.h"

class sensore;

extern QMap<QString, int> PeriodoDati;

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

#endif // CHARTBOX_H
