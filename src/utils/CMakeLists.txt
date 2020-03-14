set(UTILS_FILES
        collision_box.h
        collision_box.cpp
        file.h
        math.h
        camera.h)

add_library(utils ${UTILS_FILES})
find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)
target_link_libraries(utils sfml-graphics)