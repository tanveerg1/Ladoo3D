#pragma once

namespace Ladoo {

	class RendererContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Scope<RendererContext> Create(void* window);
	};
}