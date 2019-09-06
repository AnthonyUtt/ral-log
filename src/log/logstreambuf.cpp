#include "logstreambuf.h"
#include <sstream>
#include <time.h>

namespace log
{
    LogStreamBuf::LogStreamBuf(std::streambuf *pBuf)
    {
        m_pBuf = pBuf;
        m_lineBegin = true;
        m_level = INFO;
        m_sender = DEFAULT_SENDER;
        m_format = DEFAULT_FORMAT;
    }

    void LogStreamBuf::resetPrefix()
    {
        m_sender = DEFAULT_SENDER;
        m_format = DEFAULT_FORMAT;
    }

    LogStreamBuf::int_type LogStreamBuf::overflow(int_type c)
    {
        int_type value = traits_type::not_eof(c);
        if (c != traits_type::eof())
        {
            if (m_lineBegin)
            {
                m_lineBegin = false;
                std::ostringstream oss;

                time_t curTime;
                struct tm *tmp;
                char timestamp[32];
                time(&curTime);
                tmp = localtime(&curTime);
                strftime(timestamp, sizeof(timestamp), m_format, tmp);

                oss << timestamp << " [";

                switch(m_level)
                {
                    case DEBUG: oss << color(WHITE);
                        break;
                    case QUIET: oss << color(GRAY);
                        break;
                    case INFO: oss << color(GREEN);
                        break;
                    case WARNING: oss << color(YELLOW);
                        break;
                    case ERROR: oss << color(RED);
                        break;
                    default: break;
                }

                oss << m_sender << color(WHITE) << "]: ";

                std::string ostr = oss.str();
                std::streamsize ssize = m_pBuf->sputn(ostr.c_str(), ostr.length());
                if (ssize != ostr.length())
                    return traits_type::eof();
            }

            value = m_pBuf->sputc(c);
        }

        if (traits_type::eq_int_type(c, traits_type::to_int_type('\n')))
        {
            m_lineBegin = true;
            m_level = INFO;
        }

        return value;
    }
}
