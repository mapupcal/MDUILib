
INCLUDE_DIRECTORIES(
    ${MDUILIB_HOME_DIR}
    ${MDUILIB_HOME_DIR}/WindowXX
)

add_executable(WindowXX
    WindowXXApplication.hpp
    WindowXXApplication.cpp
)
target_link_libraries(WindowXX Framework)