#ifndef MODSENSORE_H
#define MODSENSORE_H

#include <QDialog>

class ModSensore : public QDialog{
    Q_OBJECT

public:
    explicit ModSensor(QWidget* parent = nullptr);
    ~Dialog();

    QString newNome() const;
    QString newTipo() const;
    QString newStanza() const;
    QString newCollezione() const;


};

#endif // MODSENSORE_H
