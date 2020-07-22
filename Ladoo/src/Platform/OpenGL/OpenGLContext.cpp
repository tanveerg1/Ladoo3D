#include "ldpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Ladoo {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandler) 
		: m_WindowHandler(windowHandler)
	{
		LD_CORE_ASSERT(windowHandler, "Handler is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandler);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LD_CORE_ASSERT(status, "Failed to initialize glad");

		LD_CORE_INFO("OpenGL Info:");
		LD_CORE_INFO(" Vendor: {0}", glGetString(GL_VENDOR));
		LD_CORE_INFO(" Renderer: {0}", glGetString(GL_RENDERER));
		LD_CORE_INFO(" Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandler);
	}
}