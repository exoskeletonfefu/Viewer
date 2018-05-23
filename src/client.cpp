#include <QDataStream>
#include <iostream>

#include "client.h"

using namespace std;
using namespace rapidjson;

Client::Client() {
Client::Client(QObject *parent) :
    QObject(parent) {
    blockSize = 0;
}

void Client::run() {
void Client::start() {
    socket = new QTcpSocket();
    emit signAppendToLog("Client. A new socket created!");

//    connect(socket, SIGNAL(connected()), this, SLOT(connected()), Qt::DirectConnection);
//    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);
//    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
//    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)), Qt::DirectConnection);

    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));

    socket->connectToHost("127.0.0.1", 1234);
    exec();
//    exec();
}

void Client::error(QAbstractSocket::SocketError socketError) {
    switch (socketError) {
//    case QAbstractSocket::RemoteHostClosedError: {
//        emit signAppendToLog("Client. Error. Some");
//        break;
//    }
//    case QAbstractSocket::HostNotFoundError: {
//        emit signAppendToLog("Client. Error. The host was not found");
//        break;
//    }
//    case QAbstractSocket::ConnectionRefusedError: {
//        emit signAppendToLog("Client. Error. The connection was refused by the peer.");
//        break;
//    }
    default: {
        emit signAppendToLog("The following error occurred: " + socket->errorString());
    }
    }
}

void Client::connected() {
    emit signAppendToLog("Client. Connected event");
}

void Client::readyRead() {
    emit signAppendToLog("readyRead()");
    if (blockSize == 0) {        
        if (socket->bytesAvailable() < 2)
            return;
        currentBlock.clear();
        char *buf = new char[2];
        socket->read(buf, 2);
        blockSize = quint16((unsigned char)(buf[0]) << 8 | (unsigned char)(buf[1]));
    }
    if (socket->bytesAvailable() < blockSize)
        return;
    QByteArray data = socket->read(blockSize);
    currentBlock.append(data);
    blockSize -= data.size();
    if (blockSize != 0)
        return;
    emit signAppendToLog(currentBlock);

    Document document;
    document.Parse(currentBlock.toStdString().data());
    document.GetObject();
//    Value &command = document["command"];
    Value &fields = document["fields"];
    Value &title = document["title"];

    for (auto &field: fields.GetArray()) {
        switch (field["type"].GetInt()) {
        case 0: {
            emit updateNumber(title.GetString(), field["title"].GetString(), field["value"].GetInt());
            break;
        }
        default: {
            break;
        }
        }
    }
}

void Client::disconnected() {
    emit signAppendToLog("Client. Disconnected");
    socket->deleteLater();
    exit(0);
}
