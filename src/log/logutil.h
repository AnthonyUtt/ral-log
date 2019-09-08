#pragma once

#include "../init/macros.h"

namespace log
{
    enum NOT_EXPORTED LogLevel
    {
        DEBUG,
        QUIET,
        INFO,
        WARNING,
        ERROR,
        FILE
    };

    enum NOT_EXPORTED TextColor
    {
        WHITE,
        GRAY,
        GREEN,
        YELLOW,
        RED,
        NOCOLOR
    };

    inline static const char* color(TextColor col)
    {
        const char* retVal;

        switch (col)
        {
            case WHITE: retVal = "\033[0m";
                break;
            case GRAY: retVal = "\033[37m";
                break;
            case GREEN: retVal = "\033[92m";
                break;
            case YELLOW: retVal = "\033[93m";
                break;
            case RED: retVal = "\033[91m";
                break;
            default: retVal = "";
                break;
        }

        return retVal;
    }
}