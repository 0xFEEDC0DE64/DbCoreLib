#pragma once

#include <QIODevice>

#include <memory>

class QFile;

typedef struct z_stream_s z_stream;

class GzipDevice : public QIODevice
{
public:
    GzipDevice(QFile &file, QObject *parent = nullptr);
    ~GzipDevice() override;

    bool isSequential() const override;
    bool atEnd() const override;

protected:
    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;

private:
    QFile &m_file;
    static constexpr std::size_t m_readBufferSize { 32 * 1024 };
    char m_readBuffer[m_readBufferSize];
    const std::unique_ptr<z_stream> m_strm;
    int m_result;
};
