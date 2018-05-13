#include <QLayout>

#include "fieldwidget.h"

FieldWidget::FieldWidget(QString titleText, int valueText, QWidget *parent) :
    QWidget(parent) {
    titleTb = new QTextBrowser(this);
    titleTb->setFixedWidth(80);
    titleTb->setText(titleText);
//    titleTb->setFrameStyle(QFrame::NoFrame);

    valueTb = new QTextBrowser(this);
    valueTb->setText(QString::number(valueText));
//    valueTb->setFrameStyle(QFrame::NoFrame);

    setFixedHeight(30);

    QHBoxLayout *hbl = new QHBoxLayout;
    hbl->addWidget(titleTb);
    hbl->addWidget(valueTb);
//    hbl->addStretch();
    hbl->setMargin(0);
    hbl->setContentsMargins(0, 0, 0, 0);
    hbl->setSpacing(0);
    setLayout(hbl);
}

void FieldWidget::setTitleText(QString text) {
    titleTb->setText(text);
}

void FieldWidget::setValueText(QString text) {
    valueTb->setText(text);
}

void FieldWidget::setValueText(int text) {
    valueTb->setText(QString::number(text));
}

QString FieldWidget::getTitleText() const {
    return titleTb->toPlainText();
}
