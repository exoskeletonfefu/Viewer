#pragma once
#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QThreadPool>

class Client: public QObject {
    Q_OBJECT
public:
    Client(QObject *parent = 0);
//    int write(std::string data);
    void start();
private:
    QTcpSocket *socket;
    quint16 blockSize;
    QByteArray currentBlock;
signals:    
    void signAppendToLog(QString);
    void signReaded(QString);
public slots:
    void slotWrite(std::string);
    void slotConnected();
    void slotDisconnected();
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError socketError);
};
