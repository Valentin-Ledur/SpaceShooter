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

target_include_directories(SpaceShooter
    "${CMAKE_PREFIX_PATH}/include"
    "${CMAKE_PREFIX_PATH}/include/SDL2"
)

target_compile_features(project PUBLIC cxx_std_11)

target_link_libraries(project PRIVATE 
	SDL2::SDL2 
	SDL2_image::SDL2_image 
	SDL2_ttf::SDL2_ttf
)


if (MSVC)
	target_compile_definitions(project PRIVATE _SCL_SECURE_NO_WARNINGS)
else ()
	target_compile_options(project PRIVATE -Wall -Wno-long-long -fPIC)
endif()

target_compile_definitions(project PRIVATE $<IF:$<CONFIG:Debug>,DEBUG,NDEBUG>)
