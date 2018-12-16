#pragma once

typedef signed __int8 i8;
typedef unsigned __int8 u8;

typedef signed __int16 i16;
typedef unsigned __int16 u16;

typedef signed __int32 i32;
typedef unsigned __int32 u32;

typedef signed __int64 i64;
typedef unsigned __int64 u64;

typedef float f32;
typedef double f64;

typedef f32 vec4f32[4];
typedef f64 vec4f64[4];
typedef f32 vec3f32[3];
typedef f64 vec3f64[3];
typedef f32 vec2f32[2];
typedef f64 vec2f64[2];

#define u8_MAX (u8)0xFF
#define u8_MIN (u8)0
#define i8_MAX (i8)0x7F
#define i8_MIN (i8)0x80

#define u16_MAX (u16)0xFFFF
#define u16_MIN (u16)0
#define i16_MAX (i16)0x7FFF
#define i16_MIN (i16)0x8000

#define u32_MAX (u32)0xFFFFFFFF
#define u32_MIN (u32)0
#define i32_MAX (i32)0x7FFFFFFF
#define i32_MIN (i32)0x80000000

#define u64_MAX (u64)0xFFFFFFFFFFFFFFFF
#define u64_MIN (u64)0
#define i64_MAX (i64)0x7FFFFFFFFFFFFFFF
#define i64_MIN (i64)0x8000000000000000

struct MaxVal {
	static f32 __f32_MAX() {
		u32 max = 0x7F7FFFFF;
		return *(f32*)&max;
	}
	static f64 __f64_MAX() {
		u64 max = 0x7FEFFFFFFFFFFFFF;
		return *(f64*)&max;
	}
};
#define f32_MAX MaxVal::__f32_MAX()
#define f32_MIN -f32_MAX
#define f64_MAX MaxVal::__f64_MAX()
#define f64_MIN -f64_MAX