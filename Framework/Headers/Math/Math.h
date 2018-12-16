#pragma once
#ifndef M_PI
#define M_PI 3.1415926535f
#endif

#include "../Type/OTypes.h"
#include <cmath>

namespace lun {
	//Class for handling math (wow surprising)
	//@template T, which data type is used for calculations (f32 or f64)
	template<class T> class Math {
	public:
		//Get the fraction of a floating point number; fraction(50.5) will return .5 while (50.3f) will return .3f
		//@param T value
		//@return T fraction
		static T fraction(T value);

		//Floor (get integer value of flpoint)
		//@param T value
		//@return T int
		static T floor(T value);

		//Square root
		//@param T value
		//@return T result
		static T sqrt(T value);

		//Get the remainder of a successful division 
		//@param T a
		//@param T b
		//@return T remainder (fraction(a / b) * b)
		static T mod(T a, T b);

		//Get the absolute value of a floating point; absf(-5.f) returns 5.f and absf(50.0) returns 50.0
		//@param T value
		//@return T absolute value (unsigned version)
		static T absf(T value);

		//Get the maximum of two numbers
		//@param T value1
		//@param T value2
		//@return value1 > value2 ? value1 : value2
		static T max(T value1, T value2);

		//Get the rounded up version of a division (5.000000....1 rounds up to 6 while 5 remains 5; -5.0001 rounds down to -6)
		//@param T value
		//@return T fraction
		static T ceil(T value);

		//Get the minimum of two numbers
		//@param T value1
		//@param T value2
		//@return T fraction
		static T min(T value1, T value2);

		//Clamp the value between a range of numbers
		//@param T value
		//@param T min
		//@param T max
		//@return T clamped value
		static T clamp(T value, T min, T max);

		//Checks if the number is a base2 number (..., 0.125, 0.25, 0.5, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32728, 65536, etc.)
		//@param T value
		//@return T fraction
		static bool base2(T value);

		//Convert angle in degrees to angle in radians
		//@param T degrees
		//@return T radians
		static T deg2rad(T degrees);

		//Convert angle in radians to angle in degrees
		//@param T radians
		//@return T degrees
		static T rad2deg(T radians);
	};
}