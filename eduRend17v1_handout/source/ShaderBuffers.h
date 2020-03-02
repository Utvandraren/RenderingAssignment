
#pragma once
#ifndef MATRIXBUFFERS_H
#define MATRIXBUFFERS_H

#include "vec\vec.h"
#include "vec\mat.h"

using namespace linalg;

struct MatrixBuffer_t
{
	mat4f ModelToWorldMatrix;
	mat4f WorldToViewMatrix;
	mat4f ProjectionMatrix;
};

struct PhongBuffer_t
{
	vec4f ambColor;
	vec4f diffColor;
	vec4f specColor;
};

struct LightCamBuffer_t 
{
	vec4f lightPos;
	vec4f camerPos;

	
};

struct CubeMapBuffer_t
{
	int isCubeMap;
	float3 dummy;
};


#endif