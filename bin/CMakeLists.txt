add_executable(${PROJECT_NAME} main.cpp ../src/FramesFactory/Frame.h ../src/ConvertionFuncs/assistant.h ../src/HandleParse/id3parse.h ../src/FrameParse/FrameHandle.h ../src/FrameParse/FrameHandle.cpp ../src/ConvertionFuncs/assistant.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE lib)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})