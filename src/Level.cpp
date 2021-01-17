#include <iostream>
#include <cstdint>
#include <stdexcept>
#include "GTMR/Level.h"

using namespace gt;

static inline uint32_t globalToLocalCoord(const uint32_t global) {
	return global % CHUNK_SIZE;
}

static inline uint32_t tileToChunkCoord(const uint32_t tile) {
	return tile / CHUNK_SIZE;
}

static inline void checkBounds(uint32_t x, uint32_t y, uint32_t maxX, uint32_t maxY) {
	if (x >= maxX || y >= maxY) {
		std::cerr << "Error: tile " << "(" << x << ", " << y << ") out of bounds" << std::endl;
		throw std::domain_error("Out of bounds");
	}
}

Level::Level()
	: m_width{},
	  m_height{},
	  m_hChunks{},
	  m_vChunks{},
	  m_chunks{ 0, 0 } {}

Level::Level(const uint32_t width, const uint32_t height, const sf::Image& texAtlas)
	: m_width{width},
	  m_height{height},
	  m_hChunks{((width - 1) / CHUNK_SIZE) + 1},
	  m_vChunks{((height - 1) / CHUNK_SIZE) + 1},
	  m_chunks{m_vChunks, m_hChunks} {
	
	m_texAtlas.loadFromImage(texAtlas);

	for (size_t cy = 0; cy < m_vChunks; cy++) {
		for (size_t cx = 0; cx < m_hChunks; cx++) {
			m_chunks.get(cx, cy).setPosition(
				static_cast<float>(cx * CHUNK_SIZE * TILE_SIZE),
				static_cast<float>(cy * CHUNK_SIZE * TILE_SIZE)
			);
		}
	}
}

// Probably not the most efficient way to do this, but it works.
Level::Level(const Level& other) : Level() {
	*this = other;
}

Level& Level::operator=(const Level& other) {
	m_width = other.m_width;
	m_height = other.m_height;
	m_hChunks = other.m_hChunks;
	m_vChunks = other.m_vChunks;
	m_chunks = other.m_chunks;

	const sf::Image tempAtlas = other.m_texAtlas.copyToImage();
	m_texAtlas.loadFromImage(tempAtlas);

	return *this;
}

void Level::setTexAtlas(const sf::Image &texAtlas) {
    m_texAtlas.loadFromImage(texAtlas);
}


TileID Level::get(const uint32_t x, const uint32_t y) const {

	checkBounds(x, y, m_width, m_height);

	const uint32_t chunkX = tileToChunkCoord(x);
	const uint32_t chunkY = tileToChunkCoord(y);
	const uint32_t chunkInnerX = globalToLocalCoord(x);
	const uint32_t chunkInnerY = globalToLocalCoord(y);

	return m_chunks.get(chunkX, chunkY).get(chunkInnerX, chunkInnerY);
}


// ReSharper disable once CppMemberFunctionMayBeConst
void gt::Level::update(const uint32_t x, const uint32_t y, const TileID val) {

	checkBounds(x, y, m_width, m_height);

	const uint32_t chunkX = tileToChunkCoord(x);
	const uint32_t chunkY = tileToChunkCoord(y);
	const uint32_t chunkInnerX = globalToLocalCoord(x);
	const uint32_t chunkInnerY = globalToLocalCoord(y);

	m_chunks.get(chunkX, chunkY).update(chunkInnerX, chunkInnerY, val);
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	// Bind the texture atlas
	states.texture = &m_texAtlas;
	
	// Find the section of the world shown on the screen
	const sf::View view = target.getView();
	const sf::IntRect viewRect(
		static_cast<int>(view.getCenter().x - (view.getSize().x / 2)),
		static_cast<int>(view.getCenter().y - (view.getSize().y / 2)),
		static_cast<int>(view.getSize().x),
		static_cast<int>(view.getSize().y)
	);

	// Calculate which chunks are within that
	const uint32_t chunkStartX = (viewRect.left / TILE_SIZE) / CHUNK_SIZE;
	const uint32_t chunkEndX = std::min(static_cast<uint32_t>(m_chunks.cols() - 1), chunkStartX + ((viewRect.width / TILE_SIZE) / CHUNK_SIZE) + 1);
	const uint32_t chunkStartY = (viewRect.top / TILE_SIZE) / CHUNK_SIZE;
	const uint32_t chunkEndY = std::min(static_cast<uint32_t>(m_chunks.rows() - 1), chunkStartY + ((viewRect.height / TILE_SIZE) / CHUNK_SIZE) + 1);

	// Render them
	for (uint32_t cy = chunkStartY; cy <= chunkEndY; cy++) {
		for (uint32_t cx = chunkStartX; cx <= chunkEndX; cx++) {
			target.draw(m_chunks.get(cx, cy), states);
		}
	}
}