#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Ladoo {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		//virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
		//virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& values) = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

}