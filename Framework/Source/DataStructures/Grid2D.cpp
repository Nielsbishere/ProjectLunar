#include "../../Headers/DataStructures/Grid2D.h"
using namespace lun;

Grid2D::Grid2D(u32 _width, u32 _height, f32(*func)(f32, f32)) {
	width = _width;
	height = _height;
	arr = new f32[3 * width * height];

	for (u32 i = 0; i < width*height; ++i)
		arr[i] = get(func, (f32)(i % width), (f32)(i / width));

	for (u32 l = 0; l < width * height; ++l) {
		u32 i = l % width;
		u32 j = l / width;


		f32 d = 1.f;

		vec2 delta;
		delta.x = get(func, i + d, j) - get(func, i - d, j);
		delta.y = get(func, i, j + d) - get(func, i, j - d);

		*(vec2*)(&arr[width * height + 2 * l]) = delta.normalize();
	}
}

Grid2D::Grid2D(const Grid2D &g) {
	arr = new f32[3 * (width = g.width) * (height = g.height)];
	for (u32 i = 0; i < 3 * width* height; ++i)
		arr[i] = g.arr[i];
}

Grid2D::~Grid2D() {
	delete[] arr;
}

f32 Grid2D::get(u32 i, u32 j) {
	if (i >= width || j >= height)
		return 0;

	return arr[j * width + i];
}

vec2 Grid2D::getDelta(u32 i, u32 j) {
	if (i >= width || j >= height)
		return vec2();

	return *(vec2*)&arr[height * width + 2 * (j * width + i)];
}

void Grid2D::normalize() {
	f32 mi = f32_MAX, ma = f32_MIN;

	for (u32 i = 0; i < width*height; ++i) {
		if (arr[i] < mi)
			mi = arr[i];
		if (arr[i] > ma)
			ma = arr[i];
	}

	for (u32 i = 0; i < width*height; ++i) {
		arr[i] = (arr[i] - mi) / (ma - mi);
	}
}

void Grid2D::print() {
	for (u32 j = 0; j < height; ++j) {
		for (u32 i = 0; i < width; ++i)
			printf("%f\t", get(i, j));
		printf("\n");
	}

}

u32 Grid2D::getWidth() { return width; }
u32 Grid2D::getHeight() { return height; }
u32 Grid2D::getPoints() { return width * height; }

f32 Grid2D::get(f32(*func)(f32, f32), f32 x, f32 y) {
	return func(x / width, y / height);
}