#ifndef CHARTARIA_H
#define CHARTARIA_H
#include "charttemp.h"

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

#endif // CHARTARIA_H
