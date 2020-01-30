
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
	vec4f Color;
};

struct LightBuffer_t 
{
	mat4f WorldToVieWMatrix;
};


#endif