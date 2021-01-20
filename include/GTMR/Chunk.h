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
#include <array>
#include <SFML/Graphics.hpp>

#include "Common.h"
#include "Array2d.h"
// Heavily influenced by https://github.com/dfranx/Tily <3

namespace gt {

	class Chunk final : public sf::Drawable, public sf::Transformable {
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		Array2d<TileID> m_tiles;
		//std::array<std::array<TileID, CHUNK_SIZE>, CHUNK_SIZE> m_tiles;

		std::array<sf::Vertex, VERTS_PER_CHUNK> m_vertexArray; // CPU side
		sf::VertexBuffer m_vertexBuffer; // GPU side

	public:
		Chunk();

		TileID get(uint32_t x, uint32_t y) const;
		void update(uint32_t x, uint32_t y, TileID val);

	};
}


