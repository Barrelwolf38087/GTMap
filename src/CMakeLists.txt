# This file is part of GTMR.
#
# GTMR is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# GTMR is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GTMR.  If not, see <https://www.gnu.org/licenses/>.

target_sources(GTMR
    PRIVATE
        Array2d.h
        Chunk.cpp
        Level.cpp
)

target_include_directories(GTMR PUBLIC ${CMAKE_SOURCE_DIR}/include PRIVATE ${CMAKE_SOURCE_DIR}/src)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
target_link_libraries(GTMR PUBLIC sfml-system sfml-window sfml-graphics)
