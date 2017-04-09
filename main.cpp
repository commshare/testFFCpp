#include "AV.h"

#include <iostream>


AVFilterContext* gBuffersinkCtx = NULL;
AVFilterContext* gBuffersrcCtx = NULL;
AVFilterGraph* gFilterGraph = NULL;

AVFilter* gBuffersink = NULL;
AVFilter* gBuffersrc = NULL;

AVFilterInOut *gOutputs = NULL;
AVFilterInOut *gInputs  = NULL;
enum AVPixelFormat gPixFmts[] = { AV_PIX_FMT_YUV420P, AV_PIX_FMT_NONE };

const char* gFilterDesc = "boxblur";
const char * filepath = "green_line.mp4";//"D:\\test_videos\\green2.mp4"
int in_width = 268;
int in_height = 480;


int InitFilter() {
    avfilter_register_all();

    gBuffersrc = avfilter_get_by_name("buffer");
    gBuffersink = avfilter_get_by_name("ffbuffersink");
    gOutputs = avfilter_inout_alloc();
    gInputs = avfilter_inout_alloc();

    gFilterGraph = avfilter_graph_alloc();

    char args[512] = { 0 };
    snprintf(args, sizeof(args),
             "video_size=%dx%d:pix_fmt=%d:time_base=%d/%d:pixel_aspect=%d/%d",
             in_width,in_height,AV_PIX_FMT_YUV420P,
             1, 25,1,1);
    int ret = avfilter_graph_create_filter(&gBuffersrcCtx, gBuffersrc, "in", args, NULL, gFilterGraph);
    if(ret < 0 ) {
        return ret;
    }

    AVBufferSinkParams *buffersink_params = NULL;
    buffersink_params = av_buffersink_params_alloc();
    buffersink_params->pixel_fmts = gPixFmts;
    ret = avfilter_graph_create_filter(&gBuffersinkCtx, gBuffersink, "out", NULL, buffersink_params, gFilterGraph);
    av_free(buffersink_params);
    if(ret < 0) {
        char buf[1024] = { 0 };
        printf("%s\n", av_make_error_string(buf, sizeof(buf), ret));
        return ret;
    }

    gOutputs->name = av_strdup("in");
    gOutputs->filter_ctx = gBuffersrcCtx;
    gOutputs->pad_idx = 0;
    gOutputs->next = NULL;

    gInputs->name = av_strdup("out");
    gInputs->filter_ctx = gBuffersinkCtx;
    gInputs->pad_idx = 0;
    gInputs->next = NULL;

    ret = avfilter_graph_parse_ptr(gFilterGraph, gFilterDesc, &gInputs, &gOutputs, NULL);
    if(ret < 0) {
        return ret;
    }
    ret = avfilter_graph_config(gFilterGraph, NULL);
    if(ret < 0) {
        return ret;
    }
    return 0;
}

void DestroyFilter() {

}

void HandleFrame(AVFrame* frame, AVMediaType mediaType) {
    if(mediaType == AVMEDIA_TYPE_VIDEO) {
    }
}

int main(int argc, char *argv[]) {
    using namespace cppav;

    int ret = 0;
	#if 0
    if((ret = InitFilter()) != 0) {
        return ret;
    }
	#endif

    AV av;
	Logger::setLogLevel(AV_LOG_DEBUG);
	LOG_DEBUG("BEGIN BEGIN");
    av.Open(filepath);
    av.SetFrameHandler(HandleFrame);
    av.Play();

    return 0;
}

