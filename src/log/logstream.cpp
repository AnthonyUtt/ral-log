#include "logstream.h"

namespace log
{
    LogStream::LogStream(std::streambuf *pBuf)
    {
        m_pBuf = new LogStreamBuf(pBuf);
        rdbuf(m_pBuf);
    }
}
