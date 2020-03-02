#pragma once

#include "../init/macros.h"
#include "../init/pch.h"
#include "logutil.h"

#define DEFAULT_SENDER "RAL-LOG"
#define DEFAULT_FORMAT "%x %H:%M:%S.%Q"

namespace log
{
    /// \class LogStreamBuf logstreambuf.h ral-log.h
    /// This class should not be used directly; use 
    /// LogStream instead.
    class NOT_EXPORTED LogStreamBuf : public std::streambuf {
      private:
        bool m_lineBegin;
        LogLevel m_level;
        const char *m_sender;
        const char *m_format;
        bool m_ms;
        std::streambuf *m_pBuf;

      public:
        /// __[DO NOT USE]__ LogStreamBuf consructor
        explicit LogStreamBuf(std::streambuf *pBuf);

        /// __[DO NOT USE]__ Resets prefix to default values.
        void resetPrefix();

        /// __[DO NOT USE]__ Determines color of prefix output.
        inline void setLevel(LogLevel level) { m_level = level; }

        /// __[DO NOT USE]__ Sets the sender of the message, 
        /// which shows in the prefix.
        inline void setSender(const char *sender) { m_sender = strcmp(sender, "") ? sender : DEFAULT_SENDER; }

        /// __[DO NOT USE]__ Sets the format of the timestamp, 
        /// which shows in the prefix.
        inline void setTimestampFormat(const char *format) { m_format = strcmp(format, "") ? format : DEFAULT_FORMAT; };

      protected:
        /// __[DO NOT USE]__ Override of `std::streambuf::overflow()`.
        /// Adds custom prefix to log content before 
        /// writing data to buffer. __This function 
        /// should not be used directly.__
        int_type overflow(int_type c = traits_type::eof());

      private:
        void parseFormat(const char *format, std::string &formatFront, std::string &formatBack);
    };
}  // namespace log