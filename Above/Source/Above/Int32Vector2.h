// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Above.h"

/**
*
*/
struct Int32Vector2 {
public:
	int32 x;
	int32 y;

	// More constructors
	Int32Vector2::Int32Vector2() {
	}

	Int32Vector2::Int32Vector2(int32 value)
		: x(value), y(value) {

	}

	Int32Vector2::Int32Vector2(int32 valX, int32 valY)
		: x(valX), y(valY) {

	}
};