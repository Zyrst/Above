// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "ConstValues.h"

ConstValues::ConstValues()
{
	mStandardFov = StandardFoV;
	
}

ConstValues::~ConstValues()
{
}

int32 ConstValues::getStandardFov(){
	return mStandardFov;
}