include(ExternalProject)

cmake_minimum_required(VERSION 3.5)

project(LibCam LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THIRDPARTY_DIR ${CMAKE_CURRENT_LIST_DIR}/lib)
set(OPENCV_INSTALL_DIR ${CMAKE_BINARY_DIR}/opencv)
set(OPENCV_DIR ${THIRDPARTY_DIR}/opencv)

ExternalProject_Add(
        opencv
        SOURCE_DIR ${OPENCV_DIR}
        CMAKE_ARGS
        -DCMAKE_CXX_FLAGS=${CXX_OPT_FLAGS}
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
        #-DCPU_BASELINE:String=${OPENCV_CPU_BASELINE}
        -DENABLE_CXX11=ON
        -DWITH_FFMPEG=OFF
        -DBUILD_opencv_world=ON
        -DCMAKE_CXX_STANDARD=14
        ### Enabled modules
        -DBUILD_opencv_imgproc=ON
        -DBUILD_opencv_video=ON
        -DBUILD_opencv_highgui=ON
        -DBUILD_opencv_imgcodecs=ON
        -DBUILD_opencv_videoio=ON
        ### Disabled modules
        -DBUILD_opencv_dnn=OFF
        -DBUILD_opencv_apps=OFF
        -DBUILD_opencv_contrib=OFF
        -DBUILD_opencv_flann=OFF
        -DBUILD_opencv_features2d=OFF
        -DBUILD_opencv_calib3d=OFF
        -DBUILD_opencv_java=OFF
        -DBUILD_opencv_java_bindings_generator=OFF
        -DBUILD_opencv_ml=OFF
        -DBUILD_opencv_objdetect=OFF
        -DBUILD_opencv_photo=OFF
        -DBUILD_opencv_python2=OFF
        -DBUILD_opencv_shape=OFF
        -DBUILD_opencv_stitching=OFF
        -DBUILD_opencv_superres=OFF
        -DBUILD_opencv_ts=OFF
        -DBUILD_opencv_videostab=OFF
        -DBUILD_opencv_python2=OFF
        -DBUILD_opencv_viz=OFF
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
        -DWITH_CUDA=OFF
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
        BUILD_BYPRODUCTS ${OPENCV_LIBS}
        GIT_TAG 4.1.2
        GIT_REPOSITORY https://github.com/opencv/opencv.git
        GIT_PROGRESS ON
)

add_library(
        LibCam
        ${CMAKE_CURRENT_LIST_DIR}/src/SlowMotion.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/LongExposure.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/VideoManager.cpp
)

target_include_directories(LibCam PUBLIC ${OPENCV_INSTALL_DIR}/include/opencv4)
target_link_libraries(LibCam opencv_world)
add_dependencies(LibCam opencv)
