#pragma once
#include "../Type/OTypes.h"
namespace lun {
	class Grid2D {

	public:

		Grid2D(u32 _width, u32 _height, f32(*func)(f32, f32));
		Grid2D(const Grid2D &g);
		~Grid2D();

		f32 get(u32 i, u32 j);
		vec2 getDelta(u32 i, u32 j);

		void print();

		u32 getWidth();
		u32 getHeight();
		u32 getPoints();

		void normalize();

	protected:

		f32 get(f32(*func)(f32, f32), f32 x, f32 y);

	private:

		u32 width, height;
		f32 *arr;
	};
}