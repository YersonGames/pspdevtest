cmake_minimum_required(VERSION 3.11)

project(raylibGameTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    main.cpp
    src/Player.cpp
    src/CollisionBlock.cpp
    src/Hitbox.cpp
    src/Hurtbox.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE src/)

find_package(SDL3 REQUIRED)
find_package(SDL3_mixer REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    raylib
    SDL3::SDL3
    SDL3_mixer::SDL3_mixer
    -lGL -lGLU -lglut -lz -lpspvfpu -lpsphprm -lpspsdk -lpspctrl -lpspumd -lpsprtc -lpsppower -lpspgum -lpspgu -lpspaudiolib -lpspaudio -lpsphttp -lpspssl -lpspwlan
    -lpspnet_adhocmatching -lpspnet_adhoc -lpspnet_adhocctl -lm -lpspvram
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
