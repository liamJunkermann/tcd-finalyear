# Install script for directory: /Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xsamplesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/opencv4/samples/cpp" TYPE FILE FILES
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/3calibration.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/CMakeLists.txt"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/application_trace.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/aruco_dict_utils.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/asift.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/audio_spectrogram.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/barcode.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/bgfg_segm.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/calibration.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/camshiftdemo.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/cloning_demo.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/cloning_gui.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/connected_components.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/contours2.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/convexhull.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/cout_mat.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/create_mask.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/dbt_face_detection.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/delaunay2.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/demhist.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/detect_blob.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/detect_mser.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/dft.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/digits_lenet.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/digits_svm.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/dis_opticalflow.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/distrans.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/drawing.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/edge.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/ela.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/em.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/epipolar_lines.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/essential_mat_reconstr.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/facedetect.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/facial_features.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/falsecolor.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/fback.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/ffilldemo.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/filestorage.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/fitellipse.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/flann_search_dataset.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/grabcut.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/image_alignment.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/imagelist_creator.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/imagelist_reader.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/imgcodecs_jpeg.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/inpaint.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/intelligent_scissors.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/intersectExample.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/kalman.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/kmeans.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/laplace.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/letter_recog.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/lkdemo.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/logistic_regression.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/lsd_lines.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/mask_tmpl.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/matchmethod_orb_akaze_brisk.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/minarea.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/morphology2.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/neural_network.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/npr_demo.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/opencv_version.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/pca.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/peopledetect.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/phase_corr.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/points_classifier.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/polar_transforms.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/qrcode.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/segment_objects.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/select3dobj.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/simd_basic.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/smiledetect.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/squares.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/stereo_calib.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/stereo_match.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/stitching.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/stitching_detailed.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/text_skewness_correction.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/train_HOG.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/train_svmsgd.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/travelsalesman.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/tree_engine.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/videocapture_audio.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/videocapture_audio_combination.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/videocapture_basic.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/videocapture_camera.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/videocapture_gphoto2_autofocus.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/videocapture_gstreamer_pipeline.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/videocapture_image_sequence.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/videocapture_microphone.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/videocapture_obsensor.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/videocapture_openni.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/videocapture_realsense.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/videocapture_starter.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/videowriter_basic.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/warpPerspective_demo.cpp"
    "/Users/liam/Documents/dev/tcd-finalyear/computer-vision/opencv/samples/cpp/watershed.cpp"
    )
endif()

