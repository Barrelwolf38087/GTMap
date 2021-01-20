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

#include <iostream>

#include "GTMR/Chunk.h"

using namespace gt;

Chunk::Chunk() : m_tiles{ CHUNK_SIZE, CHUNK_SIZE } {
	
	m_vertexBuffer.setPrimitiveType(sf::PrimitiveType::Quads);
	m_vertexBuffer.setUsage(sf::VertexBuffer::Usage::Dynamic);

	// Width, height and vertices per tile
	m_vertexBuffer.create(VERTS_PER_CHUNK);

	// Initialize vertex array
	for (int y = 0; y < CHUNK_SIZE; y++) {
		for (int x = 0; x < CHUNK_SIZE; x++) {
			m_tiles.update(x, y, 0);

			const size_t vertexOffset = ((y * CHUNK_SIZE) + x) * 4;

			sf::Vertex* tileVert = &m_vertexArray[vertexOffset];

			tileVert[0].position = sf::Vector2f(
				static_cast<float>(x * TILE_SIZE),
				static_cast<float>(y * TILE_SIZE)
			);
			tileVert[1].position = sf::Vector2f(
				static_cast<float>((x + 1) * TILE_SIZE),
				static_cast<float>(y * TILE_SIZE)
			);
			tileVert[2].position = sf::Vector2f(
				static_cast<float>((x + 1) * TILE_SIZE),
				static_cast<float>((y + 1) * TILE_SIZE)
			);
			tileVert[3].position = sf::Vector2f(
				static_cast<float>(x * TILE_SIZE),
				static_cast<float>((y + 1) * TILE_SIZE)
			);

			tileVert[0].texCoords = sf::Vector2f(0, 0);
			tileVert[1].texCoords = sf::Vector2f(TILE_SIZE, 0);
			tileVert[2].texCoords = sf::Vector2f(TILE_SIZE, TILE_SIZE);
			tileVert[3].texCoords = sf::Vector2f(0, TILE_SIZE);
		}
	}

	// Send to GPU
	m_vertexBuffer.update(m_vertexArray.data());
}

void Chunk::update(const uint32_t x, uint32_t y, const TileID val) {
	if (m_tiles.get(x, y) != val) {

		m_tiles.update(x, y, val);

		const size_t vertexOffset = ((y * CHUNK_SIZE) + x) * 4;

		sf::Vertex* vert = &m_vertexArray[vertexOffset];

		// Texture coordinates
		const uint16_t tx = (val * TILE_SIZE) % TEXTURE_SIZE;
		const uint16_t ty = ((val * TILE_SIZE) / TEXTURE_SIZE) * TILE_SIZE;

		vert[0].texCoords = sf::Vector2f(tx, ty);
		vert[1].texCoords = sf::Vector2f(static_cast<float>(tx + TILE_SIZE), ty);
		vert[2].texCoords = sf::Vector2f(static_cast<float>(tx + TILE_SIZE), static_cast<float>(ty + TILE_SIZE));
		vert[3].texCoords = sf::Vector2f(tx, static_cast<float>(ty + TILE_SIZE));

		//m_vertexBuffer.update(m_vertexArray.data() + vertexOffset, 4, vertexOffset);
		m_vertexBuffer.update(m_vertexArray.data());
	}
}


void Chunk::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	target.draw(m_vertexBuffer, states);
}

TileID Chunk::get(const uint32_t x, const uint32_t y) const {
	return m_tiles.get(x, y);
}
