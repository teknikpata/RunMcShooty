set(MANAGERS_FILES
        texture_manager.h
        texture_manager.cpp)

add_library(managers ${MANAGERS_FILES})
find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)
target_link_libraries(managers sfml-graphics)