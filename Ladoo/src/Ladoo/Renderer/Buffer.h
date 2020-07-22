#pragma once

namespace Ladoo {

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case Ladoo::ShaderDataType::None:
			LD_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		case Ladoo::ShaderDataType::Float:
			return 4;
		case Ladoo::ShaderDataType::Float2:
			return 4 * 2;
		case Ladoo::ShaderDataType::Float3:
			return 4 * 3;
		case Ladoo::ShaderDataType::Float4:
			return 4 * 4;
		case Ladoo::ShaderDataType::Mat3:
			return 4 * 3 * 3;
		case Ladoo::ShaderDataType::Mat4:
			return 4 * 4 * 4;
		case Ladoo::ShaderDataType::Int:
			return 4;
		case Ladoo::ShaderDataType::Int2:
			return 4 * 2;
		case Ladoo::ShaderDataType::Int3:
			return 4 * 3;
		case Ladoo::ShaderDataType::Int4:
			return 4 * 4;
		case Ladoo::ShaderDataType::Bool:
			return 1;
		}

		LD_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElements
	{
		ShaderDataType Type;
		std::string Name;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized;

		BufferElements() {}

		BufferElements(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case Ladoo::ShaderDataType::None:
				LD_CORE_ASSERT(false, "Unknown ShaderDataType!");
				return 0;
			case Ladoo::ShaderDataType::Float:
				return 1;
			case Ladoo::ShaderDataType::Float2:
				return 2;
			case Ladoo::ShaderDataType::Float3:
				return 3;
			case Ladoo::ShaderDataType::Float4:
				return 4;
			case Ladoo::ShaderDataType::Mat3:
				return 3 * 3;
			case Ladoo::ShaderDataType::Mat4:
				return 4 * 4;
			case Ladoo::ShaderDataType::Int:
				return 1;
			case Ladoo::ShaderDataType::Int2:
				return 2;
			case Ladoo::ShaderDataType::Int3:
				return 3;
			case Ladoo::ShaderDataType::Int4:
				return 4;
			case Ladoo::ShaderDataType::Bool:
				return 1;
			}

			LD_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElements>& element) 
			: elements(element) 
		{
			CalculateOffsetAndStride();
		}

		inline const std::vector<BufferElements>& GetElements() const { return elements; }
		inline uint32_t GetStride() const { return stride; }

		std::vector<BufferElements>::iterator begin() { return elements.begin(); }
		std::vector<BufferElements>::iterator end() { return elements.end(); }
		std::vector<BufferElements>::const_iterator begin() const { return elements.begin(); }
		std::vector<BufferElements>::const_iterator end() const { return elements.end(); }
	private:
		void CalculateOffsetAndStride()
		{
			uint32_t offset = 0;
			stride = 0;
			for (auto& element : elements)
			{
				element.Offset = offset;
				offset += element.Size;
				stride += element.Size;
			}
		}

		std::vector<BufferElements> elements;
		uint32_t stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};

}