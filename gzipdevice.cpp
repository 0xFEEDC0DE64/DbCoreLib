#include "gzipdevice.h"

#include <QFile>

#include <stdexcept>

#include <zlib.h>

GzipDevice::GzipDevice(QFile &file, QObject *parent) :
    QIODevice(parent),
    m_file(file),
    m_strm(std::make_unique<z_stream>())
{
    if (!m_file.isOpen())
        throw std::runtime_error("file is not open");

    setOpenMode(QIODevice::ReadOnly);

    // Prepare inflater status
    m_strm->zalloc = Z_NULL;
    m_strm->zfree = Z_NULL;
    m_strm->opaque = Z_NULL;
    m_strm->avail_in = 0;
    m_strm->next_in = Z_NULL;

    // Initialize inflater
    m_result = inflateInit2(m_strm.get(), 15 + 16);
    if (m_result != Z_OK)
        throw std::runtime_error("could not init z_stream");
}

GzipDevice::~GzipDevice()
{
    inflateEnd(m_strm.get());
}

bool GzipDevice::isSequential() const
{
    return true;
}

bool GzipDevice::atEnd() const
{
    return m_result == Z_STREAM_END;
}

qint64 GzipDevice::readData(char *data, qint64 maxlen)
{
    if (m_strm->avail_in == 0)
    {
        m_strm->next_in = reinterpret_cast<unsigned char *>(m_readBuffer);
        m_strm->avail_in = m_file.read(m_readBuffer, m_readBufferSize);
    }

    m_strm->next_out = reinterpret_cast<unsigned char*>(data);
    m_strm->avail_out = maxlen;

    m_result = inflate(m_strm.get(), Z_NO_FLUSH);

    switch (m_result) {
    case Z_NEED_DICT:
        throw std::runtime_error("decompression failed: Z_NEED_DICT");
    case Z_DATA_ERROR:
        throw std::runtime_error("decompression failed: Z_DATA_ERROR");
    case Z_MEM_ERROR:
        throw std::runtime_error("decompression failed: Z_MEM_ERROR");
    case Z_STREAM_ERROR:
        throw std::runtime_error("decompression failed: Z_STREAM_ERROR");
    }

    return maxlen-m_strm->avail_out;
}

qint64 GzipDevice::writeData(const char *data, qint64 len)
{
    Q_UNUSED(data)
    Q_UNUSED(len)
    throw std::runtime_error("writing not allowed!");
    return -1;
}
