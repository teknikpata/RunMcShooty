set(GRAPHIC_FILES
        sprite.h
        sprite.cpp animation_controller.h)

add_library(graphic ${GRAPHIC_FILES})
find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)
target_link_libraries(graphic sfml-graphics)