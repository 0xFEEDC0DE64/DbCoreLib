#include "waverecorder.h"

// Qt includes
#include <QVector>

// system includes
#include <stdexcept>

WaveRecorder::WaveRecorder(const quint16 channels, const quint32 frequency, const QString &filename) :
    m_file(filename),
    m_dataStream(&m_file)
{
    m_dataStream.setByteOrder(QDataStream::LittleEndian);

    if(!m_file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        throw std::runtime_error(QString("Could open file %0 because %1").arg(m_file.fileName(), m_file.errorString()).toStdString());

    m_dataStream << quint8('R') << quint8('I') << quint8('F') << quint8('F');
    m_dataStream << quint32(0);

    m_dataStream << quint8('W') << quint8('A') << quint8('V') << quint8('E');

    m_dataStream << quint8('f') << quint8('m') << quint8('t') << quint8(' ');
    m_dataStream << quint32(16);
    m_dataStream << quint16(1); // audio format (pcm)
    m_dataStream << channels;
    m_dataStream << frequency;
    m_dataStream << quint32(frequency * channels * sizeof(qint32)); // byte rate
    m_dataStream << quint16(sizeof(qint32) * channels); // block align
    m_dataStream << quint16(sizeof(qint32) * 8); // bits per sample

    m_dataStream << quint8('d') << quint8('a') << quint8('t') << quint8('a');
    m_dataStream << quint32(0);

    m_dataStream.setByteOrder(QDataStream::BigEndian);
}

void WaveRecorder::addSample(const qint32 sample)
{
    m_dataStream << sample;
}

void WaveRecorder::addSamples(const QVector<qint32> &samples)
{
    for(auto sample : samples)
        addSample(sample);
}
