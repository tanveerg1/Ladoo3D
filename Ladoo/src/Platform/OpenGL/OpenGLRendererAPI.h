#pragma once

#include "Ladoo/Renderer/RendererAPI.h"

namespace Ladoo {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColour(const glm::vec4& colour) override;
		virtual void Clear() override;

		virtual void DrawElements(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}

