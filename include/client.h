#pragma once
#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QThreadPool>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

class Client: public QThread {
class Client: public QObject {
    Q_OBJECT
public:
    Client();
    void run();
    Client(QObject *parent = 0);
    void start();
private:
    QTcpSocket *socket;
    quint16 blockSize;
    QByteArray currentBlock;

//    void parseInt()
//    void parseCommand(int command, rapidjson::Document document);
//    void parseStateCommand(rapidjson::Value fields);
//    void parseInitCommand(rapidjson::Value fields);
signals:
    void newNumber(QString, QString);
    void updateNumber(QString, QString, int);
    void signAppendToLog(QString);
public slots:
    void connected();
    void disconnected();
    void readyRead();
    void error(QAbstractSocket::SocketError socketError);
};
