// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonShooter/Public/Characters/Player/PlayerAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "ThirdPersonShooter/Public/Characters/Player/ShooterCharacter.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	if (APawn* PlayerPawn = TryGetPawnOwner())
	{
		ShooterCharacter = Cast<AShooterCharacter>(PlayerPawn);
		MovementComponent = ShooterCharacter ? ShooterCharacter->GetCharacterMovement() : nullptr;
	}
}

void UPlayerAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	// Check each frame if we have a valid reference to the ShooterCharacter.
	APawn* OwningPawn = TryGetPawnOwner();
	if (OwningPawn != ShooterCharacter || !IsValid(MovementComponent))
	{
		ShooterCharacter = Cast<AShooterCharacter>(OwningPawn);
		MovementComponent = ShooterCharacter ? ShooterCharacter->GetCharacterMovement() : nullptr;
	}
	
	if (!ShooterCharacter || !MovementComponent) return;
	
	const FVector Velocity = ShooterCharacter->GetVelocity();
	Speed = Velocity.Size2D();
	
	bIsInAir = MovementComponent->IsFalling();
	
	// Is the player actively providing movement input?
	bIsAccelerating = MovementComponent->GetCurrentAcceleration().SizeSquared() > KINDA_SMALL_NUMBER;
}




