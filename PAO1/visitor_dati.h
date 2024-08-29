#ifndef VISITOR_DATI_H
#define VISITOR_DATI_H

#include "visitor.h"

#include <QChart>
#include <QLegendMarker>
#include <QtCharts/QLineSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QStackedBarSeries>

class visitor_dati : public visitor{
    //test
private:
    int periodo_dati;
    int min;
    int max;
    int soglia;
    QChart* chart;
public:
    visitor_dati();
    visitor_dati(int n);
    visitor_dati(int n, int m, int M);
    visitor_dati(int n, int m, int M, int s);

    void visit(sensore_temp* temp) override;
    void visit(sensore_fumo* fumo) override;
    void visit(sensore_aria* aria) override;
    void visit(sensore_vent* vent) override;
    QChart* getChart();
    /*
    void setPeriodoDati(int n);
    void setMin(int m);
    void setMax(int M);
    void setSoglia(int s);*/
};

#endif // VISITOR_DATI_H
