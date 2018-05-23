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

void Client::slotReadyRead() {
    QByteArray data = socket->readAll();
    int index = 0;
    while (true) {
        if (blockSize == 0) {
            if (data.size() - index < 2)
                return;
            currentBlock.clear();
            blockSize = quint16((unsigned char)(data[index]) << 8 | (unsigned char)(data[index + 1]));
            index += 2;
        }
        if (data.size() - index < blockSize) {
            currentBlock.append(data.mid(index, -1));
            blockSize -= data.size() - index;
            return;
        }
        currentBlock.append(data.mid(index, blockSize));
        index += blockSize;
        blockSize = 0;

        emit signAppendToLog(currentBlock);
        emit signReaded(currentBlock);
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
