#set(MANAGERS_FILES ResourceManager.h)
#add_library(managers ${MANAGERS_FILES})

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)
target_link_libraries(sfml-graphics)