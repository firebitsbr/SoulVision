// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "BaseCreature.h"
#include "BattleInterface.h"
#include "CreaturePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SOULVISION_API ACreaturePlayerController : public APlayerController, public IBattleInterface
{
	GENERATED_BODY()
	
protected:
	// Input Component
	virtual void SetupInputComponent() override;
	
	// Called for forward/backward input
	void MoveForward(float Value);

	// Called for right/left input
	void MoveRight(float Value);

	// Called for jump input
	void StartJump();
	void StopJump();

	// Called for posses input
	void Possession();

	// Called for attack input
	void Attack();

	// Called when attack is complete
	UFUNCTION()
	void OnAttackComplete();

	// Called via input to turn at a given rate
	void TurnAtRate(float Rate);

	// Called via input to turn look up/down at a given rate
	void LookUpAtRate(float Rate);

	FTimerDelegate PossessionTweenDelegate;
	FTimerHandle PossessionTweenTimer;

	UFUNCTION()
	void OnPossessionAnimationComplete(ABaseCreature* OtherCreature);

	/* Move selection functionality*/

	// Variable for storing selected Move
	uint8 SelectedMoveIndex = 0;

	void PreviousMove();

	void NextMove();

	UPROPERTY(VisibleAnywhere, Category = "Test")
	bool bIsAttacking = false;	

public:
	ACreaturePlayerController();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Battle Interface")
	bool InBattle();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Battle Interface")
	bool StartBattle(AController* Controller, ABaseCreature* Creature);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Battle Interface")
	bool EndBattle();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Battle Interface")
	void Death();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Battle Interface")
	void Possessed();

	UFUNCTION(BlueprintCallable, Category = "Battle Interface")
	ABaseCreature* GetEnemyCreature();

	UFUNCTION(BlueprintCallable, Category = "Battle Interface")
	FName GetSelectedMove();
};
