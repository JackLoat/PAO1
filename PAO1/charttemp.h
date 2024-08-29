#ifndef CHARTTEMP_H
#define CHARTTEMP_H

#include "chartBox.h"

class chartTemp : public chartBox {
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

#endif // CHARTTEMP_H
