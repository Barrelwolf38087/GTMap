
target_sources(GTMR
    PRIVATE
        Array2d.h
        Chunk.cpp
        Level.cpp
)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
target_link_libraries(GTMR PUBLIC sfml-system sfml-window sfml-graphics)