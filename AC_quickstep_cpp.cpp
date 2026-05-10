// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_quickstep_cpp.h"

// Sets default values for this component's properties
UAC_quickstep_cpp::UAC_quickstep_cpp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UAC_quickstep_cpp::BeginPlay()
{
	Super::BeginPlay();

	Owner = this->GetOwner();

	if (IsValid(Owner))
	{
		ins_anim = Owner->FindComponentByClass<USkeletalMeshComponent>()->GetAnimInstance();
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, (Owner->GetName()));

	// ...
	
}


// Called every frame
void UAC_quickstep_cpp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_quickstep_cpp::Quickstep(FVector direction)
{
	if (IsValid(ins_anim))
	{

		FVector vec_direction = (direction) / (direction.Length());
		FVector ForwardVector = Owner->GetActorForwardVector();
		FVector RightVector = Owner->GetActorRightVector();
		float y = FVector::DotProduct(ForwardVector, vec_direction);
		float x = FVector::DotProduct(RightVector, vec_direction);
		FVector relative_direction = FVector(x, y, 0);

		double forward_angle = atan2(ForwardVector.Y, ForwardVector.X);
		double relative_angle = atan2(y, x); // when forward angle is close to 360 and relative angle is close to 0, the angle difference will be close to 360 instead of close to 0, so we need to fix that
		double angle_diff = 0;
		double closeness = FVector::DotProduct(ForwardVector, relative_direction); // How close the relative direction is to the forward vector
		closeness = FMath::Clamp(closeness, -1.0f, 1.0f); // Clamp the value to be between -1 and 1 to avoid NaN values from acos
		double det = ForwardVector.X * relative_direction.Y - ForwardVector.Y * relative_direction.X; // determinant of the 2 vectors, used to determine the sine of the angle difference
		angle_diff = atan2(det, closeness); // atan2 of the cross product size and the dot product
		double cap_angle; //The global angle the capsule of the player will face in the z rotation plane.

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::SanitizeFloat(relative_angle));

		if(relative_angle < 0)
		{
			cap_angle = relative_angle + (2 * PI);
		}
		else
		{
			cap_angle = relative_angle;
		} //This is to make sure cap_angle is between 0 and 2PI radians.

		cap_angle = FMath::RadiansToDegrees(cap_angle); // Convert the angle to degrees for the character rotation
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::SanitizeFloat(cap_angle));


		if (((-PI) / 3 <=  angle_diff && angle_diff <= (PI)/3)) //Forward Quickstep (300 to 60 degrees)
		{
			//cap_angle shall remain the same as its forward
			Owner->SetActorRotation(FRotator3d(0, cap_angle, 0));
			ins_anim->Montage_Play(forward_QuickstepMontage);
		}
		else if (((2 * PI) / 3) <= angle_diff && angle_diff <= PI || -PI <= angle_diff && angle_diff <= (-2 * PI) / 3) //Backward Quickstep (120 to 240 degrees)
		{
			cap_angle = cap_angle + 180;
			Owner->SetActorRotation(FRotator3d(0, cap_angle, 0));
			ins_anim->Montage_Play(backward_QuickstepMontage);
		}
		else if (((PI / 3) <= angle_diff && angle_diff <= ((2 * PI) / 3))) //Right Quickstep (60 to 120 degrees)
		{
			cap_angle = cap_angle - 90;
			ins_anim->Montage_Play(right_QuickstepMontage);
		}
		else
		{
			cap_angle = cap_angle + 90;
			ins_anim->Montage_Play(left_QuickstepMontage);
		}
	}
}
