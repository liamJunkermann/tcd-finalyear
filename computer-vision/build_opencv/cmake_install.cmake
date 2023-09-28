# Install script for directory: /Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RELEASE")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlicensesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/licenses/opencv4" TYPE FILE RENAME "ippicv-readme.htm" FILES "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/3rdparty/ippicv/ippicv_mac/icv/readme.htm")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlicensesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/licenses/opencv4" TYPE FILE RENAME "ippicv-EULA.txt" FILES "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/3rdparty/ippicv/ippicv_mac/EULA.txt")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlicensesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/licenses/opencv4" TYPE FILE RENAME "ippicv-third-party-programs.txt" FILES "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/3rdparty/ippicv/ippicv_mac/third-party-programs.txt")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlicensesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/licenses/opencv4" TYPE FILE RENAME "ippiw-support.txt" FILES "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/3rdparty/ippicv/ippicv_mac/icv/../iw/../support.txt")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlicensesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/licenses/opencv4" TYPE FILE RENAME "ippiw-third-party-programs.txt" FILES "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/3rdparty/ippicv/ippicv_mac/icv/../iw/../third-party-programs.txt")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlicensesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/licenses/opencv4" TYPE FILE RENAME "ippiw-EULA.txt" FILES "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/3rdparty/ippicv/ippicv_mac/icv/../iw/../EULA.txt")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlicensesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/licenses/opencv4" TYPE FILE RENAME "flatbuffers-LICENSE.txt" FILES "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/3rdparty/flatbuffers/LICENSE.txt")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlicensesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/licenses/opencv4" TYPE FILE RENAME "ade-LICENSE" FILES "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/3rdparty/ade/ade-0.1.2a/LICENSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2" TYPE FILE FILES "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/cvconfig.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2" TYPE FILE FILES "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/opencv2/opencv_modules.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/opencv4/OpenCVModules.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/opencv4/OpenCVModules.cmake"
         "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/CMakeFiles/Export/lib/cmake/opencv4/OpenCVModules.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/opencv4/OpenCVModules-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/opencv4/OpenCVModules.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/opencv4" TYPE FILE FILES "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/CMakeFiles/Export/lib/cmake/opencv4/OpenCVModules.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/opencv4" TYPE FILE FILES "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/CMakeFiles/Export/lib/cmake/opencv4/OpenCVModules-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/opencv4" TYPE FILE FILES
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/unix-install/OpenCVConfig-version.cmake"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/unix-install/OpenCVConfig.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xscriptsx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/CMakeFiles/install/setup_vars_opencv4.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/opencv4" TYPE FILE FILES
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/platforms/scripts/valgrind.supp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/platforms/scripts/valgrind_3rdparty.supp"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/3rdparty/zlib/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/3rdparty/libjpeg-turbo/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/3rdparty/libtiff/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/3rdparty/libwebp/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/3rdparty/openjpeg/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/3rdparty/libpng/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/3rdparty/ippiw/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/3rdparty/protobuf/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/3rdparty/quirc/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/3rdparty/ittnotify/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/include/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/calib3d/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/core/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/dnn/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/features2d/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/flann/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/gapi/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/highgui/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/imgcodecs/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/imgproc/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/java/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/js/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/ml/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/objc/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/objdetect/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/photo/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/python/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/stitching/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/ts/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/video/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/videoio/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/.firstpass/world/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/core/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/flann/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/imgproc/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/ml/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/photo/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/python_tests/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/dnn/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/features2d/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/imgcodecs/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/videoio/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/calib3d/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/highgui/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/objdetect/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/stitching/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/ts/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/video/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/gapi/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/java_bindings_generator/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/js_bindings_generator/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/objc_bindings_generator/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/modules/python_bindings_generator/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/doc/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/data/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/apps/cmake_install.cmake")
  include("/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/samples/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/build_opencv/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
