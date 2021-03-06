#include "ldpch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>

namespace Ladoo {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		LD_CORE_ASSERT(data, "Failed tp load image!");
		m_Width = width;
		m_Height = height;

		GLenum openglFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			openglFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			openglFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_OpenGLFormat = openglFormat;
		m_DataFormat = dataFormat;

		LD_CORE_ASSERT(openglFormat & dataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, openglFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{
		m_OpenGLFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_OpenGLFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}
	
	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bytes_per_pixel = m_DataFormat == GL_RGBA ? 4 : 3;
		LD_CORE_ASSERT(size == m_Width * m_Height * bytes_per_pixel, "Data must be entire texture");

		//glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}
}