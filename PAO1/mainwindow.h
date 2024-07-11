#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "editDialog.h"
#include <QMap>
#include <QWidget>
#include "sensori.h"
#include "ui_mainwindow.h"
#include "sensorBox.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileInfo>
#include <QSplitter>
#include <QLineEdit>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCarica_collezione_clicked();
    void on_sensorClicked(QListWidgetItem* item);
    void onRemoveItem(QListWidgetItem* item);
    void onAggiungi_sensore_clicked();
    void onModificaChartContainer(chartBox* newChartBox);
    void resetChartBox();
    void onRicerca();
    //void on_Genera_dati_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton* carica_collezione;
    QLabel* nome_collezione;
    QListWidget* mostra_sensori;
    QPushButton* aggiungi_sensore;
    sensorBox* box_sensore;
    QWidget* chartContainer;
    QLineEdit* barra_ricerca;
    //QPushButton* ricerca;

    void fileToWidgetList(const QString& path);
};

extern QMap<QString, int> periodoDati;

#endif // MAINWINDOW_H
