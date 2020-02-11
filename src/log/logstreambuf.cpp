#include "logstreambuf.h"
#include <sstream>
#include <time.h>
#include <chrono>
#include <iostream>
#include <iomanip>

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

                std::string formatFront, formatBack;
                parseFormat(m_format, formatFront, formatBack);

                strftime(timestampFront, sizeof(timestampFront), formatFront.c_str(), tmp);
                std::size_t fractional_seconds = ms.count() % 1000;

                oss << timestampFront;
                
                if (m_ms)
                {
                    oss << "." << std::setfill('0') << std::setw(3) << fractional_seconds;

                    if (formatBack.length() > 0)
                    {
                        strftime(timestampBack, sizeof(timestampBack), formatBack.c_str(), tmp);
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
                    case FILE: oss << color(NOCOLOR);
                    default: break;
                }

                oss << m_sender << ((m_level == FILE)?color(NOCOLOR):color(WHITE)) << "]: ";

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

    void LogStreamBuf::parseFormat(const char* format, std::string& formatFront, std::string& formatBack)
        {
            if (strcmp(format, ""))
            {
                m_ms = false;
                std::string formatStr(format);
                
                std::size_t pos = formatStr.find(".%Q");
                if (pos != std::string::npos)
                {
                    m_ms = true;
                    formatFront = formatStr.substr(0, pos);

                    if (pos < (formatStr.length() - 3))
                    {
                        formatBack = formatStr.substr(pos + 3, formatStr.length() - (pos + 3));
                    }
                    else
                    {
                        formatBack = "";
                    }
                }
                else
                {
                    formatFront = "";
                    formatBack = "";
                }
            }
        }
}
