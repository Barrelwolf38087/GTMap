#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

#include "Common.h"
#include "Chunk.h"
#include "Array2d.h"

// Heavily influenced by https://github.com/dfranx/Tily <3
// Without Tily to reference, this project would have taken far longer.
//
// Currently, this functions almost exactly like Tily except for one key difference:
// it does not support multiple layers.
// 
// This is because Tily's layer system is designed to work around a technical constraint
// wherein each layer is limited in the number of different tile types it can have.
// This is because each layer's texture atlas is an OpenGL texture, which has a system-dependent
// maximum size. You cannot, therefore, have more tile types than you can fit textures
// in the atlas. The exact number of tile types each layer can have is dependent
// on the hardware, Tily's atlas size configuration value, and the size of each tile.
// 
// Additionally, Tily's documentation and interface do not make this clear, leaving
// the user to stumble into the limitation themselves.
// 
// A proper solution to this problem would be to take one large atlas from the user
// as a sf::Image (which does not have the same limitations as a texture) and dynamically
// split it into multiple sf::Texture objects depending on the maximum texture size,
// which can be detected at runtime. This system would also need to abstract away
// the use of the smaller atlases so it is seamless for the user. This is what my rendering
// system will do once it's completed. For now, we will simply stick with using one texture atlas.

namespace gt {
	class Level final : public sf::Drawable {
		// All the tile textures in one big texture
		// This method severely limits the number of tile types we can have
		// in a level. TODO: Create a more scalable system using multiple texture atlases.
		sf::Texture m_texAtlas;

		uint32_t m_width;
		uint32_t m_height;

		uint32_t m_hChunks;
		uint32_t m_vChunks;

		Array2d<Chunk> m_chunks;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	
	public:

		// Needed for copy constructor
		Level();

		Level(uint32_t width, uint32_t height, const sf::Image& texAtlas);

		Level(const Level& other);
		Level& operator=(const Level& other);

		TileID get(uint32_t x, uint32_t y) const;
		void update(uint32_t x, uint32_t y, TileID val);
		
	};

}
