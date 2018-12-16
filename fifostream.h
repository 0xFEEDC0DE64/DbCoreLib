#pragma once

#include "dbcorelib_global.h"
#include <QIODevice>

#include <QByteArray>

class DBCORELIB_EXPORT FifoStream : public QIODevice
{
    Q_OBJECT

public:
    FifoStream(QObject *parent = Q_NULLPTR);

    qint64 bytesAvailable() const Q_DECL_OVERRIDE;

protected:
    qint64 readData(char *data, qint64 maxlen) Q_DECL_OVERRIDE;
    qint64 writeData(const char *data, qint64 len) Q_DECL_OVERRIDE;

private:
    QByteArray m_buffer;
};
