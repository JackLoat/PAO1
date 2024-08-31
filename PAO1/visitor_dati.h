#ifndef VISITOR_DATI_H
#define VISITOR_DATI_H

#include "visitor.h"

#include <QString>
#include <QVector>
#include <QDate>
#include <QStringList>
#include <QPen>
#include <QColor>

#include <QChart>
#include <QLegendMarker>
#include <QtCharts/QLineSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QStackedBarSeries>

class visitor_dati : public visitor{

private:
    int periodo_dati;
    double min;
    double max;
    double soglia;
    QChart* chart;
public:
    visitor_dati();
    visitor_dati(int n);
    visitor_dati(int n, double m, double M);
    visitor_dati(int n, double m, double M, double s);

    void visit(sensore_temp* temp) override;
    void visit(sensore_fumo* fumo) override;
    void visit(sensore_aria* aria) override;
    void visit(sensore_vent* vent) override;
    QChart* getChart();

};

#endif // VISITOR_DATI_H
