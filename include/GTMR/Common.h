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