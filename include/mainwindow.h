#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include <QMainWindow>
#include <map>
#include <QThread>

//#include "fieldwidget.h"
#include "messagewidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createNewMessage(QString data, int id);
    void createNewControlMessage(QString data, int id);
    void updateMessage(QString data, int id);
private:
    void initInputWidget();
    void initOutputWidget();
    Ui::MainWindow *ui;
    std::map<int, MessageWidget*> inputMessages;
    std::map<int, ControlMessageWidget*> outputMessages;
signals:
    void signWriteMessage(std::string);
public slots:
    void slotWriteMessage(std::string);
    void slotAppendToLog(QString text);
};

#endif // MAINWINDOW_H
