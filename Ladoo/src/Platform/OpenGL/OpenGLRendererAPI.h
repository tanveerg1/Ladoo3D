#pragma once

#include "Ladoo/Renderer/RendererAPI.h"

namespace Ladoo {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void SetClearColour(const glm::vec4& colour) override;
		virtual void Clear() override;

		virtual void DrawElements(const Ref<VertexArray>& vertexArray) override;
	};
}


