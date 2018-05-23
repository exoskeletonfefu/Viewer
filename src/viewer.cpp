#include "viewer.h"

using namespace rapidjson;

Viewer::Viewer() {
    mainWindow = new MainWindow;
    client = new Client;
    log = new Log;

    connect(log, SIGNAL(signAppended(QString)), mainWindow, SLOT(slotAppendToLog(QString)));
    connect(client, SIGNAL(signAppendToLog(QString)), this, SLOT(slotAppendToLog(QString)));
    connect(client, SIGNAL(signReaded(QString)), this, SLOT(slotParseMessage(QString)));
//    connect(client, SIGNAL(finished()), client, SLOT(deleteLater()));
    connect(mainWindow, SIGNAL(signWriteMessage(std::string)), client, SLOT(slotWrite(std::string)));

    client->start();
}

void Viewer::show() {
    mainWindow->show();
}

void Viewer::slotAppendToLog(QString data) {
    log->append(data);
}

void Viewer::slotParseMessage(QString data) {
    Document document;
    document.Parse(data.toStdString().data());
    document.GetObject();
    Value &command = document["command"];
    Value &id = document["id"];
    switch (command.GetInt()) {
    case Command::INIT: {
        mainWindow->createNewMessage(data, id.GetInt());
        break;
    }
    case Command::STATE: {
        mainWindow->updateMessage(data, id.GetInt());
        break;
    }
    case Command::CONTROL: {
        mainWindow->createNewControlMessage(data, id.GetInt());
        break;
    }
    }
}
