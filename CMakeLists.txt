cmake_minimum_required(VERSION 3.11)

project(hello)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    main2.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    pspdebug
    pspdisplay
    pspge
    pspctrl
    raylib
    GL
    png
    z
    glut
    GLU
    pspvfpu
)

# Create an EBOOT.PBP file
create_pbp_file(
    TARGET ${PROJECT_NAME}
    ICON_PATH NULL
    BACKGROUND_PATH NULL
    PREVIEW_PATH NULL
    TITLE ${PROJECT_NAME}
    VERSION 01.00
)
