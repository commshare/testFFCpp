#https://github.com/biezhihua/FFMPEG/blob/master/FFmpegTranscoder/CMakeLists.txt
#http://stackoverflow.com/questions/25909943/getting-a-cmake-error-cannot-specify-link-libraries-for-target-which-is-not-bui
#Specify the version being used aswell as the language
cmake_minimum_required(VERSION 2.8)
#Name your project here
project(FFmpegCpp)

#set(CMAKE_C_STANDARD 99)

#Sends the -std=c++11 flag to the gcc compiler
ADD_DEFINITIONS(-std=c++11)


SET(CMAKE_CXX_FLAGS "-O2 -std=c++11")

##可以打印出详细的链接信息
SET(CMAKE_EXE_LINKER_FLAGS "-v")


##

if(LINUX OR APPLE)
	message("ConfigurationName" ${ConfigurationName})
	set(PREPROCESSOR_DEFINITIONS ${PREPROCESSOR_DEFINITIONS};/DIFLOOR_EXPORTS;/DIFLOOR_EFFECT_PLUGIN_BASE_EXPORTS;/D__STDC_CONSTANT_MACROS)

	#SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
	#SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
	#if(LINUX) 
	#	SET(CMAKE_INSTALL_RPATH ".:./../../")
	#else()
	#	SET(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")
	#endif(LINUX)
endif(LINUX OR APPLE)

####freetype2 load a module like FindFreetype.cmake
#http://stackoverflow.com/questions/14110769/undefined-reference-with-freetype-2
#http://stackoverflow.com/questions/23888274/linking-freetype-with-cmake
find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

# Import required CMake files
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")
##
 find_package (ASS REQUIRED)




##兼容我的ubuntu16
set(FFMPEG_INC_DIRS /root/.ffmpeg_build/include /root/ffmpeg_build/include)
set(FFMPEG_LIB_DIRS /root/.ffmpeg_build/lib /root/ffmpeg_build/lib)

include_directories(${FFMPEG_INC_DIRS})
link_directories(${FFMPEG_LIB_DIRS})


set(SOURCE_FILES main.cpp AV.cpp log.cpp)
add_executable(testffcpp.out ${SOURCE_FILES})


#不需要-lfreetype，直接用  ${FREETYPE_LIBRARIES} ，因为target_link_libraries是与平台无关的
###target_link_libraries(demo ${FREETYPE_LIBRARIES})
#target_link_libraries is platform independent whereas '-lfreetype in CMAKE_EXE_LINKER_FLAGS is not.

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
        x265
  ${FREETYPE_LIBRARIES}
  ${LIBASS_LIBRARIES}
)
