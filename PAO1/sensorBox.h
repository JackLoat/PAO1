#ifndef sensorBox_H
#define sensorBox_H

#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QMessageBox>

#include "sensorefumo.h"
#include "sensorevent.h"
#include "collezione.h"
#include "editDialog.h"
#include "visitor_grafico.h"

class chartBox;

class sensorBox : public QGroupBox {
    Q_OBJECT

private:

    QHBoxLayout *mainLayout;

    QLabel *Htipo;
    QLabel *HdataC;
    QLabel *Hcollezione;
    QLabel *Hstanza;

    QLabel *tipo;
    QLabel *dataC;
    QLabel *collezione;
    QLabel *stanza;
    QLabel *icona;

    QPushButton *rimuovi;
    QPushButton *modifica;

    void connectButtons();

private slots:

    void on_modifica_clicked();
    void onRimuoviClicked();

public:

    explicit sensorBox(QWidget *parent = nullptr);
    ~sensorBox();

    void setTipo(const QString& t);
    void setData(const QString& d);
    void setColl(const QString& c);
    void setStanza(const QString& s);
    void setIcona(QPixmap);

    QString getTipo() const;
    QString getData() const;
    QString getColl() const;
    QString getStanza() const;
    QPixmap getIcona() const;

    void disabilitaModifica(const bool& x);
    void disabilitaRimuovi(const bool& x);

    void reset();

signals:

    void removeItem(QListWidgetItem* item);
    void modificaChartContainer(chartBox* newChartBox);
    void resetChartBox();

};

#endif // CUSTOMGROUPBOX_H

