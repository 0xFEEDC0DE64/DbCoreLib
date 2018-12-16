#pragma once

#include "dbcorelib_global.h"
#include <QObject>

// Qt includes
#include <QFile>
#include <QDataStream>

// forward declarations
template <typename T> class QVector;

class DBCORELIB_EXPORT WaveRecorder : public QObject
{
    Q_OBJECT

public:
    explicit WaveRecorder(const quint16 channels, const quint32 frequency, const QString &filename);

public Q_SLOTS:
    void addSample(const qint32 sample);

private:
    quint32 m_size = 0;
    quint32 m_samplesCount = 0;
    quint32 m_time = 0;
    quint32 m_timeSamples = 0;

    QFile m_file;
    QDataStream m_dataStream;
};
