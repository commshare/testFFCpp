#ifndef _AV_COMMON_H_
#define _AV_COMMON_H_

#if __cplusplus
extern "C" {
#endif

#define __STDC_CONSTANT_MACROS

#include <libavdevice/avdevice.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
#include <libavfilter/avfiltergraph.h>
#include <libavfilter/buffersink.h>
#include <libavfilter/buffersrc.h>
#include <libavutil/frame.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
/* https://ffmpeg.org/doxygen/2.0/group__lavu__misc.html#ga9a84bba4713dfced21a1a56163be1f48 for AVMediaType*/
#include <libavutil/avutil.h>

#if __cplusplus
};
#endif
#include "log.hpp"



#endif
