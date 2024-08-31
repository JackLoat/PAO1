#ifndef NSDIALOG_H
#define NSDIALOG_H

#include "editDialog.h"

#include <QFile>
#include <QMessageBox>
#include <QFileDialog>

class nsDialog : public editDialog{
    Q_OBJECT

private slots:

    void on_carica_collezione_clicked();
    void on_nuova_collezione_clicked();

protected:

    QHBoxLayout* buttonsLayout2;

    QPushButton* carica_collezione;
    QPushButton* nuova_collezione;
    QString path_collezione;
    bool optNuova;

    void accept() override;

public:

    nsDialog(QWidget* parent = nullptr);

    const QString& getPathColl() const;
    void setPathColl(const QString& path);

    bool getOptNuova() const;

};

#endif // NSDIALOG_H
