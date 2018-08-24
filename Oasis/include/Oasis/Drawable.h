#pragma once

#include "SpriteBatch.h"
#include "Texture2D.h"
#include "Vertex.h"
#include <string>
#include <glm/glm.hpp>
#include "GameObject.h"


namespace Oasis
{
	class Drawable : public GameObject
	{
	public:
		Drawable();
		Drawable(glm::vec2 pos, const std::string& texturePath, float scale = 1, Color color = { 255, 255, 255, 255 });
		void Draw(SpriteBatch& spriteBatch);

		glm::vec2 GetOrigin() const;
		float GetScale() const { return _scale; }

	protected:
		float _scale;
		Color _color;

	private:
		Texture2D* _texture;
	};
}
