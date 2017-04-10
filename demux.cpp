#include <stdafx.h>
#include "demux.h"
using namespace cppav;
/*
https://github.com/e-soroush/Project_FFMpegMediaIO/blob/master/libsrc/demuxer.cpp
*/
Demuxer::Demuxer(std::string file_name):m_filename(file_name),m_avfcx(NULL)
{
	    avcodec_register_all();
		av_register_all();

}

Demuxer::~Demuxer()
{
    avformat_close_input(&this->m_avfcx);
}

bool Demuxer::init()
{
  av_register_all();

  if (avformat_open_input(&m_avfcx, m_filename.c_str(), 0, 0) < 0) 
  {
    assert(false&&"Could not open input file");
	return false;
  }

  if (avformat_find_stream_info(m_avfcx, 0) < 0) 
  {
    assert(false&&"Failed to retrieve input stream information");
	return false;
  }

  av_dump_format(m_avfcx, 0, m_filename.c_str(), 0);
  av_init_packet(&m_avPacket);
}

void Demuxer::process()
{
  av_read_frame(m_avfcx,&m_avPacket);
}

void Demuxer::finish()
{
  avformat_close_input(&m_avfcx);
  av_free_packet(&m_avPacket);
}

bool Demuxer::init(const char* _fileName){
	/* initialize packet, set data to NULL, let the demuxer fill it */
	   av_init_packet(&this->m_avPacket);
	   this->avPacket.data = NULL;
	   this->avPacket.size = 0;
	   this->m_filename.assign(_fileName);
	   int number = -1;
	   AVInputFormat *inputFormat = NULL;
	   AVDictionary *dict = NULL;
	   if (avformat_open_input(&m_avfcx, m_filename.c_str(), 0, 0) < 0) 
	   {
	   	  std::cerr << "Could not open source file " << this->m_filename.c_str() << std::endl;
		  assert(false&&"Could not open input file");
		  return false;
	   }
	   
	   if (avformat_find_stream_info(m_avfcx, 0) < 0) 
	   {
		 assert(false&&"Failed to retrieve input stream information");
		 return false;
	   }
	    /* dump input information to stderr */
	    av_dump_format(this->m_avfcx, 0, m_filename, 0);
	   initialized = true;
	    return true;

}

bool Demuxer::reinit()
{
    avformat_close_input(&this->m_avfcx);
    this->m_avfcx = NULL;
    return init(this->m_filename.c_str());
}
bool Demuxer::getNextAvPacketFrame(AVPacket &_avPacket)
{
    if(this->initialized == false)
        return false;
    int ret = av_read_frame(this->m_avfcx, &this->m_avPacket);
    m_avPacket = this->avPacket;
    if(ret == 0)
        return true;
    else
        return false;
}

int Demuxer::getVideoStreamNumber()
{
    for (uint cnt = 0; cnt < this->m_avfcx->nb_streams; ++cnt) {
        if(this->m_avfcx->streams[cnt]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
            return int(cnt);
    }
    return -1;
}

uint Demuxer::getWidth()
{
    int ret = this->getVideoStreamNumber();
    if(ret < 0)
        return 0;
    else
        return this->m_avfcx->streams[ret]->codec->width;
}

uint Demuxer::getHeight()
{
    int ret = this->getVideoStreamNumber();
    if(ret < 0)
        return 0;
    else
        return this->m_avfcx->streams[ret]->codec->height;
}

