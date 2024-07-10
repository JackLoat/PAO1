#ifndef EDITDIALOG_H
#define EDITDIALOG_H

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

public:
    editDialog(QWidget* parent = nullptr);

    void setLabelsText(const QString &newNome, const QString &newStanza, const QString &newTipo);
    QString getNome() const;
    QString getStanza() const;
    QString getTipo() const;

protected:
    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonsLayout;

    QLineEdit* editNome;
    QLineEdit* editStanza;
    //QLineEdit* editTipo;
    QComboBox* comboTipo;

    QPushButton *okButton;
    QPushButton *cancelButton;

private slots:
    void acceptChanges();
};

class nsDialog : public editDialog{
    Q_OBJECT
public:
    nsDialog(QWidget* parent = nullptr);
    const QString& getPathColl() const;
    void setPathColl(const QString& path);

protected:
    void accept() override;

private:
    QHBoxLayout* buttonsLayout2;

    QPushButton* carica_collezione;
    QPushButton* nuova_collezione;
    QString path_collezione;

private slots:
    void on_carica_collezione_clicked();
    void on_nuova_collezione_clicked();
};

#endif // EDITDIALOG_H
