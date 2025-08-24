// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayTags/SRGameplayTags.h"

namespace SRGameplayTags
{

UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");
UE_DEFINE_GAMEPLAY_TAG(InputTag_Dash, "InputTag.Dash");
UE_DEFINE_GAMEPLAY_TAG(InputTag_Grapple, "InputTag.Grapple");
UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack, "InputTag.Attack");
UE_DEFINE_GAMEPLAY_TAG(InputTag_Respawn, "InputTag.Respawn");

UE_DEFINE_GAMEPLAY_TAG(AbilityTag_Jump, "AbilityTag.Movement.Jump");
UE_DEFINE_GAMEPLAY_TAG(AbilityTag_Dash, "AbilityTag.Movement.Dash");
UE_DEFINE_GAMEPLAY_TAG(AbilityTag_Grapple, "AbilityTag.Movement.Grapple");
UE_DEFINE_GAMEPLAY_TAG(AbilityTag_Attack, "AbilityTag.Combat.Attack");
UE_DEFINE_GAMEPLAY_TAG(AbilityTag_Death, "AbilityTag.State.Death");
UE_DEFINE_GAMEPLAY_TAG(AbilityTag_Shoot, "AbilityTag.Combat.Shoot");

UE_DEFINE_GAMEPLAY_TAG(EventTag_AttackWindow, "EventTag.AttackWindow");
UE_DEFINE_GAMEPLAY_TAG(EventTag_AttackState, "EventTag.AttackState");



} // namespace SRGameplayTags
