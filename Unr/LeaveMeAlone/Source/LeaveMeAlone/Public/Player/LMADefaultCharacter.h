// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMADefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ULMAHealthComponent;
class UAnimMontage;
class ULMAWeaponComponent;

UCLASS()
class LEAVEMEALONE_API ALMADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALMADefaultCharacter();


	UFUNCTION()
	ULMAHealthComponent* GetHealthComponent() const { return HealthComponent; } 

	UFUNCTION(BlueprintCallable, Category = "Character")
	float GetStamina() const { return Stamina; };

	UFUNCTION(BlueprintCallable, Category = "Character")
	float GetSprinting() const { return IsSprinting; };

	//UFUNCTION(BlueprintNativeEvent, Category = "Character")
	void OnDeath();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Health")
	ULMAHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Weapon")
	ULMAWeaponComponent* WeaponComponent;

	UPROPERTY()
	UDecalComponent* CurrentCursor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Components|Stamina")
	float MaxStamina = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Components|Stamina")
	float StaminaDrainRate = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Components|Stamina")
	float StaminaRecoveryRate = 10.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Stamina")
	bool IsSprinting = false;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathMontage;

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float YRotation = -75.0f;

	float ArmLength = 1400.0f;
	float MinZoom = 100.0f;
	float MaxZoom = 5000.0f;
	float ZoomStep = 50.0f;
	float FOV = 55.0f;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void MoveZoom(float Value);

	float DefaultWalkSpeed;
	float Stamina = 0.0f;
	bool CanSprint = true;

	void StaminaLogic();
	void StartSprinting();
	void StopSprinting();

	
	void OnHealthChanged(float NewHealth);

	void RotationPlayerOnCursor();

};