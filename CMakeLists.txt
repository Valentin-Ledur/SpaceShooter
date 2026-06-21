cmake_minimum_required(VERSION 4.0)

project(SpaceShooter)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(SpaceShooter
    src/main.cpp
    src/Utils/Utils.cpp
    src/Player/PlayerManager.cpp
    src/Enemy/Asteroid/Asteroid.cpp
    src/Enemy/EnemyManager.cpp
    src/Game/Game.cpp
    src/Projectile/ProjectileManager.cpp
    src/UI/Button/Button.cpp
    src/UI/Menu/Menu.cpp
    src/UI/TextArea/TextArea.cpp
    src/UI/UIManager.cpp
    src/Animation/Animation.cpp
)

target_compile_features(SpaceShooter PUBLIC cxx_std_17)

target_include_directories(SpaceShooter PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_PREFIX_PATH}/include"
    "${CMAKE_PREFIX_PATH}/include/SDL2"
)

target_link_libraries(SpaceShooter PRIVATE 
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
    $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
)

if (EMSCRIPTEN)

    set_target_properties(SpaceShooter PROPERTIES SUFFIX ".html")

    target_link_options(SpaceShooter PRIVATE
        "-sALLOW_MEMORY_GROWTH=1"
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

    target_compile_definitions(SpaceShooter PRIVATE _SCL_SECURE_NO_WARNINGS)
endif()