// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Above.h"

struct TriFVector {
public:
	FVector x, y, z = FVector(0, 0 ,0);

	TriFVector::TriFVector() {

	}

	TriFVector::TriFVector(FVector value)
		: x(value), y(value), z(value){

	}

	TriFVector::TriFVector(FVector valueX, FVector valueY, FVector valueZ)
		: x(valueX), y(valueY), z(valueZ) {

	}
};
