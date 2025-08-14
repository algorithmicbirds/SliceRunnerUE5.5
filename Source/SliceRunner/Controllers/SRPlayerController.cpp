// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/SRPlayerController.h"
#include "Camera/SRPlayerCameraManager.h"
#include "PlayerCharacter/SRBaseCharacter.h"

ASRPlayerController::ASRPlayerController() { 
	PlayerCameraManagerClass = ASRPlayerCameraManager::StaticClass();
    PlayerTeamID = FGenericTeamId(1);
}

FGenericTeamId ASRPlayerController::GetGenericTeamId() const { return PlayerTeamID; }

