#pragma once

#include "../init/macros.h"
#include "logutil.h"
#include <streambuf>

#define DEFAULT_SENDER "RAL-LOG"
#define DEFAULT_FORMAT "%x %H:%M:%S"

namespace log
{
    class NOT_EXPORTED LogStreamBuf : public std::streambuf
    {
    private:
        bool m_lineBegin;
        LogLevel m_level;
        const char* m_sender;
        const char* m_format;
        std::streambuf *m_pBuf;

    public:
        explicit LogStreamBuf(std::streambuf *pBuf);

        void resetPrefix();

        inline void setLevel(LogLevel level) { m_level = level; }
        inline void setSender(const char* sender) { m_sender = (sender != "")?sender:DEFAULT_SENDER; }
        inline void setTimestampFormat(const char* format) { m_format = (format != "")?format:DEFAULT_FORMAT; }

    protected:
        int_type overflow(int_type c = traits_type::eof());
    };
}