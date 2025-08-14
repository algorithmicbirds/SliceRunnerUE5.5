// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BheaviorTreeTasks/BTTask_LookAt.h"
#include "Debug/DebugHelper.h"

UBTTask_LookAt::UBTTask_LookAt()
{
    bNotifyTick = false; 
}

EBTNodeResult::Type UBTTask_LookAt::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    //Super::ExecuteTask(OwnerComp, NodeMemory);
    //Debug::Print("Look At task ran successfully");
    return EBTNodeResult::Succeeded;
}
