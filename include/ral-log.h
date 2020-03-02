#pragma once

#include "../src/init/macros.h"
#include "../src/init/pch.h"
#include "../src/log/logstream.h"

namespace RALlogger
{
    inline static void logDebug(const char *message, const char *sender = "", const char *format = "")
    {
        log::LogStream(std::cout.rdbuf()) << log::DEBUG << log::Sender(sender) << log::Format(format) << message << std::endl;
    }

    inline static void logQuiet(const char *message, const char *sender = "", const char *format = "")
    {
        log::LogStream(std::cout.rdbuf()) << log::QUIET << log::Sender(sender) << log::Format(format) << message << std::endl;
    }

    inline static void logInfo(const char *message, const char *sender = "", const char *format = "")
    {
        log::LogStream(std::cout.rdbuf()) << log::INFO << log::Sender(sender) << log::Format(format) << message << std::endl;
    }

    inline static void logWarning(const char *message, const char *sender = "", const char *format = "")
    {
        log::LogStream(std::cout.rdbuf()) << log::WARNING << log::Sender(sender) << log::Format(format) << message << std::endl;
    }

    inline static void logError(const char *message, const char *sender = "", const char *format = "")
    {
        log::LogStream(std::cout.rdbuf()) << log::ERROR << log::Sender(sender) << log::Format(format) << message << std::endl;
    }

    inline static void writeToLog(const char *message, const char *pathToFile, const char *sender = "", const char *format = "")
    {
        log::LogStream(std::ofstream(pathToFile, std::ios_base::out | std::ios_base::app).rdbuf()) << log::FILE << log::Sender(sender) << log::Format(format) << message << std::endl;
    }
}  // namespace RALlogger