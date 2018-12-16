#pragma once

/*
Relative Pointer
Relative pointers are used as a way to remove position dependency.
When using relative pointers in and on a big chunk of data, that data can be moved around and not be disturbed by the change in memory position.

Use the relative pointer like a normal pointer.
*/

namespace lun
{
	template<typename T, typename PtrSize = signed int>
	class RelPtr
	{
	public:
		RelPtr() 
		{
			relativePosition = 0;
		}

		RelPtr(T *absolutePtr)
		{
			operator=(absolutePtr);
		}

		inline T *operator->()
		{
			return (T*)((char*)this + relativePosition);
		}

		inline T &operator*()
		{
			return *(T*)((char*)this + relativePosition);
		}

		inline RelPtr<T> &operator=(T *absolutePtr)
		{
			relativePosition = (char*)absolutePtr - (char*)this;
			return *this;
		}

		inline void operator+=(signed int add)
		{
			relativePosition += sizeof(T) * add;
		}

		inline void operator++()
		{
			relativePosition += sizeof(T);
		}
		inline void operator++(PtrSize offset)
		{
			relativePosition += sizeof(T);// *offset;
		}

		inline bool operator==(T *absolutePtr)
		{
			return operator->() == absolutePtr;
		}

		inline bool operator!=(T *absolutePtr)
		{
			return !operator==(absolutePtr);
		}

	private:
		PtrSize relativePosition;
	};
}