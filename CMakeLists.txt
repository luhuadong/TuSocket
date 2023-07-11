cmake_minimum_required(VERSION 3.0)
project(tusockit)

set(CMAKE_BUILD_TYPE "Debug")

# 添加可执行文件
add_executable(${PROJECT_NAME} src/main.c src/tusockit.c)

# 添加头文件目录
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# 链接 pthread 多线程库
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

# 如果需要链接额外的库文件，可以使用类似以下的语法
# target_link_libraries(your_program_name library_name)

# 设置编译选项（可选）
# 若需要特定的编译选项，可以取消注释以下行，并替换为你需要的选项
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

# 设置输出目录（可选）
# 若需要将可执行文件放置在特定目录下，可以取消注释以下行，并替换为你所需的路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# 完成配置