// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Above.h"

struct DuoFVector {
public:
	FVector x, y = FVector(0, 0, 0);

	DuoFVector::DuoFVector() {

	}

	DuoFVector::DuoFVector(FVector value)
		: x(value), y(value) {

	}

	DuoFVector::DuoFVector(FVector valueX, FVector valueY)
		: x(valueX), y(valueY) {

	}
};
