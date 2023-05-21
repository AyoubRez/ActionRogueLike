// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USAttributesComponent;
class USInteractionComponent;
struct FInputActionValue;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category="Effects")
	FName TimeToHitParamName;

	UPROPERTY(VisibleAnywhere, Category="Effects")
	FName HandeSocketName;

	UPROPERTY(EditAnywhere, Category="Abilities|Attack|Primary")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category="Abilities|Attack|Primary")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category="Abilities|Attack|SpellOne")
	TSubclassOf<AActor> SpellOneProjectileClass;

	UPROPERTY(EditAnywhere, Category="Abilities|Attack|SpellOne")
	TSubclassOf<AActor> SpellTwoProjectileClass;

	UPROPERTY(EditAnywhere, Category="Abilities|Attack|SpellOne")
	UAnimMontage* SpellOneAttackAnim;

	UPROPERTY(EditAnywhere, Category="Abilities|Attack|SpellOne")
	UAnimMontage* SpellTwoAttackAnim;

	UPROPERTY(EditAnywhere, Category="Effects")
	UParticleSystem* CastingEffect;

	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_SpellOneAttack;
	FTimerHandle TimerHandle_SpellTwoAttack;
	float AttackAnimDelay;

	void PrimaryAttack_TimeElapsed();
	void SpellOneAttack_TimeElapsed();
	void SpellTwoAttack_TimeElapsed();

	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);
	void StartAttackEffect();

public:
	ASCharacter();

protected:
	virtual void BeginPlay() override;

	/**************** INPUT *************/
#pragma region Inputs
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|Context")
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|Actions")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|Actions")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|Actions")
	UInputAction* PrimaryAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|Actions")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|Actions")
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|Actions")
	UInputAction* SpellOneAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|Actions")
	UInputAction* SpellTwoAction;
#pragma endregion
	/********************************************/

	/******** Actions *****/
	/**** Movement */
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	/***************************/
	/****** Abilities */
	void PrimaryAttack(const FInputActionValue& Value);
	void PrimaryInteract(const FInputActionValue& Value);
	void SpellOneAttack(const FInputActionValue& Value);
	void SpellTwoAttack(const FInputActionValue& Value);
	/*******************************************/
	/********** Components ****/
#pragma region Components
	UPROPERTY(VisibleAnywhere, Category="Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category="Components")
	USInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USAttributesComponent* AttributesComp;
#pragma endregion
	/***************************************/

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributesComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
