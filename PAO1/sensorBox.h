#ifndef sensorBox_H
#define sensorBox_H

#include "sensori.h"
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>

class sensorBox : public QGroupBox {
    Q_OBJECT

public:
    explicit sensorBox(QWidget *parent = nullptr);
    QLabel *tipo;
    QLabel *dataC;
    QLabel *collezione;
    QLabel *stanza;
    QLabel *icona;


    void connectButtons();
    void reset();
    QPushButton *rimuovi;

private slots:
    void on_modifica_clicked();
    void onRimuoviClicked();

private:
    QPushButton *modifica;


    QVBoxLayout *mainLayout;
};

#endif // CUSTOMGROUPBOX_H

