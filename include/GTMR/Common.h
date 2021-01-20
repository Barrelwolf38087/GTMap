// This file is part of GTMR.
//
// GTMR is free software: you can redistribute it and/or modify
//         it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// GTMR is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with GTMR.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <cstdint>

// Types and constants used by multiple headers
namespace gt {

	// These will likely be configurable in the future
	constexpr static uint16_t CHUNK_SIZE = 16;
	constexpr static uint16_t TILE_SIZE = 64;
	constexpr static unsigned int TEXTURE_SIZE = 512;
	constexpr static size_t VERTS_PER_CHUNK = CHUNK_SIZE * CHUNK_SIZE * 4;

	typedef uint16_t TileID;
}