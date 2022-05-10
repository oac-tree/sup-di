target_include_directories(sup-di
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(sup-di
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/ObjectManager.cpp
)
