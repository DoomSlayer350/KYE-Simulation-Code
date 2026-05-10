// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_quickstep_cpp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KYE_SIM_PROTOTYPE_2_API UAC_quickstep_cpp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_quickstep_cpp();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* Owner = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAnimInstance* ins_anim = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* forward_QuickstepMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* backward_QuickstepMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* right_QuickstepMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* left_QuickstepMontage;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Quickstep(FVector direction);
		
};
