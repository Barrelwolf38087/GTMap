#pragma once

#include <vector>
#include <algorithm>

namespace gt {

	// A dynamically-allocated 2-dimensional array.
	// The size is determined at construction, and is immutable thereafter.
	template<typename T>
	class Array2d {
		
		// A single larger vector instead of a real 2d array to simplify implementation.
		std::vector<T> m_vec;

		size_t m_rows;
		size_t m_cols;
	
	public:

		Array2d(const size_t rows, const size_t cols) : m_rows{ rows }, m_cols{ cols } {
			// The inner set of brackets after new is important
			// because it default-initializes built-in types
			m_vec.reserve(m_rows * m_cols);

			for (size_t i = 0; i < (m_rows * m_cols); i++) {
				m_vec.emplace_back();
			}
		}

		Array2d(const Array2d<T>& other) : m_rows{ other.m_rows }, m_cols{ other.m_cols } {
			*this = other;
		}

		Array2d& operator=(const Array2d<T>& other) {
			if (this != &other) {
				m_rows = other.m_rows;
				m_cols = other.m_cols;

				m_vec.reserve(m_rows * m_cols);
				
				// Somehow I feel like there's a more modern way to do this,
				// but if it works it works.
				for (size_t i = 0; i < (m_rows * m_cols); i++) {
					m_vec.emplace_back(other.m_vec[i]);
				}
			}

			return *this;
		}

		// Deleted to get rid of a warning
		// TODO: Implement these
		Array2d(Array2d<T>&& other) = delete;
		Array2d& operator=(Array2d<T>&& other) = delete;

		~Array2d() = default;

		[[nodiscard]] size_t rows() const { return m_rows; }
		[[nodiscard]] size_t cols() const { return m_cols; }
		
		// The size of the inner array.
		[[nodiscard]] size_t size() const { return m_rows * m_cols; }

		//T* operator[](const size_t row) const {
		//	size_t offset = row * m_cols;
		//	return m_vec.data();
		//}

		[[nodiscard]] T& get(const size_t x, const size_t y) const {
			// TODO: Find a way to do this that doesn't break const-correctness
			return const_cast<T&>(m_vec[(y * m_cols) + x]);
		}

		void update(const size_t x, const size_t y, T val) {
			m_vec[(y * m_cols) + x] = val;
		}
	};

}

