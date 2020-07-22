#include "ldpch.h"
#include "RendererCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Ladoo {

	RendererAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI;
}