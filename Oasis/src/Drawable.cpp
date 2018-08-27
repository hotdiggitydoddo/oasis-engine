#include "Drawable.h"
#include "ResourceManager.h"

namespace Oasis
{
	Drawable::Drawable(glm::vec2 pos, const std::string& texturePath, float scale, Color color)
		: _scale(scale), _color(color)
	{
		_position = pos;
		_texture = ResourceManager::LoadTexture(texturePath.c_str(), true, "");
	}
	
	void Drawable::Draw(SpriteBatch& spriteBatch)
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(_position, 0.0f));

		model = glm::translate(model, glm::vec3(0.5f * _texture->Width, 0.5f * _texture->Height, 0.0f));
		//model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f * _texture->Width, -0.5f * _texture->Height, 0.0f));
		model = glm::scale(model, glm::vec3(_scale, _scale, 1.0f));
		

		glm::vec4 pos((_position.x), (_position.y), _texture->Width * _scale, _texture->Height * _scale);
		glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

		spriteBatch.Draw(pos, uv, _texture->ID, 0.0f, _color);
	}

	Drawable::Drawable()
	{

	}

	glm::vec2 Drawable::GetOrigin() const
	{
		return glm::vec2((_texture->Width / 2) * _scale, (_texture->Height / 2) * _scale);
	}

}