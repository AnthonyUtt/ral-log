#include "logstreambuf.h"
#include <string>
#include <sstream>
#include <time.h>
#include <chrono>

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

                
                std::chrono::high_resolution_clock::time_point tp = std::chrono::high_resolution_clock::now();
                std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
                std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);
                time_t curTime = s.count();

                struct tm *tmp;
                char timestampFront[32];
                char timestampBack[32];
                time(&curTime);
                tmp = localtime(&curTime);

                parseFormat(m_format);

                strftime(timestampFront, sizeof(timestampFront), m_formatFront, tmp);
                std::size_t fractional_seconds = ms.count() % 1000;

                oss << timestampFront;
                
                if (m_ms)
                {
                    oss << "." << fractional_seconds;

                    if (m_formatBack != "")
                    {
                        strftime(timestampBack, sizeof(timestampBack), m_formatBack, tmp);
                        oss << timestampBack;
                    }
                }
                oss << " [";

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

    void LogStreamBuf::parseFormat(const char* format)
        {
            if (format != "")
            {
                m_ms = false;
                std::string formatStr(format);
                
                std::size_t pos = formatStr.find("%Q");
                if (pos != std::string::npos)
                {
                    m_ms = true;
                    std::string formatFront(formatStr.substr(0, pos));
                    std::string formatBack(formatStr.substr(pos + 2, formatStr.length() - (pos + 2)));
                    m_formatFront = formatFront.c_str();
                    m_formatBack = formatBack.c_str();
                }
                else
                {
                    m_formatFront = format;
                    m_formatBack = "";
                }
            }
            
        }
}
