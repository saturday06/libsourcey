if(HAVE_WEBRTC)
  if(HAVE_FFMPEG)
    add_subdirectory(webrtcstreamer)
  endif()
  add_subdirectory(webrtcrecorder)
  add_subdirectory(webrtccapturer)

  if(HAVE_OPENCV)
    add_subdirectory(opencvanalyzer)
  endif()
endif()
