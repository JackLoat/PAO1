#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "editDialog.h"

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
    void on_carica_collezione_clicked();
    void on_sensorClicked(QListWidgetItem* item);
    void onRemoveItem(QListWidgetItem* item);
    void on_Aggiungi_sensore_clicked();

private:
    Ui::MainWindow *ui;
    void fileToWidgetList(const QString& path);
};
#endif // MAINWINDOW_H
