cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含目录
include_directories(include)

# 添加可执行文件
add_executable(snake_game
    src/main.cpp
    src/draw.cpp
    src/food.cpp
    src/game.cpp
    src/menu.cpp
    src/snake.cpp
    src/music.cpp
)

target_link_libraries(snake_game winmm)

# 直接链接Windows库（不需要find_library）
if(WIN32)
    target_link_libraries(snake_game gdi32)
endif()

# 设置输出目录
set_target_properties(snake_game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)