set(ENTITIES_FILES
        entity.h
        entity.cpp
        movable_entity.h
        movable_entity.cpp
        static_entity.cpp
        static_entity.h
        player.cpp
        player.h)

add_library(entities ${ENTITIES_FILES})
find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)
target_link_libraries(entities graphic sfml-graphics)
