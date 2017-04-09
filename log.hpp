#ifndef _AV_TRANSCODER_LOG_HPP
#define _AV_TRANSCODER_LOG_HPP
/*
https://github.com/avTranscoder/avTranscoder/blob/develop/src/AvTranscoder/log.cpp
*/
//#include <AvTranscoder/common.hpp>

/*
http://www.cnblogs.com/verstin/p/5011274.html

*/

extern "C" {
#ifdef __cplusplus
#define __STDC_CONSTANT_MACROS
#ifdef _STDINT_H
#undef _STDINT_H
#endif
# include "stdint.h"
#endif
	
	
#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif

#include <libavutil/log.h>
}

#include <sstream>
#include <fstream>

namespace cppav
{
/*用下面的这些宏更方便*/
#define LOG_FILE "cppav.log"
#define LOG_DEBUG(...)                                                                                                      \
    {                                                                                                                       \
        std::stringstream os;                                                                                               \
        os << __VA_ARGS__;                                                                                                  \
        Logger::log(AV_LOG_DEBUG, os.str());                                                                                \
    }
#define LOG_INFO(...)                                                                                                       \
    {                                                                                                                       \
        std::stringstream os;                                                                                               \
        os << __VA_ARGS__;                                                                                                  \
        Logger::log(AV_LOG_INFO, os.str());                                                                                 \
    }
#define LOG_WARN(...)                                                                                                       \
    {                                                                                                                       \
        std::stringstream os;                                                                                               \
        os << __VA_ARGS__;                                                                                                  \
        Logger::log(AV_LOG_WARNING, os.str());                                                                              \
    }
#define LOG_ERROR(...)                                                                                                      \
    {                                                                                                                       \
        std::stringstream os;                                                                                               \
        os << __VA_ARGS__;                                                                                                  \
        Logger::log(AV_LOG_ERROR, os.str());                                                                                \
    }

/// Logger class which contains static functions to use ffmpeg/libav log system 这个类里用静态方法
class /*AvExport*/ Logger
{
public:
    /**
     * @brief Set the log level of ffmpeg/libav.
     * @param level: refer to define AV_LOG_xxx (from AV_LOG_QUIET to AV_LOG_DEBUG)
     * @note By default AV_LOG_INFO
     * @see SWIG interface avLogLevel.i
     */
    static void setLogLevel(const int level);

    /**
     * @brief Log with the ffmpeg/libav log system
     * @note you can use macro LOG_* to log at DEBUG/INFO/WARN/ERROR level
     * @param msg: the message will be prefixed by '[avTranscoder - <level>]'
     * @param msg: the message will be suffixed by '\n'
     */
    static void log(const int level, const std::string& msg);

    /**
     * @brief Log ffmpeg/libav and avtranscoder informations in a text file.
     * @note log filename is avtranscoder.log
     */
    static void logInFile();

private:
    static std::string logHeaderMessage; ///< First caracters present for each logging message
};
}

#endif

