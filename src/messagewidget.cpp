#include <QLayout>
#include <QDebug>

#include "messagewidget.h"

using namespace rapidjson;

MessageWidget::MessageWidget(QWidget *parent) :
    QWidget(parent) {

    toggleBtn = new QPushButton(this);
//    toggleBtn->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    initFieldsPanel();
    initWidgetsPanel();
    init();

    connect(toggleBtn, SIGNAL(clicked()), this, SLOT(slotClickedToggleBtn()));
//    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
}

void MessageWidget::initWidgetsPanel() {
    widgetsPanel = new QWidget(this);
    widgetsPanel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(fieldsPanel);
    layout->setAlignment(Qt::AlignBottom);
    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    widgetsPanel->setLayout(layout);
}

void MessageWidget::initFieldsPanel() {
    fieldsPanel = new QWidget(this);
    fieldsPanel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop);
    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    fieldsPanel->setLayout(layout);
}

void MessageWidget::init() {
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(toggleBtn);
    layout->addWidget(widgetsPanel);
    layout->setAlignment(Qt::AlignTop);
    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);
}


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
