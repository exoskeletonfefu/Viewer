#pragma once
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <map>

#include "fieldwidget.h"

class MessageWidget: public QWidget {
    Q_OBJECT
public:
    MessageWidget(QString title, QWidget *parent = 0);
    void addField(FieldWidget *field);
    void updateField(QString title, int value);
private:
    QPushButton *toggleBtn;
    QWidget *fieldsW;
    std::map<QString, FieldWidget*> fields;
public slots:
    void slotClickedToggleBtn();
};
