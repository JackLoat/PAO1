#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileInfo>
#include <QSplitter>
#include <QLineEdit>
#include <QPixmap>
#include <QShortcut>
#include <QGraphicsDropShadowEffect>

#include "sensorevent.h"
#include "sensorefumo.h"
#include "ui_mainwindow.h"
#include "sensorBox.h"
#include "visitor_grafico.h"
#include "nsdialog.h"
#include "collezione.h"
#include "chartvent.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    Ui::MainWindow *ui;
    QPushButton* carica_collezione;
    QLabel* nome_collezione;
    QPushButton* rimuovi_collezione;
    QListWidget* mostra_sensori;
    QPushButton* aggiungi_sensore;
    sensorBox* box_sensore;
    QWidget* chartContainer;
    QLineEdit* barra_ricerca;

    void fileToWidgetList(const QString& path);

private slots:

    void onCarica_collezione_clicked();
    void onRimuoviCollezioneClicked();
    void on_sensorClicked(QListWidgetItem* item);
    void onRemoveItem(QListWidgetItem* item);
    void onAggiungi_sensore_clicked();
    void onModificaChartContainer(chartBox* newChartBox);
    void resetChartBox();
    void onRicerca();

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

};

#endif // MAINWINDOW_H
