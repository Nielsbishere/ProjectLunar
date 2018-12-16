#include "../../Headers/Math/WorleyNoise.h"
#include "../../Headers/Math/Math.h"
using namespace lun;

f32 WorleyNoise::K = 1.f / 7;
f32 WorleyNoise::Ko = 1.f / 2 - K / 2;
f32 WorleyNoise::K2 = 1.f / (7 * 7);
f32 WorleyNoise::Kz = 1.f / 6;
f32 WorleyNoise::Kzo = 1.f / 2 - 1.f / 6 * 2;

vec3 WorleyNoise::permute(vec3 x) {
	return (x * 34 + 1) * x % 289;
}

vec2 WorleyNoise::worley(vec3 P, f32 jitter) {
	jitter = Math<f32>::clamp(jitter, 0, 1);
	vec3 Pi = P.floor() % 289;
	vec3 Pf = P.fract() - 0.5;

	vec3 Pfx = vec3(1, 0, -1) + Pf.x;
	vec3 Pfy = vec3(1, 0, -1) + Pf.y;
	vec3 Pfz = vec3(1, 0, -1) + Pf.z;

	vec3 p = permute(vec3(-1, 0, 1) + Pi.x);
	vec3 p1 = permute(p + Pi.y - 1);
	vec3 p2 = permute(p + Pi.y);
	vec3 p3 = permute(p + Pi.y + 1);

	vec3 p11 = permute(p1 + Pi.z - 1);
	vec3 p12 = permute(p1 + Pi.z);
	vec3 p13 = permute(p1 + Pi.z + 1);

	vec3 p21 = permute(p2 + Pi.z - 1);
	vec3 p22 = permute(p2 + Pi.z);
	vec3 p23 = permute(p2 + Pi.z + 1);

	vec3 p31 = permute(p3 + Pi.z - 1);
	vec3 p32 = permute(p3 + Pi.z);
	vec3 p33 = permute(p3 + Pi.z + 1);

	vec3 ox11 = (p11 * K).fract() - Ko;
	vec3 oy11 = (p11 * K).floor().mod(7) * K - Ko;
	vec3 oz11 = (p11 * K2).floor() * Kz - Kzo; // p11 < 289 guaranteed

	vec3 ox12 = (p12 * K).fract() - Ko;
	vec3 oy12 = ((p12 * K).floor()).mod(7) * K - Ko;
	vec3 oz12 = (p12 * K2).floor() * Kz - Kzo;

	vec3 ox13 = (p13 * K).fract() - Ko;
	vec3 oy13 = ((p13 * K).floor()).mod(7) * K - Ko;
	vec3 oz13 = (p13 * K2).floor() * Kz - Kzo;

	vec3 ox21 = (p21 * K).fract() - Ko;
	vec3 oy21 = ((p21 * K).floor()).mod(7) * K - Ko;
	vec3 oz21 = (p21 * K2).floor() * Kz - Kzo;

	vec3 ox22 = (p22 * K).fract() - Ko;
	vec3 oy22 = ((p22 * K).floor()).mod(7) * K - Ko;
	vec3 oz22 = (p22 * K2).floor() * Kz - Kzo;

	vec3 ox23 = (p23 * K).fract() - Ko;
	vec3 oy23 = ((p23 * K).floor()).mod(7) * K - Ko;
	vec3 oz23 = (p23 * K2).floor() * Kz - Kzo;

	vec3 ox31 = (p31 * K).fract() - Ko;
	vec3 oy31 = ((p31 * K).floor()).mod(7) * K - Ko;
	vec3 oz31 = (p31 * K2).floor() * Kz - Kzo;

	vec3 ox32 = (p32 * K).fract() - Ko;
	vec3 oy32 = ((p32 * K).floor()).mod(7) * K - Ko;
	vec3 oz32 = (p32 * K2).floor() * Kz - Kzo;

	vec3 ox33 = (p33 * K).fract() - Ko;
	vec3 oy33 = ((p33 * K).floor()).mod(7) * K - Ko;
	vec3 oz33 = (p33 * K2).floor() * Kz - Kzo;

	vec3 dx11 = ox11* jitter + Pfx;
	vec3 dy11 = oy11* jitter + Pfy.x;
	vec3 dz11 = oz11* jitter + Pfz.x;

	vec3 dx12 = ox12* jitter + Pfx;
	vec3 dy12 = oy12* jitter + Pfy.x;
	vec3 dz12 = oz12* jitter + Pfz.y;

	vec3 dx13 = ox13* jitter + Pfx;
	vec3 dy13 = oy13* jitter + Pfy.x;
	vec3 dz13 = oz13* jitter + Pfz.y;

	vec3 dx21 = ox21* jitter + Pfx;
	vec3 dy21 = oy21* jitter + Pfy.y;
	vec3 dz21 = oz21* jitter + Pfz.x;

	vec3 dx22 = ox22* jitter + Pfx;
	vec3 dy22 = oy22* jitter + Pfy.y;
	vec3 dz22 = oz22* jitter + Pfz.y;

	vec3 dx23 = ox23* jitter + Pfx;
	vec3 dy23 = oy23* jitter + Pfy.y;
	vec3 dz23 = oz23* jitter + Pfz.z;

	vec3 dx31 = ox31* jitter + Pfx;
	vec3 dy31 = oy31* jitter + Pfy.z;
	vec3 dz31 = oz31* jitter + Pfz.x;

	vec3 dx32 = ox32* jitter + Pfx;
	vec3 dy32 = oy32* jitter + Pfy.z;
	vec3 dz32 = oz32* jitter + Pfz.y;

	vec3 dx33 = ox33* jitter + Pfx;
	vec3 dy33 = oy33* jitter + Pfy.z;
	vec3 dz33 = oz33* jitter + Pfz.z;

	vec3 d11 = dx11 * dx11 + dy11 * dy11 + dz11 * dz11;
	vec3 d12 = dx12 * dx12 + dy12 * dy12 + dz12 * dz12;
	vec3 d13 = dx13 * dx13 + dy13 * dy13 + dz13 * dz13;
	vec3 d21 = dx21 * dx21 + dy21 * dy21 + dz21 * dz21;
	vec3 d22 = dx22 * dx22 + dy22 * dy22 + dz22 * dz22;
	vec3 d23 = dx23 * dx23 + dy23 * dy23 + dz23 * dz23;
	vec3 d31 = dx31 * dx31 + dy31 * dy31 + dz31 * dz31;
	vec3 d32 = dx32 * dx32 + dy32 * dy32 + dz32 * dz32;
	vec3 d33 = dx33 * dx33 + dy33 * dy33 + dz33 * dz33;


	// Do it right and sort out both F1 and F2
	vec3 d1a = vec3::min(d11, d12);
	d12 = vec3::max(d11, d12);
	d11 = vec3::min(d1a, d13); // Smallest now not in d12 or d13
	d13 = vec3::max(d1a, d13);
	d12 = vec3::min(d12, d13); // 2nd smallest now not in d13
	vec3 d2a = vec3::min(d21, d22);
	d22 = vec3::max(d21, d22);
	d21 = vec3::min(d2a, d23); // Smallest now not in d22 or d23
	d23 = vec3::max(d2a, d23);
	d22 = vec3::min(d22, d23); // 2nd smallest now not in d23
	vec3 d3a = vec3::min(d31, d32);
	d32 = vec3::max(d31, d32);
	d31 = vec3::min(d3a, d33); // Smallest now not in d32 or d33
	d33 = vec3::max(d3a, d33);
	d32 = vec3::min(d32, d33); // 2nd smallest now not in d33
	vec3 da = vec3::min(d11, d21);
	d21 = vec3::max(d11, d21);
	d11 = vec3::min(da, d31); // Smallest now in d11
	d31 = vec3::max(da, d31); // 2nd smallest now not in d31
	d11.xy((d11.x < d11.y) ? d11.xy() : d11.yx());
	d11.xz((d11.x < d11.z) ? d11.xz() : d11.zx()); // d11.x now smallest
	d12 = vec3::min(d12, d21); // 2nd smallest now not in d21
	d12 = vec3::min(d12, d22); // nor in d22
	d12 = vec3::min(d12, d31); // nor in d31
	d12 = vec3::min(d12, d32); // nor in d32
	d11.yz(vec2::min(d11.yz(), d12.xy())); // nor in d12.yz
	d11.y = Math<f32>::min(d11.y, d12.z); // Only two more to go
	d11.y = Math<f32>::min(d11.y, d11.z); // Done! (Phew!)
	return d11.xy().sqrt(); // F1, F2
}

f32 WorleyNoise::worley3D(vec3 P, f32 jitter) {
	vec2 v = worley(P, jitter);
	return v.y - v.x;
}

f32 WorleyNoise::cellularNoise3D(vec3 P, f32 jitter) {
	vec2 v = worley(P, jitter);
	return v.x;
}

f32 WorleyNoise::worley2D(vec2 P, f32 jitter) {
	vec2 v = worley(vec3(P, 0), jitter);
	return v.y - v.x;
}

f32 WorleyNoise::cellularNoise2D(vec2 P, f32 jitter) {
	vec2 v = worley(vec3(P, 0), jitter);
	return v.x;
}

f32 WorleyNoise::worley1D(f32 P, f32 jitter) {
	vec2 v = worley(vec3(P, 0, 0), jitter);
	return v.y - v.x;
}

f32 WorleyNoise::cellularNoise1D(f32 P, f32 jitter) {
	vec2 v = worley(vec3(P, 0, 0), jitter);
	return v.x;
}
