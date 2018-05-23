#include "log.h"

void Log::append(const QString &text) {
    QStringList::append(text);
    qDebug() << text;
    emit signAppended(text);
}
