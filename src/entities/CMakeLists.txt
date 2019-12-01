set(ENTITIES_FILES
        Entitiy.h
        Entitiy.cpp
        SceneNode.h
        SceneNode.cpp)

add_library(entities ${ENTITIES_FILES})
find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)
target_link_libraries(entities sfml-graphics)