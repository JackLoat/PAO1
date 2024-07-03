#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

class editDialog : public QDialog{
    Q_OBJECT

public:
    editDialog(QWidget* parent = nullptr);

    void setLabelsText(const QString &newNome, const QString &newStanza, const QString &newTipo);
    QString getNome() const;
    QString getStanza() const;
    QString getTipo() const;

private:
    QLineEdit* editNome;
    QLineEdit* editStanza;
    //QLineEdit* editTipo;
    QComboBox* comboTipo;

    QPushButton *okButton;
    QPushButton *cancelButton;

private slots:
    void acceptChanges();
};

#endif // EDITDIALOG_H
