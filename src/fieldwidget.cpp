#include <QLayout>
#include <cmath>

#include "fieldwidget.h"

using namespace rapidjson;

FieldWidget::FieldWidget(rapidjson::Value *field, QWidget *parent) :
    QWidget(parent) {
    this->field = field;

    initTitleW();
//    initValueW();
    init();
}

void FieldWidget::initTitleW() {
    titleW = new QTextBrowser(this);
    titleW->setFixedWidth(100);
    titleW->setText((*field)["title"].GetString());

//    int height = std::ceil(titleW->toPlainText().size() / titleW->width()) * 30;
//    titleW->setFixedHeight(height);
    titleW->setFixedHeight(45);
//    titleW->setEnabled(false);
//    titleW->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
}

void FieldWidget::init() {
    QHBoxLayout *hbl = new QHBoxLayout;
    hbl->addWidget(titleW);
//    hbl->addWidget(valueW);
    hbl->setMargin(0);
    hbl->setContentsMargins(0, 0, 0, 0);
    hbl->setSpacing(0);
    setLayout(hbl);
}

void FieldWidget::setTitleText(QString text) {
    titleW->setText(text);
}

QString FieldWidget::getTitleText() const {
    return titleW->toPlainText();
}

NumbFW::NumbFW(rapidjson::Value *field, QWidget *parent) :
    FieldWidget(field, parent) {
    initValueW();
    layout()->addWidget(valueW);
}

void NumbFW::initValueW() {
    valueW = new QLineEdit(this);
    min = (*field)["min"].GetInt();
    max = (*field)["max"].GetInt();
    connect(valueW, SIGNAL(textChanged(QString)), this, SLOT(slotTextChanged(QString)));
    valueW->setText(QString::number((*field)["value"].GetInt()));
    valueW->setEnabled(false);
    valueW->setValidator(new QIntValidator(-999999, 999999, this));
    valueW->setFixedHeight(45);
}

void NumbFW::slotTextChanged(const QString &text) {
    checkCorrect(text);
}

void NumbFW::checkCorrect(const QString &text) {
    if ((text.toInt() < min || text.toInt() > max) && min != max)
        valueW->setStyleSheet("QLineEdit { background-color: red }");
    else
        valueW->setStyleSheet("QLineEdit { background-color: white }");
}

void NumbFW::setField(rapidjson::Value *value) {
    field = value;
    min = (*field)["min"].GetInt();
    max = (*field)["max"].GetInt();
    titleW->setText((*field)["title"].GetString());
    valueW->setText(QString::number((*field)["value"].GetInt()));
}

void NumbFW::update() {
    (*field)["value"].SetInt(valueW->text().toInt());
}

void NumbFW::setEnabledValueW(bool param) {
    valueW->setEnabled(param);
}

EnumFW::EnumFW(rapidjson::Value *field, QWidget *parent) :
    FieldWidget(field, parent) {
    initValueW();
    layout()->addWidget(valueW);
}

void EnumFW::initValueW() {
    valueW = new QComboBox(this);
    int index = 0;
    for (auto &item: (*field)["items"].GetArray()) {
        valueW->insertItem(index, item["title"].GetString(), item["value"].GetInt());
        indeces.emplace(item["value"].GetInt(), index);
        index++;
    }
//    valueW->setCurrentIndex(indeces.at((*field)["currentItem"].GetInt()));
    valueW->setEnabled(false);
}

void EnumFW::setField(rapidjson::Value *value) {
    field = value;
    titleW->setText((*field)["title"].GetString());
    int currentItem = (*field)["currentItem"].GetInt();
    if (indeces.find(currentItem) != indeces.end()) {
        valueW->setCurrentIndex(indeces.at(currentItem));
        valueW->setStyleSheet("QComboBox { background-color: white }");
    }
    else {
        valueW->setStyleSheet("QComboBox { background-color: red }");
        valueW->setCurrentIndex(0);
    }
}

void EnumFW::update() {
    (*field)["currentItem"].SetInt(valueW->itemData(valueW->currentIndex()).toInt());
}

void EnumFW::setEnabledValueW(bool param) {
    valueW->setEnabled(param);
}
