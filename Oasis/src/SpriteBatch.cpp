#include "SpriteBatch.h"

#include <algorithm>

namespace Oasis
{
	SpriteBatch::SpriteBatch() : _vbo(0), _vao(0)
	{

	}

	SpriteBatch::~SpriteBatch()
	{

	}

	void SpriteBatch::Init()
	{
		CreateVertexArray();
	}

	void SpriteBatch::Begin(GlyphSortType sortType)
	{
		_sortType = sortType;
		_renderBatches.clear();
		_glyphs.clear();
	}

	void SpriteBatch::End()
	{
		_glyphPointers.resize(_glyphs.size());
		for (int i = 0; i < _glyphs.size(); i++)
		{
			_glyphPointers[i] = &_glyphs[i];
		}
		SortGlyphs();
		CreateRenderBatches();
	}

	void SpriteBatch::Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color)
	{
		_glyphs.emplace_back(destRect, uvRect, texture, depth, color);
	}

	void SpriteBatch::Render()
	{
		glBindVertexArray(_vao);

		for (int i = 0; i < _renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

			glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::CreateRenderBatches()
	{
		std::vector<Vertex> vertices;
		vertices.resize(_glyphs.size() * 6);

		if (_glyphs.empty())
			return;

		int offset = 0;
		int currentVertex = 0;

		_renderBatches.emplace_back(offset, 6, _glyphPointers[0]->texture);
		vertices[currentVertex++] = _glyphPointers[0]->topLeft;
		vertices[currentVertex++] = _glyphPointers[0]->bottomLeft;
		vertices[currentVertex++] = _glyphPointers[0]->bottomRight;
		vertices[currentVertex++] = _glyphPointers[0]->bottomRight;
		vertices[currentVertex++] = _glyphPointers[0]->topRight;
		vertices[currentVertex++] = _glyphPointers[0]->topLeft;
		offset += 6;

		for (int currentGlyph = 1; currentGlyph < _glyphPointers.size(); currentGlyph++)
		{
			if (_glyphPointers[currentGlyph]->texture != _glyphPointers[currentGlyph - 1]->texture)
			{
				_renderBatches.emplace_back(offset, 6, _glyphPointers[currentGlyph]->texture);
			}
			else
			{
				_renderBatches.back().numVertices += 6;
			}
			vertices[currentVertex++] = _glyphPointers[currentGlyph]->topLeft;
			vertices[currentVertex++] = _glyphPointers[currentGlyph]->bottomLeft;
			vertices[currentVertex++] = _glyphPointers[currentGlyph]->bottomRight;
			vertices[currentVertex++] = _glyphPointers[currentGlyph]->bottomRight;
			vertices[currentVertex++] = _glyphPointers[currentGlyph]->topRight;
			vertices[currentVertex++] = _glyphPointers[currentGlyph]->topLeft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		// Orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		// Upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::CreateVertexArray()
	{
		if (_vao == 0)
		{
			glGenVertexArrays(1, &_vao);
		}
		glBindVertexArray(_vao);

		if (_vbo == 0)
		{
			glGenBuffers(1, &_vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		// Tell openGL that we want to use the first attribute array.
		// We only need one array right now since we are only using position
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// this is the position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		// this is the color attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		// this is the UV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));


		glBindVertexArray(0);

	}

	void SpriteBatch::SortGlyphs()
	{
		switch (_sortType)
		{
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(),
				[](Glyph* a, Glyph* b)
			{
				return a->depth < b->depth;
			});
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(),
				[](Glyph* a, Glyph* b)
			{
				return a->depth > b->depth;
			});
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(),
				[](Glyph* a, Glyph* b)
			{
				return a->texture < b->texture;
			});
			break;
		}
	}

	//    void SpriteBatch::Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, const glm::vec2& origin,
	//                           float rotation, float scale, float depth, const Color& color)
	//    {
	//
	//        //Glyph g()
	//        _glyphs.emplace_back(glm::vec4(destRect.x, destRect.y, destRect.z * scale, destRect.w * scale), uvRect, texture,
	//                             -origin.x * scale, -origin.y * scale, depth, color);
	//       //Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint tex, float dx, float dy, float sin, float cos,  float layerDepth, const Color& color) :
	//    }


	void SpriteBatch::Draw(GLuint texture, const glm::vec2& position, const glm::vec4& uvRect, const Color& color,
		float rotation, const glm::vec2& origin, const glm::vec2& scale, float depth)
	{
		_glyphs.emplace_back(texture, position.x, position.y, -origin.x * scale.x, -origin.y * scale.y,
			(origin.x * 2) * scale.x, (origin.y * 2) * scale.y, sin(rotation), cos(rotation),
			color, glm::vec2(0.0f), glm::vec2(1.0f), depth);
	}
}