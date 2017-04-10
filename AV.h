#ifndef AV_H
#define AV_H

#include "av_common.h"
#include <fstream>
#include <string>


namespace cppav {


class AV {
public:
	/*https://github.com/plsang/visualrhythm/blob/1a2e2e6969f6a8a47a9334a7dbb774dc1130b1c7/ffpp/FormatContext.h*/
    typedef void (*HandleFrame)(AVFrame*, enum AVMediaType type);  /*定义了一个public的函数指针*/

private:
    void _Init();
    int _FrameProcess(AVPacket* packet, AVFrame* frame);

public:
    AV();
    ~AV();

    int Open(const std::string& filename);
    int Play();
    inline std::string GetLastErrStr() {
        return _lastErrStr;
    }
	/*为什么要搞成内联的*/
    inline void SetFrameHandler(HandleFrame handleFrame) {
        _handleFrame = handleFrame;
    }

private:
    AVFormatContext*	_formatCtx;
    AVCodecContext*		_videoCodecCtx;
    AVCodecContext*		_audioCodecCtx;

    std::ifstream		_inFileStream;  /*输入文件流*/
    std::ofstream		_outFileStream; /*输出文件流*/

    int 				_videoStreamIndex;
    int 				_audioStreamIndex;
    bool 				_isOpen;

    std::string			_lastErrStr;

    HandleFrame			_handleFrame;
};

}

#if 0

class AVMediaType
{
	public:

	int AVMEDIA_TYPE_UNKNOWN = -1;	///< Usually treated as AVMEDIA_TYPE_DATA
	int AVMEDIA_TYPE_VIDEO=0;
	int AVMEDIA_TYPE_AUDIO=1;
	int AVMEDIA_TYPE_DATA=2;			///< Opaque data information usually continuous
	int AVMEDIA_TYPE_SUBTITLE=3;
	int AVMEDIA_TYPE_ATTACHMENT=4;	///< Opaque data information usually sparse
	int AVMEDIA_TYPE_NB=5;
};
#endif

#endif // AV_H

