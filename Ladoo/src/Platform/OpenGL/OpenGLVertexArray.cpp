#include "ldpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Ladoo {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Ladoo::ShaderDataType::Float:
				return GL_FLOAT;
			case Ladoo::ShaderDataType::Float2:
				return GL_FLOAT;
			case Ladoo::ShaderDataType::Float3:
				return GL_FLOAT;
			case Ladoo::ShaderDataType::Float4:
				return GL_FLOAT;
			case Ladoo::ShaderDataType::Mat3:
				return GL_FLOAT;
			case Ladoo::ShaderDataType::Mat4:
				return GL_FLOAT;
			case Ladoo::ShaderDataType::Int:
				return GL_INT;
			case Ladoo::ShaderDataType::Int2:
				return GL_INT;
			case Ladoo::ShaderDataType::Int3:
				return GL_INT;
			case Ladoo::ShaderDataType::Int4:
				return GL_INT;
			case Ladoo::ShaderDataType::Bool:
				return GL_BOOL;
			}

		LD_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ladoo::Ref<VertexBuffer>& vertexBuffer)
	{
		LD_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)(intptr_t)element.Offset);
			index++;
		}
		
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::AddIndexBuffer(const Ladoo::Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}
