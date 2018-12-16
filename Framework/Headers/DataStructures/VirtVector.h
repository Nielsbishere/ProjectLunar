#pragma once
#include <type_traits>
#include <memory>
#include <cstring>
#include <assert.h>

namespace lun
{
	template<typename BaseClass>
	class VirtVector
	{
	private:
		//class cannot be create without child type
		VirtVector(unsigned int _elementSize, unsigned int totalSize, size_t type)
		{
			elementSize = _elementSize;
			vectorData = (char*)malloc(totalSize * _elementSize);
			_size = totalSize * _elementSize;
			top = 0;
			childType = type;
		}

	public:
		//empty constructor, DO NOT USE!
		VirtVector() {}
		~VirtVector()
		{
			free(vectorData);
		}

		//copy
		VirtVector(const VirtVector<BaseClass> &other)
		{
			assert(childType != other.childType);
			vectorData = (char*)malloc(other._size);
			memcpy(vectorData, other.vectorData, other._size);
			top = other.top;
			_size = other._size;
			elementSize = other.elementSize;
		}
		VirtVector<BaseClass> &operator=(const VirtVector<BaseClass> &other)
		{
			assert(childType != other.childType);
			vectorData = (char*)malloc(other._size);
			memcpy(vectorData, other.vectorData, other._size);
			top = other.top;
			_size = other._size;
			elementSize = other.elementSize;
			return *this;
		}

		BaseClass &operator[](unsigned int index)
		{
			return reinterpret_cast<BaseClass&>(vectorData[index*elementSize]);
		}

		inline unsigned int size()
		{
			return top;
		}

		//pushes element onto 
		template<typename T>
		unsigned int push_back(T newElement)
		{
			assert(typeid(T).hash_code() == childType);
			//grow vector if too small
			if ((top + 1) * elementSize == _size)
			{
				doubleSize(2);
			}
			::new(vectorData + top*elementSize) T(newElement);
			top++;
			return top - 1;
		}

	public: //static
			//create vector on heap
		template<typename T>
		static VirtVector<BaseClass> *createHeap()
		{
			static_assert(std::is_base_of<BaseClass, T>::value, "T is not child of base class");
			return new VirtVector<BaseClass>(sizeof(T), 4, typeid(T).hash_code());
		}

		//create vector on stack
		template<typename T>
		static VirtVector<BaseClass> create()
		{
			static_assert(std::is_base_of<BaseClass, T>::value, "T is not child of base class");
			return VirtVector<BaseClass>(sizeof(T), 4, typeid(T).hash_code());
		}

	private: //vars
		char *vectorData;
		unsigned int _size;
		unsigned int top;
		unsigned int elementSize;
		//child type hash
		size_t childType;

	private: //funcs
		void doubleSize(unsigned int multiplier)
		{
			unsigned int newSize = _size * multiplier;
			char *newVectorData = (char*)malloc(newSize);
			memcpy(newVectorData, vectorData, _size);
			free(vectorData);
			vectorData = newVectorData;
			_size = newSize;
		}
	};
}