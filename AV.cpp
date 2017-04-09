
#include "AV.h"

#include <cassert>

using namespace cppav;


void AV::_Init() {
    av_register_all();
    _formatCtx = avformat_alloc_context();
}

int AV::_FrameProcess(AVPacket* packet, AVFrame* frame) {
    if(packet == NULL || frame == NULL) {
        return -1;
    }

    int ret = 0;
    int gotFrame = 0;
    AVMediaType frameType = AVMEDIA_TYPE_UNKNOWN;

    if(packet->stream_index == _videoStreamIndex) {
        // Got video frame.
        if(avcodec_decode_video2(_videoCodecCtx, frame, &gotFrame, packet) < 0) {
            return -5;
        }
        if(gotFrame != 0) {
            frameType = AVMEDIA_TYPE_VIDEO;
        }
    } else if(packet->stream_index == _audioStreamIndex) {
        // Got audio frame.
        if(avcodec_decode_audio4(_audioCodecCtx, frame, &gotFrame, packet) < 0) {
            return -6;
        }
        if(gotFrame != 0) {
            frameType = AVMEDIA_TYPE_AUDIO;
        }
    }

    if(gotFrame != 0) {
        if(_handleFrame) {
            _handleFrame(frame, frameType);
        }
    }
    return 0;
}

AV::AV() : _formatCtx(NULL), _videoCodecCtx(NULL), _audioCodecCtx(NULL),
           _inFileStream(), _outFileStream(),
           _videoStreamIndex(-1), _audioStreamIndex(-1),
           _isOpen(false), _lastErrStr("Is not open!\n"),
           _handleFrame(NULL)
{
    _Init();
}

AV::~AV() {
    if(_videoCodecCtx) {
        avcodec_close(_videoCodecCtx);
    }
    if(_audioCodecCtx) {
        avcodec_close(_audioCodecCtx);
    }
    if(_formatCtx) {
        avformat_close_input(&_formatCtx);
    }
}

int AV::Open(const std::string& filename) {
    int ret = 0;

    do {
        if((ret = avformat_open_input(&_formatCtx, filename.c_str(), NULL, NULL)) != 0) {
            _lastErrStr = "Couldn't open input stream!\n";
            break;
        }
        if(avformat_find_stream_info(_formatCtx, NULL) < 0) {
            _lastErrStr = "Couldn't find stream info!\n";
            ret = -2;
            break;
        }

        for(unsigned int i = 0; i < _formatCtx->nb_streams; ++i) {
            switch(_formatCtx->streams[i]->codec->codec_type) {
            case AVMEDIA_TYPE_UNKNOWN:			///< Usually treated as AVMEDIA_TYPE_DATA
                break;
            case AVMEDIA_TYPE_VIDEO:
                _videoStreamIndex = i;
                break;
            case AVMEDIA_TYPE_AUDIO:
                _audioStreamIndex = i;
                break;
            case AVMEDIA_TYPE_DATA:          ///< Opaque data information usually continuous
                break;
            case AVMEDIA_TYPE_SUBTITLE:
                break;
            case AVMEDIA_TYPE_ATTACHMENT:    ///< Opaque data information usually sparse
                break;
            case AVMEDIA_TYPE_NB:
                break;
            }
        }
        if(_videoStreamIndex == -1 || _audioStreamIndex == -1) {
            _lastErrStr = "Didn't find a video/audio stream!\n";
            ret = -3;
            break;
        }

        _videoCodecCtx = _formatCtx->streams[_videoStreamIndex]->codec;
        AVCodec* tmpVidecCodec = avcodec_find_decoder(_videoCodecCtx->codec_id);
        if(tmpVidecCodec == NULL) {
            _lastErrStr = "Codec not found!\n";
            ret = -4;
            break;
        }
        if(avcodec_open2(_videoCodecCtx, tmpVidecCodec, NULL) < 0) {
            _lastErrStr = "Could not open codec!\n";
            ret = -5;
            break;
        }

        _audioCodecCtx = _formatCtx->streams[_audioStreamIndex]->codec;
        AVCodec* tmpAudioCodec = avcodec_find_decoder(_audioCodecCtx->codec_id);
        if(tmpAudioCodec == NULL) {
            _lastErrStr = "Codec not found!\n";
            ret = -4;
            break;
        }
        if(avcodec_open2(_audioCodecCtx, tmpAudioCodec, NULL) < 0) {
            _lastErrStr = "Could not open codec!\n";
            ret = -5;
            break;
        }
    } while(0);

    if(ret == 0) {
        _lastErrStr = "Is open!\n";
        _isOpen = true;
    }

    return ret;
}

int AV::Play() {
    int ret = 0;
    if(!_isOpen) {
        return -1;
    }

    AVFrame* frame = NULL;
    AVPacket* packet = NULL;
    do {
        frame = av_frame_alloc();
        if(frame == NULL) {
            ret = -2;
            break;
        }
        packet = (AVPacket *)av_malloc(sizeof(AVPacket));
        if(packet == NULL) {
            ret = -3;
            break;
        }

        while(1) {
            if(av_read_frame(_formatCtx, packet) < 0) {
                ret = 0;			///< error or end ?
                break;
            }
            ret = _FrameProcess(packet, frame);
            if(ret != 0) {
                break;
            }
            av_packet_unref(packet);
        }
    } while(0);

    av_free(packet);
    av_frame_free(&frame);

    return ret;
}

