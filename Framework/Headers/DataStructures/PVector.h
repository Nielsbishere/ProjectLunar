#pragma once
#include <memory>//malloc
#include <cstring>//memcpy

namespace lun
{
	template<typename T>
	class PVector
	{
	public:
		PVector()
		{
			_size = 4;
			dataPile = malloc(_size * sizeof(T));
			top = 0;
		}
		PVector(unsigned int size)
		{
			_size = size;
			dataPile = malloc(_size * sizeof(T));
			top = 0;
		}
		~PVector()
		{
			free(dataPile);
		}
		PVector(const PVector<T> &other)
		{
			_size = other._size;
			dataPile = malloc(_size * sizeof(T));
			memcpy(dataPile, other.dataPile, _size * sizeof(T));
			top = other.top;
		}

		PVector<T> &operator=(const PVector<T> &other)
		{
			_size = other._size;
			dataPile = malloc(_size * sizeof(T));
			memcpy(dataPile, other.dataPile, _size * sizeof(T));
			top = other.top;
			return *this;
		}

		T &operator[](unsigned int index)
		{
			return dataPile[index];
		}
		
		//push an element onto the vector
		void push_back(const T &newElenemt)
		{
			//if vector is too small, allocate new memory for the vector
			if (top == _size)
			{
				T *newData = malloc(_size * 2 * sizeof(T));
				memcpy(newData, dataPile, _size * sizeof(T));
				free(dataPile);
				_size *= 2;
				dataPile = newData;
			}

			dataPile[top] = newElenemt;
			top++;
		}

		//copy the data of another vector (up until the top)
		void transfer(const PVector<T> &other)
		{
			if (_size > other.top)
			{
				//fast cpy
				memcpy(dataPile, other.dataPile, other.top * sizeof(T));
				top = other.top;
				return;
			}
			//else, do a full copy
			_size = other._size;
			dataPile = malloc(_size * sizeof(T));
			memcpy(dataPile, other.dataPile, _size * sizeof(T));
			top = other.top;
		}

		//clear all the elements in the vector (does not call destructor)
		void clear()
		{
			top = 0;
		}

		//THESE MIGHT CHANGE
		T *begin() { return dataPile; }
		T *end() { return dataPile + _size; }

		//get current size of the vector
		unsigned int size() { return top; }

		//get the current maximum size of the vector
		unsigned int maxSize() { return _size; }
	private:
		unsigned int _size;
		unsigned int top;
		T *dataPile;
	};
}