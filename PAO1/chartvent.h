#ifndef CHARTVENT_H
#define CHARTVENT_H
#include "chartaria.h"

class chartVent : public chartAria{
    Q_OBJECT

private slots:

    void on_crea_grafico_clicked() override;

public:

    chartVent(QWidget* parent=nullptr, sensore* sensor=nullptr);
    ~chartVent() override;

};

#endif // CHARTVENT_H
