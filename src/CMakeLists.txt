add_subdirectory(utils)
add_subdirectory(entities)
add_subdirectory(managers)

add_executable(rms main.cpp game.cpp world.cpp weapon.h)

IF (WIN32)
    file(COPY ${SFML_DIR}..\\..\\..\\..\\bin/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
ENDIF (WIN32)

file(COPY
        ${CMAKE_SOURCE_DIR}/assets/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)

target_include_directories(entities PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )

target_include_directories(utils PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )

target_include_directories(managers PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(rms sfml-system sfml-window sfml-graphics sfml-network sfml-audio utils entities managers)