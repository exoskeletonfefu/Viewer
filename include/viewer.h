#pragma once
#include <QObject>

#include "mainwindow.h"
#include "client.h"
#include "log.h"

class Viewer: public QObject {
    Q_OBJECT
public:
    Viewer();
    void show();
    Log *log;
private:
    QMainWindow *mainWindow;
    Client *client;
public slots:
    void slotAppendToLog(QString);
};
