#pragma once

#include "../init/macros.h"
#include "logstreambuf.h"
#include <ostream>

namespace log
{
    struct NOT_EXPORTED Sender
    {
    public:
        Sender(const char* sender) { m_sender = sender; }
        inline const char* get() { return m_sender; }
    private:
        const char* m_sender;
    };

    struct NOT_EXPORTED Format
    {
    public:
        Format(const char* format) { m_format = format; }
        inline const char* get() { return m_format; }
    private:
        const char* m_format;
    };

    class API LogStream : public std::ostream
    {
    public:
        LogStream(std::streambuf *pBuf);

        inline void setLogLevel(LogLevel level) { m_pBuf->setLevel(level); }
        inline void setSender(const char* sender) { m_pBuf->setSender(sender); }
        inline void setFormat(const char* format) { m_pBuf->setTimestampFormat(format); }

    private:
        LogStreamBuf* m_pBuf;
    };

    inline std::ostream& operator<<(std::ostream& os, const LogLevel level)
    {
        dynamic_cast<LogStream*>(&os)->setLogLevel(level);
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, Sender sender)
    {
        dynamic_cast<LogStream*>(&os)->setSender(sender.get());
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, Format format)
    {
        dynamic_cast<LogStream*>(&os)->setFormat(format.get());
        return os;
    }
}