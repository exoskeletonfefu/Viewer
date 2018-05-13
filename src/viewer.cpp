#include "viewer.h"

Viewer::Viewer() {
    mainWindow = new MainWindow();
    client = new Client();
    log = new Log();
    connect(log, SIGNAL(appended(QString)), mainWindow, SLOT(appendToLog(QString)));
    connect(client, SIGNAL(signAppendToLog(QString)), this, SLOT(slotAppendToLog(QString)));
    connect(client, SIGNAL(updateNumber(QString, QString, int)), mainWindow, SLOT(updateNumber(QString, QString, int)));
    connect(client, SIGNAL(newNumber(QString, QString)), mainWindow, SLOT(newNumber(QString, QString)));
    connect(client, SIGNAL(finished()), client, SLOT(deleteLater()));
    client->start();
}

void Viewer::show() {
    mainWindow->show();
}

void Viewer::slotAppendToLog(QString data) {
    log->append(data);
}
