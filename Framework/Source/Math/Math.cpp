#include "../../Headers/Math/Math.h"
using namespace lun;

template class Math<f32>;
template class Math<f64>;

template<class T> T Math<T>::fraction(T value) { return value - floor(value); }
template<class T> T Math<T>::floor(T value) { return (T)((i64)value); }
template<class T> T Math<T>::mod(T a, T b) { return fraction(a / b) * b; }
template<class T> T Math<T>::absf(T value) { return value < 0 ? -value : value; }
template<class T> T Math<T>::max(T value1, T value2) { return value1 < value2 ? value2 : value1; }
template<class T> T Math<T>::ceil(T value) { return floor(value) == value ? value : floor(value) + (value < 0 ? -1 : 1) * 1; }
template<class T> T Math<T>::min(T value1, T value2) { return value1 > value2 ? value2 : value1; }
template<class T> T Math<T>::clamp(T value, T min, T max) { return value > max ? max : (value < min ? min : value); }
template<class T> bool Math<T>::base2(T value) { return fraction((T)(log(value) / log(2))) == 0; }
template<class T> T Math<T>::deg2rad(T degrees) { return degrees * M_PI / 180; }
template<class T> T Math<T>::rad2deg(T radians) { return radians / M_PI * 180; }
template<class T> T Math<T>::sqrt(T value) { return (T)std::sqrt(value); }