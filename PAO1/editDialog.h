#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QWidget>
#include <QAbstractItemView>

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>

class editDialog : public QDialog{
    Q_OBJECT

private slots:

    void acceptChanges();

protected:

    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonsLayout;

    QLineEdit* editNome;
    QLineEdit* editStanza;
    QComboBox* comboTipo;

    QPushButton *okButton;
    QPushButton *cancelButton;

public:

    editDialog(QWidget* parent = nullptr);

    void setLabelsText(const QString &newNome, const QString &newStanza, const QString &newTipo);
    QString getNome() const;
    QString getStanza() const;
    QString getTipo() const;

};

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

#endif // EDITDIALOG_H
