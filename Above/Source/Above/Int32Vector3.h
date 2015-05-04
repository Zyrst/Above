// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Above.h"

/**
*
*/
struct Int32Vector3 {
public:
	int32 x;
	int32 y;
	int32 z;

	// More constructors
	Int32Vector3::Int32Vector3() {
	}

	Int32Vector3::Int32Vector3(int32 value)
		: x(value), y(value), z(value)
	{

	}

	Int32Vector3::Int32Vector3(int32 valX, int32 valY, int32 valZ)
		: x(valX), y(valY), z(valZ)
	{

	}
};