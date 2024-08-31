#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QWidget>
#include <QAbstractItemView>

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
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



#endif // EDITDIALOG_H
