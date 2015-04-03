// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class ABOVE_API ConstValues
{
public:
	ConstValues();
	~ConstValues();

	int32 getStandardFov();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Utility)
		int32 StandardFoV;
private:
	int32 mStandardFov;

};
