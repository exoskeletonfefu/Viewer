#include <QPushButton>
#include <QLayout>
#include <map>
#include <iostream>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->logTextBrowser->setFixedWidth(400);

    initInputWidget();
    initOutputWidget();
}

void MainWindow::initInputWidget() {
    ui->inputWidget->setFixedWidth(250);
    QVBoxLayout *inputLayout = new QVBoxLayout;
    inputLayout->setAlignment(Qt::AlignTop);
    inputLayout->setMargin(0);
    inputLayout->setContentsMargins(0, 0, 0, 0);
    inputLayout->setSpacing(0);
    ui->inputWidget->widget()->setLayout(inputLayout);
}

void MainWindow::initOutputWidget() {
    ui->outputWidget->setFixedWidth(250);
    QVBoxLayout *outputLayout = new QVBoxLayout;
    outputLayout->setAlignment(Qt::AlignTop);
    outputLayout->setMargin(0);
    outputLayout->setContentsMargins(0, 0, 0, 0);
    outputLayout->setSpacing(0);
    ui->outputWidget->widget()->setLayout(outputLayout);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::slotAppendToLog(QString text) {
    ui->logTextBrowser->append(text);
}

void MainWindow::createNewMessage(QString data, int id) {
    MessageWidget *msg = new MessageWidget();
    msg->parseDocument(data);
    inputMessages.emplace(id, msg);
    ui->inputWidget->widget()->layout()->addWidget(msg);
}

void MainWindow::updateMessage(QString data, int id) {
    MessageWidget *msg = inputMessages.at(id);
    msg->updateFields(data);
}

void MainWindow::createNewControlMessage(QString data, int id) {
    ControlMessageWidget *msg = new ControlMessageWidget();
    msg->parseDocument(data);
    connect(msg, SIGNAL(signWriteData(std::string)), this, SLOT(slotWriteMessage(std::string)));
    outputMessages.emplace(id, msg);
    ui->outputWidget->widget()->layout()->addWidget(msg);
}

void MainWindow::slotWriteMessage(std::string data) {
    emit signWriteMessage(data);
}

