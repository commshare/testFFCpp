#ifndef DEMUX_H_
#define DEMUX_H_

#include "av_common.h"

/*https://github.com/wangxiaoxiwudi/testffmpeg/blob/master/testffmpeg/testffmpeg/demux.h
https://github.com/e-soroush/Project_FFMpegMediaIO/blob/master/libsrc/demuxer.h
*/
namespace cppav {

class Demuxer
{
public:
 	 Demuxer(std::string file_name);
 	 ~Demuxer();
 	 bool init();
     bool init(const char* _fileName);
	  bool reinit();
  	  void process();
  	  void finish();

      bool getNextAvPacketFrame(AVPacket &_avPacket);
	  std::string getFileName() const {return this->m_filename;}
	  AVFormatContext *getAvFormatContext() const {return this->m_avfcx;}
	  
	  void dumpFormatContext() {av_dump_format(this->m_avfcx, 0, this->m_filename.c_str(), 0);}
	  int getVideoStreamNumber();
    	uint getWidth();
	    uint getHeight();
private:
 	 AVFormatContext * m_avfcx;
 	 std::string m_filename;
 	 AVPacket m_avPacket;	 
	 bool initialized = false;
};

}

#endif

