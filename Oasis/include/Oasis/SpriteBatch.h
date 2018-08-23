#pragma once;

#include "Vertex.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

namespace Oasis
{
	enum class GlyphSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	struct Glyph
	{
		Glyph() {}

		Glyph(GLuint tex, float x, float y, float dx, float dy, float w, float h, float sin, float cos,
			const Color& color, const glm::vec2& uvTopLeft, const glm::vec2& uvBottomRight, float layerDepth)
			: texture(tex),
			depth(layerDepth)
		{
			topLeft.color = color;
			topLeft.setPosition(x + dx * cos - dy * sin, y + dx * sin + dy * cos);
			topLeft.setUV(uvTopLeft.x, uvBottomRight.y);

			topRight.color = color;
			topRight.setPosition(x + (dx + w)*cos - dy * sin, y + (dx + w)*sin + dy * cos);
			topRight.setUV(uvBottomRight.x, uvBottomRight.y);

			bottomLeft.color = color;
			bottomLeft.setPosition(x + dx * cos - (dy + h)*sin, y + dx * sin + (dy + h)*cos);
			bottomLeft.setUV(uvTopLeft.x, uvTopLeft.y);

			bottomRight.color = color;
			bottomRight.setPosition(x + (dx + w)*cos - (dy + h)*sin, y + (dx + w)*sin + (dy + h)*cos);
			bottomRight.setUV(uvBottomRight.x, uvTopLeft.y);
		}




		Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint tex, float layerDepth, const Color& color) :
			texture(tex), depth(layerDepth)
		{
			topLeft.color = color;
			topLeft.setPosition(destRect.x, destRect.y);
			topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

			topRight.color = color;
			topRight.setPosition(destRect.x + destRect.z, destRect.y);
			topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

			bottomLeft.color = color;
			bottomLeft.setPosition(destRect.x, destRect.y + destRect.w);
			bottomLeft.setUV(uvRect.x, uvRect.y);

			bottomRight.color = color;
			bottomRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
			bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
		}

		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	};

	struct RenderBatch
	{
		RenderBatch(GLuint offset, GLuint numVertices, GLuint texture)
			: offset(offset), numVertices(numVertices), texture(texture) { }

		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void Init();

		void Begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void End();

		void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);
		void Draw(GLuint texture, const glm::vec2& position, const glm::vec4& uvRect, const Color& color,
			float rotation, const glm::vec2& origin, const glm::vec2& scale, float depth);

		void Render();

	private:
		void CreateRenderBatches();
		void CreateVertexArray();
		void SortGlyphs();

		GLuint _vbo;
		GLuint _vao;

		GlyphSortType _sortType;

		std::vector<Glyph*> _glyphPointers;
		std::vector<Glyph> _glyphs;
		std::vector<RenderBatch> _renderBatches;
	};
}