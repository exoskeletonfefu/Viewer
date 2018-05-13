#include <QPushButton>
#include <QLayout>
#include <map>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
//    layout()->setMargin(0);
//    layout()->setContentsMargins(0, 0, 0, 0);
//    layout()->setSpacing(0);
    ui->outputWidget->setFixedWidth(200);
    ui->inputWidget->setFixedWidth(200);

    QVBoxLayout *hbl = new QVBoxLayout;
    hbl->setAlignment(Qt::AlignTop);
    hbl->setMargin(0);
    hbl->setContentsMargins(0, 0, 0, 0);
    hbl->setSpacing(0);
    ui->inputWidget->widget()->setLayout(hbl);
    setAttribute(Qt::WA_LayoutUsesWidgetRect);
//    ui->inputWidget->setAttribute(Qt::WA_LayoutUsesWidgetRect);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::appendToLog(QString text) {
    ui->textBrowser->append(text);
}

void MainWindow::updateNumber(QString msgTitle, QString title, int value) {
//    Field *field = ui->inputWidget->widget()->layout()->findChild<Field*>(title);
//    auto &field = fields.find(title);
    if (inputMessages.find(msgTitle) != inputMessages.end())
        inputMessages.at(msgTitle)->updateField(title, value);
    else {
        MessageWidget *msg = new MessageWidget(msgTitle);
        inputMessages.emplace(msgTitle, msg);
        ui->inputWidget->widget()->layout()->addWidget(msg);
        FieldWidget *field = new FieldWidget(title, value);
        msg->addField(field);
    }
}

//void MainWindow::newNumber(QString msgTitle, QString title) {
////    FieldWidget *field = new FieldWidget(title);
////    field->setObjectName(title);
////    fields.emplace(title, field);

////    QPushButton *pb = new QPushButton;
////    ui->inputWidget->widget()->layout()->addWidget(pb);

////    MessageWidget *mw = new MessageWidget("tmp");
////    mw->addField(field);
////    ui->inputWidget->widget()->layout()->addWidget(mw);
//    MessageWidget *msg;
//    if (inputMessages.find(msgTitle) == inputMessages.end()) {
//        msg = new MessageWidget(msgTitle);
//        inputMessages.emplace(msgTitle, msg);
//        ui->inputWidget->widget()->layout()->addWidget(msg);
//    }
//    else
//        msg = inputMessages.at(msgTitle);

//    FieldWidget *field = new FieldWidget(title);
//    msg->addField(field);
//}
