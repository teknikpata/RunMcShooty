set(EVENTS_FILES
        event.h)

add_library(events ${EVENTS_FILES})
#find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)
#target_link_libraries(utils sfml-graphics)