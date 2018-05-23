#pragma once
#include <QObject>

#include "mainwindow.h"
#include "client.h"
#include "log.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

namespace Command {
enum Type {
    INIT    = 0,
    STATE   = 1,
    CONTROL = 2
};
}

class Viewer: public QObject {
    Q_OBJECT
public:
    Viewer();
    void show();
    Log *log;
//    void parseCommand(Command::Type command, rapidjson::Document &document);
private:
    MainWindow *mainWindow;
    Client *client;
signals:
public slots:
    void slotAppendToLog(QString);
    void slotParseMessage(QString);
};
