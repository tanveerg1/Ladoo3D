#pragma once

#include "RendererAPI.h"

namespace Ladoo {

	class RendererCommand
	{
	public:
		inline static void SetClearColour(const glm::vec4& colour)
		{
			s_RendererAPI->SetClearColour(colour);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawElements(const Ref<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawElements(vertexArray);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}