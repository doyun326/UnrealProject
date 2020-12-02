// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAnimInstance.h"

UWeaponAnimInstance::UWeaponAnimInstance()
{

}

void UWeaponAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto actor = TryGetPawnOwner();

	if (::IsValid(actor))
	{
		ABLOG(Warning, TEXT("OK"));
	}
	else
	{
		ABLOG(Warning, TEXT("false"));
	}

	
}