#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <iterator>

class GridIterator {
public:
	GridIterator(): m_width(10), m_length(10), m_index(0) {}
	GridIterator(int width, int length, int index = 0) : m_width(width), m_length(length), m_index(index) {}

	glm::mat4 operator*() const {
		return get_position(m_index);
	}

	GridIterator& operator++() {
		++m_index;
		return *this;
	}

	bool operator!=(const GridIterator& other) const {
		return m_index != other.getIndex();
	}

	int getIndex() const { return m_index; }

private:
	int m_width;
	int m_length;
	int m_index;

	glm::mat4 get_position(int idx) const {
		int x = idx % m_width;
		int y = idx / m_width;
		auto pos = glm::vec3(x, perlin_noise(x,y), y);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, pos);
		return model;
	}

	// Perlin noise function (simplified for 2D grid)
	float perlin_noise(float x, float y) const {
		return fabs(sin(x * 12.9898 + y * 78.233) * 43758.5453) - floor(fabs(sin(x * 12.9898 + y * 78.233) * 43758.5453));
	}
};

class Grid {
public:
	Grid(int width, int height) : width(width), height(height) {}

	GridIterator begin() const { return GridIterator(width, height, 0); }
	GridIterator end() const { return GridIterator(width, height, width * height); }

private:
	int width, height;
};