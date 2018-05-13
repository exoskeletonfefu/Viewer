#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include <QMainWindow>
#include <map>

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
private:
    Ui::MainWindow *ui;
    std::map<QString, MessageWidget*> inputMessages;
public slots:
    void appendToLog(QString text);
//    void newNumber(QString msgTitle, QString title);
    void updateNumber(QString msgTitle, QString title, int value);
};

#endif // MAINWINDOW_H
