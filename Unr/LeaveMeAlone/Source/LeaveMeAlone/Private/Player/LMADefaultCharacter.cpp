// LeaveMeAlone Game by Netologiya. All Rights Reserved.


#include "Player/LMADefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "LMAHealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"


ALMADefaultCharacter::ALMADefaultCharacter()
{

	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = ArmLength;
	SpringArmComponent->SetRelativeRotation(FRotator(YRotation, 0.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bEnableCameraLag = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetFieldOfView(FOV);
	CameraComponent->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	HealthComponent = CreateDefaultSubobject<ULMAHealthComponent>("HealthComponent");

	Stamina = MaxStamina;
}

void ALMADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (CursorMaterial)
	{
		CurrentCursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), CursorMaterial, CursorSize, FVector(0));
	}

	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnHealthChanged.AddUObject(this, &ALMADefaultCharacter::OnHealthChanged);
	HealthComponent->OnDeath.AddUObject(this, &ALMADefaultCharacter::OnDeath);

	DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

void ALMADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!(HealthComponent->IsDead()))
	{
		RotationPlayerOnCursor();
		StaminaLogic();
	}
}

void ALMADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALMADefaultCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALMADefaultCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveZoom", this, &ALMADefaultCharacter::MoveZoom);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ALMADefaultCharacter::StartSprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ALMADefaultCharacter::StopSprinting);
}

void ALMADefaultCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ALMADefaultCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ALMADefaultCharacter::MoveZoom(float Value) {
	if (Value != 0.0f)
	{
		/*if (((ArmLength + (Value * ZoomStep)) <= MaxZoom) || ((ArmLength + (Value * ZoomStep)) >= MinZoom))
			ArmLength = ArmLength + (Value * ZoomStep);
		SpringArmComponent->TargetArmLength = ArmLength;*/
		ArmLength = FMath::Clamp((ArmLength + (Value * ZoomStep)), MinZoom, MaxZoom);
		SpringArmComponent->TargetArmLength = ArmLength;
	}
}

void ALMADefaultCharacter::OnDeath()
{
	CurrentCursor->DestroyRenderState_Concurrent();
	PlayAnimMontage(DeathMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.0f);
	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void ALMADefaultCharacter::OnHealthChanged(float NewHealth) {
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Health = %f"), NewHealth));
}

void ALMADefaultCharacter::RotationPlayerOnCursor() {
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		FHitResult ResultHit;
		PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, ResultHit);
		float FindRotatorResultYaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ResultHit.Location).Yaw;
		SetActorRotation(FQuat(FRotator(0.0f, FindRotatorResultYaw, 0.0f)));
		if (CurrentCursor)
		{
			CurrentCursor->SetWorldLocation(ResultHit.Location);
		}
	}
}

void ALMADefaultCharacter::StaminaLogic()
{
	bool IsMoving = GetVelocity().Size() > 0.0f;
	if (IsSprinting && IsMoving)
	{
		Stamina -= StaminaDrainRate * GetWorld()->GetDeltaSeconds();
		if (Stamina <= 0.0f)
		{
			Stamina = 0.0f;
			StopSprinting();
		}
	}
	else if (Stamina < MaxStamina)
	{
		Stamina += StaminaRecoveryRate * GetWorld()->GetDeltaSeconds();
		if (Stamina > MaxStamina)
		{
			Stamina = MaxStamina;
		}
	}

	CanSprint = (Stamina > 0.0f) && (GetVelocity().Size() > 0.0f);
}

void ALMADefaultCharacter::StartSprinting()
{
	if (CanSprint && ((int)Stamina > ((int)MaxStamina % 10)))
	{
		IsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed * 2;
	}
}

void ALMADefaultCharacter::StopSprinting()
{
	IsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
}
