#pragma once

#include "Ladoo/Renderer/Shader.h"

namespace Ladoo {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
	private:
		uint32_t m_RendererID;
	};
}


