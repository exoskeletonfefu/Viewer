#pragma once

#include <QWidget>
#include <QTextBrowser>
#include <QListWidget>

class FieldWidget : public QWidget {
    Q_OBJECT
public:
    FieldWidget(QString titleText, int valueText, QWidget *parent = 0);
    void setTitleText(QString text);
    void setValueText(QString text);
    void setValueText(int text);
    QString getTitleText() const;
private:
    QTextBrowser *titleTb;
    QTextBrowser *valueTb;
};
