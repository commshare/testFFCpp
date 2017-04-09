#https://github.com/biezhihua/FFMPEG/blob/master/FFmpegTranscoder/CMakeLists.txt
#http://stackoverflow.com/questions/25909943/getting-a-cmake-error-cannot-specify-link-libraries-for-target-which-is-not-bui
#Specify the version being used aswell as the language
cmake_minimum_required(VERSION 2.8)
#Name your project here
project(FFmpegCpp)

#set(CMAKE_C_STANDARD 99)

#Sends the -std=c++11 flag to the gcc compiler
ADD_DEFINITIONS(-std=c++11)





##

if(LINUX OR APPLE)
	message("ConfigurationName" ${ConfigurationName})
	set(PREPROCESSOR_DEFINITIONS ${PREPROCESSOR_DEFINITIONS};/DIFLOOR_EXPORTS;/DIFLOOR_EFFECT_PLUGIN_BASE_EXPORTS;/D__STDC_CONSTANT_MACROS)

	SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
	SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
	if(LINUX) 
		SET(CMAKE_INSTALL_RPATH ".:./../../")
	else()
		SET(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")
	endif(LINUX)
endif(LINUX OR APPLE)




#include the subdirectory containing our libs
#add_subdirectory (gui)
#include_directories(gui)

include_directories(/root/ffmpeg_build/include)
link_directories(/root/ffmpeg_build/lib/)


set(SOURCE_FILES main.cpp AV.cpp log.cpp)
add_executable(testffcpp.out ${SOURCE_FILES})

#The first argument of target_link_libraries is the target name
target_link_libraries(
        testffcpp.out 
	avformat        
        avdevice
	avfilter 
	postproc        
	swresample  
	swscale   
	avcodec	
	avutil
	m
	dl
	pthread	
	mp3lame
	opus
	vorbis
	ogg
	vpx
	x264
	vorbisenc
	z
	fdk-aac
	vorbisfile
)