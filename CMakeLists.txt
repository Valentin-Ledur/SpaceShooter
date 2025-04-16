cmake_minimum_required(VERSION 4.0)

project(SpaceShooter)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(SpaceShooter
    src/main.cpp
    src/Enemy/Asteroid.cpp
    src/Game/Game.cpp
    src/Player/Player.cpp
    src/Projectile/Projectile.cpp
)

target_compile_features(SpaceShooter PUBLIC cxx_std_11)

target_include_directories(SpaceShooter PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_PREFIX_PATH}/include"
    "${CMAKE_PREFIX_PATH}/include/SDL2"
)

target_link_libraries(SpaceShooter PRIVATE 
	SDL2::SDL2main 
	SDL2::SDL2 
	SDL2_image::SDL2_image 
	SDL2_ttf::SDL2_ttf
)


if (MSVC)
    target_compile_definitions(SpaceShooter PRIVATE _SCL_SECURE_NO_WARNINGS)
else ()
    target_compile_options(SpaceShooter PRIVATE -Wall -Wno-long-long -fPIC)
endif()

target_compile_definitions(SpaceShooter PRIVATE $<IF:$<CONFIG:Debug>,DEBUG,NDEBUG>)
