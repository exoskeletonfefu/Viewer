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
//    void parseCommand(Command::Type command, rapidjson::Document &document);
private:
    QMainWindow *mainWindow;
    MainWindow *mainWindow;
    Client *client;
signals:
public slots:
    void slotAppendToLog(QString);
};
