#include <QLayout>
#include <QDebug>

#include "messagewidget.h"

MessageWidget::MessageWidget(QString title, QWidget *parent) :
    QWidget(parent) {
//    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);

    toggleBtn = new QPushButton(title, this);
//    toggleBtn->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    fieldsW = new QWidget(this);
    fieldsW->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(toggleBtn);
    layout->addWidget(fieldsW);
    layout->setAlignment(Qt::AlignTop);
    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);

    QVBoxLayout *filedsWLayout = new QVBoxLayout;
    filedsWLayout->setAlignment(Qt::AlignTop);
    filedsWLayout->setMargin(0);
    filedsWLayout->setContentsMargins(0, 0, 0, 0);
    filedsWLayout->setSpacing(0);
    fieldsW->setLayout(filedsWLayout);

    connect(toggleBtn, SIGNAL(clicked()), this, SLOT(slotClickedToggleBtn()));
}

void MessageWidget::slotClickedToggleBtn() {
    if (fieldsW->isHidden())
        fieldsW->show();
    else
        fieldsW->hide();
}

void MessageWidget::addField(FieldWidget *field) {
    fields.emplace(field->getTitleText(), field);
    fieldsW->layout()->addWidget(field);
}

void MessageWidget::updateField(QString title, int value) {
    if (fields.find(title) != fields.end())
        fields.at(title)->setValueText(value);
}
