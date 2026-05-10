// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDS_attack.generated.h"

UENUM(BlueprintType)
enum class E_damage_type : uint8
{
	none UMETA(DisplayName = "none"),
	melee_blunt UMETA(DisplayName = "melee_blunt"),
	melee_sharp UMETA(DisplayName = "melee_sharp"),
	projectile UMETA(DisplayName = "projectile")

};

UENUM(BlueprintType)
enum class E_damage_response : uint8
{
	none UMETA(DisplayName = "none"),
	hitreaction UMETA(DisplayName = "hitreaction")

};

USTRUCT(BlueprintType)
struct Fdamage_store
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* damager = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damage_amount = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_damage_type damage_type = E_damage_type::none;

};

USTRUCT(BlueprintType)
struct FS_damage_info
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damage_amount = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_damage_type damage_type = E_damage_type::none;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_damage_response damage_response = E_damage_response::none;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool should_force_interrupt = false;

};

/**
 * 
 */
UCLASS()
class KYE_SIM_PROTOTYPE_2_API UPDS_attack : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attack_data")
	TMap<FName, UAnimMontage*> possible_chain_attacks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* attack_anim_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attack_data")
	float player_movement_speed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attack_data")
	float enemy_movement_speed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attack_data")
	FS_damage_info damage_info;

};

	