#pragma once
#include <QObject>
#include <QStringList>
#include <QDebug>

class Log: public QObject, public QStringList {
    Q_OBJECT
public:
    void append(const QString &text);
private:
signals:
    void signAppended(QString text);
public slots:
};
