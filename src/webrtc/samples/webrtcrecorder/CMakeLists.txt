include_dependency(WebRTC REQUIRED)

#define_sourcey_module_sample(webrtcrecorder base crypto net http util json socketio symple webrtc)

#macro(define_sourcey_module_sample name)

project(webrtcrecorder)

# Include internal module dependencies
#include_sourcey_modules(${ARGN})

# Add source files
file(GLOB lib_hdrs "*.h*")
file(GLOB lib_srcs "*.cpp")

source_group("Src" FILES ${lib_srcs})
source_group("Include" FILES ${lib_hdrs})

message(STATUS "Including module sample webrtcrecorder")
#message(STATUS "    Libraries: ${LibSourcey_INCLUDE_LIBRARIES}")
#message(STATUS "    Library Dirs: ${LibSourcey_LIBRARY_DIRS}")
#message(STATUS "    Include Dirs: ${LibSourcey_INCLUDE_DIRS}")

add_executable(webrtcrecorder ${lib_srcs} ${lib_hdrs})
add_library(webrtcelevator STATIC signaler.cpp lib.cpp ${lib_hdrs})

# Include library and header directories
set_default_project_directories(webrtcrecorder base crypto net http util json socketio symple webrtc)
set_default_project_directories(webrtcelevator base crypto net http util json socketio symple webrtc)

# Include linker dependencies
set_default_project_dependencies(webrtcrecorder base crypto net http util json socketio symple webrtc)
set_default_project_dependencies(webrtcelevator base crypto net http util json socketio symple webrtc)

if(ENABLE_SOLUTION_FOLDERS)
  set_target_properties(webrtcrecorder PROPERTIES FOLDER "samples")
endif()
set_target_properties(webrtcrecorder PROPERTIES DEBUG_POSTFIX "d")

install(TARGETS webrtcrecorder RUNTIME DESTINATION "${LibSourcey_SHARED_INSTALL_DIR}/samples/webrtcrecorder" COMPONENT samples)
