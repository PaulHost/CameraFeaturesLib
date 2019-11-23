include(ExternalProject)

cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(LibCam LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THIRDPARTY_DIR ${CMAKE_CURRENT_LIST_DIR}/lib)

set(OPENCV_INSTALL_DIR ${CMAKE_BINARY_DIR}/opencv)
set(OPENCV_DIR ${THIRDPARTY_DIR}/opencv)

set(FFMPEG_INSTALL_DIR ${CMAKE_BINARY_DIR}/ffmpeg)
set(FFMPEG_DIR ${THIRDPARTY_DIR}/ffmpeg)

set(OH264_INSTALL_DIR ${CMAKE_BINARY_DIR}/openh264)
set(OH264_DIR ${THIRDPARTY_DIR}/openh264)

ExternalProject_Add(
        opencv
        SOURCE_DIR ${OPENCV_DIR}
        CMAKE_ARGS
        -DCMAKE_CXX_FLAGS=${CXX_OPT_FLAGS}
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
        #-DCPU_BASELINE:String=${OPENCV_CPU_BASELINE}
        -DENABLE_CXX11=ON
        -DBUILD_opencv_world=ON
        -DCMAKE_CXX_STANDARD=14
        ### Enabled modules
				-DBUILD_LIST=imgproc,video,highgui,imgcodecs,videoio,photo
				###
        -DBUILD_JPEG=ON
        -DBUILD_JASPER=ON
        -DBUILD_PNG=ON
        -DBUILD_TIFF=ON
        -DBUILD_ZLIB=ON
				-DWITH_FFMPEG=ON
        ###
        -DBUILD_DOCS=OFF
        -DBUILD_EXAMPLES=OFF
        -DBUILD_JAVA=OFF
        -DBUILD_NEW_PYTHON_SUPPORT=OFF
        -DBUILD_PACKAGE=OFF
        -DBUILD_PERF_TESTS=OFF
        -DBUILD_SHARED_LIBS=OFF
        -DBUILD_TESTS=OFF
        -DBUILD_WITH_CAROTENE=OFF
        -DBUILD_WITH_DEBUG_INFO=OFF
				-DWITH_1394=OFF
        -DWITH_CUDA=OFF
				-DWITH_MFX=OFF
        -DWITH_CUFFT=OFF
        -DWITH_GSTREAMER=OFF
        -DWITH_IPP=OFF
        -DWTTH_IPP_IW=OFF
        -DWITH_ITT=OFF
        -DWITH_MATLAB=OFF
        -DWITH_NVCUVID=OFF
        -DWITH_OPENCL=OFF
        -DWITH_OPENEXR=OFF
        -DWITH_TBB=OFF
        -DWITH_WEBP=OFF
        -DWITH_PTHREADS_PF=OFF
        -DWITH_OPENMP=OFF
        -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX:PATH=${OPENCV_INSTALL_DIR}
)

ExternalProject_Add(
  ffmpeg
	SOURCE_DIR ${FFMPEG_DIR}
  CMAKE_ARGS
	BUILD_IN_SOURCE ON
	CONFIGURE_COMMAND git clean -f && PKG_CONFIG_PATH=${OH264_INSTALL_DIR}/lib/pkgconfig ./configure --disable-autodetect --enable-libopenh264 --disable-decoder=opus --disable-encoder=opus --enable-pic --prefix=${FFMPEG_INSTALL_DIR}
	BUILD_COMMAND make -j10 && make install
)

add_dependencies(opencv ffmpeg)

ExternalProject_Add(
	openh264
	SOURCE_DIR ${OH264_DIR}
	BUILD_IN_SOURCE ON
	CONFIGURE_COMMAND git clean -f
	BUILD_COMMAND git clean -f && make -j10
	INSTALL_COMMAND make PREFIX=${OH264_INSTALL_DIR} install 
)

add_dependencies(ffmpeg openh264)

set_target_properties(opencv 
	PROPERTIES 
	pkgcfg_lib_FFMPEG_avcodec ${FFMPEG_INSTALL_DIR}/lib/libavcodec.a 
	pkgcfg_lib_FFMPEG_avformat ${FFMPEG_INSTALL_DIR}/lib/libavformat.a
	pkgcfg_lib_FFMPEG_avutil ${FFMPEG_INSTALL_DIR}/lib/libavutil.a
	pkgcfg_lib_FFMPEG_swscale ${FFMPEG_INSTALL_DIR}/lib/libswscale.a
)

add_library(
	LibCam
	${CMAKE_CURRENT_LIST_DIR}/src/MotionInterpolator.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/LongExposure.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/VideoInput.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/VideoOutput.cpp
)

# Targets for library
target_include_directories(LibCam PUBLIC 
	${OPENCV_DIR}/include 
	${OPENCV_INSTALL_DIR}/include/opencv4
)
target_link_libraries(LibCam 
	opencv_world
	pthread 
	libpng 
	libtiff 
	libjpeg-turbo 
	zlib 
	libjasper 
	libprotobuf 
	dl 
	${FFMPEG_INSTALL_DIR}/lib/libavformat.a
	${FFMPEG_INSTALL_DIR}/lib/libavcodec.a 
	${FFMPEG_INSTALL_DIR}/lib/libavutil.a
	${FFMPEG_INSTALL_DIR}/lib/libavfilter.a
	${FFMPEG_INSTALL_DIR}/lib/libswscale.a
	${FFMPEG_INSTALL_DIR}/lib/libavdevice.a
	${OH264_INSTALL_DIR}/lib/libopenh264.a
	) 
target_link_directories(LibCam PUBLIC 
	${OPENCV_INSTALL_DIR}/lib 
	${OPENCV_INSTALL_DIR}/lib/opencv4/3rdparty
)
add_dependencies(LibCam opencv)

add_executable(
	LibCamUsage
  ${CMAKE_CURRENT_LIST_DIR}/sample/Main.cpp
)

# Targets for sample
target_include_directories(LibCamUsage PUBLIC ${CMAKE_CURRENT_LIST_DIR}/sample)
target_link_libraries(LibCamUsage LibCam)
