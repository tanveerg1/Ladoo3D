#pragma once

#include "Ladoo/Renderer/RendererContext.h"

struct GLFWwindow;

namespace Ladoo {

	class OpenGLContext : public RendererContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandler);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandler;
	};
}