// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/ADAnimInstance.h"

UADAnimInstance::UADAnimInstance()
{
	curSpeed_ = 0.0f;
}

void UADAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();

	if (::IsValid(Pawn))
	{
		curSpeed_ = Pawn->GetVelocity().Size();
		//ABLOG(Warning, TEXT("%f"), curSpeed_);
	}
}