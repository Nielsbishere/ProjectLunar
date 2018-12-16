#pragma once
#include "../../Type/OTypes.h"
namespace lun {

	struct TPointLight {

		vec4 colPow;
		vec4 posRadius;

		TPointLight(vec4 pr, vec4 cp) : posRadius(pr), colPow(cp) {}

		TPointLight(): TPointLight(vec4(), vec4()){}
	};

	struct TDirectionalLight {

		vec4 colPow;
		vec4 dir;

		TDirectionalLight(vec3 d, vec4 cp): dir(vec4(d, 0)), colPow(cp){}

		TDirectionalLight() : TDirectionalLight(vec3(), vec4()) {}
	};

	struct TSpotLight {

		vec4 colPow;
		vec4 posHeight;
		vec4 dirRadius;

		TSpotLight(vec4 ph, vec4 dr, vec4 cp): posHeight(ph), dirRadius(dr), colPow(cp){}

		TSpotLight() : TSpotLight(vec4(), vec4(), vec4()) {}
	};
};