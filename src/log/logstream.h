#pragma once

#include "../init/macros.h"
#include "../init/pch.h"
#include "logstreambuf.h"

namespace log
{
    /// \cond DOXYGEN_OMIT
    struct NOT_EXPORTED Sender
    {
      public:
        Sender(const char *sender) { m_sender = sender; }
        inline const char *get() { return m_sender; }

      private:
        const char *m_sender;
    };

    struct NOT_EXPORTED Format
    {
      public:
        Format(const char *format) { m_format = format; }
        inline const char *get() { return m_format; }

      private:
        const char *m_format;
    };
    /// \endcond

    /// \class LogStream logstream.h ral-log.h
    class API LogStream : public std::ostream {
      public:
        /// `pBuf` is a pointer to a `std::streambuf` object,
        /// usually found by calling `obj.rdbuf()`; commonly 
        /// used with `std::cout`, but can be used with any 
        /// type that implements `std::basic_streambuf`
        LogStream(std::streambuf *pBuf);

        /// Determines color of prefix output.
        /// Must be passed to the LogStream object with the `<<` operator.\n
        /// `[INFO:green|DEBUG:white|ERROR:red|WARNING:yellow|QUIET:gray]`
        inline void setLogLevel(LogLevel level) { m_pBuf->setLevel(level); }

        /// Sets the sender of the message, which shows in the prefix.
        /// Must be passed to the LogStream object with the `<<` operator.
        inline void setSender(const char *sender) { m_pBuf->setSender(sender); }

        /// Sets the format of the timestamp, which shows in the prefix.
        /// Format rules follow that of `strftime()`, with the addition 
        /// of `%Q` to show milliseconds.
        inline void setFormat(const char *format) { m_pBuf->setTimestampFormat(format); }

      private:
        LogStreamBuf *m_pBuf;
    };

    /// \cond DOXYGEN_OMIT
    inline std::ostream &operator<<(std::ostream &os, const LogLevel level)
    {
        dynamic_cast<LogStream *>(&os)->setLogLevel(level);
        return os;
    }

    inline std::ostream &operator<<(std::ostream &os, Sender sender)
    {
        dynamic_cast<LogStream *>(&os)->setSender(sender.get());
        return os;
    }

    inline std::ostream &operator<<(std::ostream &os, Format format)
    {
        dynamic_cast<LogStream *>(&os)->setFormat(format.get());
        return os;
    }
    /// \endcond
}  // namespace log