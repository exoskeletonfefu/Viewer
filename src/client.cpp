#include <QDataStream>
#include <iostream>

#include "client.h"

using namespace std;

Client::Client(QObject *parent) :
    QObject(parent) {
    blockSize = 0;
}

void Client::start() {
    socket = new QTcpSocket();
    emit signAppendToLog("A new socket created!");

    connect(socket, SIGNAL(connected()), this, SLOT(slotConnected()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()), Qt::DirectConnection);
    connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)), Qt::DirectConnection);

//    connect(socket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
//    connect(socket, SIGNAL(connected()), this, SLOT(slotConnected()));
//    connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
//    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));

//    socket->connectToHost("127.0.0.1", 1234);
    socket->connectToHost("172.20.10.12", 1234);

//    exec();
}

void Client::slotError(QAbstractSocket::SocketError socketError) {
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

void Client::slotConnected() {
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

void Client::slotWrite(std::string data) {
    socket->write(data.data(), data.size());
}

void Client::slotDisconnected() {
    emit signAppendToLog("Disconnected");
    socket->deleteLater();
//    exit(0);
}
