#include "fifostream.h"

// system includes
#include <algorithm>
#include <cstring>

FifoStream::FifoStream(QObject *parent) :
    QIODevice(parent)
{
    setOpenMode(QIODevice::ReadWrite);
}

qint64 FifoStream::bytesAvailable() const
{
    return m_buffer.size();
}

qint64 FifoStream::readData(char *data, qint64 maxlen)
{
    const int len = std::min(int(maxlen), int(m_buffer.size()));
    std::memcpy(data, m_buffer.data(), len);
    m_buffer.remove(0, len);
    return len;
}

qint64 FifoStream::writeData(const char *data, qint64 len)
{
    m_buffer.append(data, len);
    return len;
}
