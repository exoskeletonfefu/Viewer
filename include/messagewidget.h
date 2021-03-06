#pragma once
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <map>
#include <string>

#include "fieldwidget.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

namespace Field {
enum Type {
    NUMBER = 0,
    ENUM = 1
};
}

class MessageWidget: public QWidget {
    Q_OBJECT
public:
    MessageWidget(QWidget *parent = 0);
    void updateFields(QString data);
    void parseDocument(QString data);
protected:
    void initWidgetsPanel();
    void initFieldsPanel();
    void init();
    virtual void addField(FieldWidget *field);
//    void updateField(QString title, int value);
    QPushButton *toggleBtn;
    QWidget *widgetsPanel;
    QWidget *fieldsPanel;
    std::map<QString, FieldWidget*> fields;
    rapidjson::Document document;
public slots:
    void slotClickedToggleBtn();
};

class ControlMessageWidget: public MessageWidget {
    Q_OBJECT
public:
    ControlMessageWidget(QWidget *parent = 0);
    void addField(FieldWidget *field) override;
private:
    QPushButton *sendBtn;
signals:
    void signWriteData(std::string);
public slots:
    void slotClickedSendBtn();
};
