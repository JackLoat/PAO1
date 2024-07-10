#ifndef sensorBox_H
#define sensorBox_H

#include "sensori.h"
//#include "mainwindow.h"
#include "editDialog.h"
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QMessageBox>

class sensorBox : public QGroupBox {
    Q_OBJECT

public:
    explicit sensorBox(QWidget *parent = nullptr);
    QLabel *Htipo;
    QLabel *HdataC;
    QLabel *Hcollezione;
    QLabel *Hstanza;
    QLabel *tipo;
    QLabel *dataC;
    QLabel *collezione;
    QLabel *stanza;
    QLabel *icona;


    void connectButtons();
    void reset();
    QPushButton *rimuovi;
    QPushButton *modifica;

signals:
    void removeItem(QListWidgetItem* item);
    void modificaChartContainer(chartBox* newChartBox);
    void resetChartBox();

private slots:
    void on_modifica_clicked();
    void onRimuoviClicked();

private:



    QVBoxLayout *mainLayout;
};

#endif // CUSTOMGROUPBOX_H

