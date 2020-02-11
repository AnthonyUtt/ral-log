#pragma once

#include "../init/macros.h"
#include "logutil.h"
#include <streambuf>
#include <string.h>

#define DEFAULT_SENDER "RAL-LOG"
#define DEFAULT_FORMAT "%x %H:%M:%S.%Q"

namespace log
{
    class NOT_EXPORTED LogStreamBuf : public std::streambuf
    {
    private:
        bool m_lineBegin;
        LogLevel m_level;
        const char* m_sender;
        const char* m_format;
        bool m_ms;
        std::streambuf *m_pBuf;

    public:
        explicit LogStreamBuf(std::streambuf *pBuf);

        void resetPrefix();

        inline void setLevel(LogLevel level) { m_level = level; }
        inline void setSender(const char* sender) { m_sender = strcmp(sender, "")?sender:DEFAULT_SENDER; }
        inline void setTimestampFormat(const char* format) { m_format = strcmp(format, "")?format:DEFAULT_FORMAT; };

    protected:
        int_type overflow(int_type c = traits_type::eof());

    private:
        void parseFormat(const char* format, std::string& formatFront, std::string& formatBack);
    };
}