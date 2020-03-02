/// \mainpage RAL-log
///
/// \section intro Introduction
/// RAL-log is a cross-platform, open-source logging library.
/// It features thread-safe logging functions that output
/// directly to the std::cout buffer with custom headers
/// prepended to the output statements. Options for the
/// headers include custom-formatted timestamps,
/// color-coding, and displaying the message sender
/// (in the case of multiple subsystems using the library
/// to report on various processes.)
///
/// \section install Installation
/// There are a few different ways to install RAL-log to use
/// with your projects:
///
/// \subsection submodule Option 1: Using git submodule (Recommended)
/// Add the git repository for RAL-log as a submodule of your project.
/// \code{.unparsed}
/// cd <path_to_containing_folder>
/// git submodule add https://github.com/AnthonyUtt/ral-log
/// \endcode
/// When using this option, make sure you call
/// `add_subdirectory(<ral-log_path>)` in your CMakeLists.txt file
/// and call `target_include_directories(${PROJECT_NAME} PRIVATE <ral-log_path>/include)`
/// so that your build will be successful.
///
/// \subsection sourceBuild Option 2: Build library from source
/// Clone the git repo into a new directory and build the target
/// from the source code:
/// \code{.unparsed}
/// git clone https://github.com/AnthonyUtt/ral-log.git
/// cd ral-log/bin
/// cmake ..
/// cmake --build .
/// \endcode
/// From there, you can copy the build into the `/usr/lib/` directory
/// and include it in your project from anywhere.
///
/// \subsection sourceInclude Option 3: Build source directly into your project (Not Recommended)
/// This option is similar to Option 1, except, instead of adding
/// RAL-log as a git submodule, you copy the source code directly into
/// your project manually.
///
/// \section usage Usage
/// In order to use RAL-log, add `#include <ral-log.h>` to any file
/// in your project.
///
/// \section license License
/// RAL-log is licensed under the [MIT License](https://opensource.org/licenses/MIT).

#include "logstream.h"

namespace log
{
    LogStream::LogStream(std::streambuf *pBuf)
    {
        m_pBuf = new LogStreamBuf(pBuf);
        rdbuf(m_pBuf);
    }
}  // namespace log
