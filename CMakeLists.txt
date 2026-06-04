cmake_minimum_required(VERSION 4.0)

project(SpaceShooter)

find_package(SDL2 REQUIRED)

if (EMSCRIPTEN)

elseif(MSVC)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
endif()

add_executable(SpaceShooter
    src/main.cpp
    src/Utils/Utils.cpp
    src/UI/Button/Button.cpp
    src/UI/TextArea/TextArea.cpp
    src/UI/Menu/Menu.cpp
    src/Game/Game.cpp
    src/Enemy/Asteroid.cpp
    src/Projectile/Projectile.cpp
    src/Player/Player.cpp
)

target_compile_features(SpaceShooter PUBLIC cxx_std_17)

target_include_directories(SpaceShooter PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_PREFIX_PATH}/include"
    "${CMAKE_PREFIX_PATH}/include/SDL2"
)

if (EMSCRIPTEN)

    set_target_properties(SpaceShooter PROPERTIES SUFFIX ".html")

    target_compile_options(SpaceShooter PRIVATE
        "-sUSE_SDL=2"
        "-sUSE_SDL_IMAGE=2"
        "-sUSE_SDL_TTF=2"
    )

    target_link_options(SpaceShooter PRIVATE
        "-sUSE_SDL=2"
        "-sUSE_SDL_IMAGE=2"
        "-sSDL2_IMAGE_FORMATS=['png']"
        "-sUSE_SDL_TTF=2"
        "SHELL:--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/data@data"
        "SHELL:--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/font@font"
    )

elseif(MSVC)
    add_custom_command(TARGET SpaceShooter POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/data"
            "$<TARGET_FILE_DIR:SpaceShooter>/data"
            
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/font"
            "$<TARGET_FILE_DIR:SpaceShooter>/font"
    )

    target_include_directories(SpaceShooter PUBLIC
    "${CMAKE_PREFIX_PATH}/include"
    "${CMAKE_PREFIX_PATH}/include/SDL2"
    )

    target_link_libraries(SpaceShooter PRIVATE 
	SDL2::SDL2main 
	SDL2::SDL2 
	SDL2_image::SDL2_image 
	SDL2_ttf::SDL2_ttf
    )

endif()



if (MSVC)
    target_compile_definitions(SpaceShooter PRIVATE _SCL_SECURE_NO_WARNINGS)
elseif(EMSCRIPTEN)
    target_compile_definitions(SpaceShooter PRIVATE -DCMAKE_BUILD_TYPE=Release)
else ()
    target_compile_options(SpaceShooter PRIVATE -Wall -Wno-long-long -fPIC)
endif()

target_compile_definitions(SpaceShooter PRIVATE $<IF:$<CONFIG:Debug>,DEBUG,NDEBUG>)