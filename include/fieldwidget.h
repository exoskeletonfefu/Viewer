#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QTextBrowser>
#include <QListWidget>
#include <QComboBox>

#include "rapidjson/document.h"

class FieldWidget : public QWidget {
    Q_OBJECT
public:
    FieldWidget(rapidjson::Value *field, QWidget *parent = 0);
    void setTitleText(QString text);
    virtual void setEnabledValueW(bool) = 0;
    QString getTitleText() const;
    virtual void setField(rapidjson::Value *value) = 0;
    virtual void update() = 0;
protected:
    void initTitleW();
    void init();
    QTextBrowser *titleW;
    rapidjson::Value *field;
};

class NumbFW : public FieldWidget {
    Q_OBJECT
public:
    NumbFW(rapidjson::Value *field, QWidget *parent = 0);
    void setEnabledValueW(bool) override;
    void setField(rapidjson::Value *value) override;
    void update() override;
private:
    void checkCorrect(const QString &text);
    void initValueW();
    QLineEdit *valueW;
    int min;
    int max;
private slots:
    void slotTextChanged(const QString &text);
};

class EnumFW : public FieldWidget {
    Q_OBJECT
public:
    EnumFW(rapidjson::Value *field, QWidget *parent = 0);
    void setEnabledValueW(bool) override;
    void setField(rapidjson::Value *value) override;
    void update() override;
private:
    std::map<int, int> indeces;
    void initValueW();
    QComboBox *valueW;
};
