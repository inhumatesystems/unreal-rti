//
// Inhumate Unreal Engine RTI Plugin
// Copyright 2025 Inhumate AB
//

#include "RTISceneComponent.h"

inhumate::rti::RTIClient *URTISceneComponent::RTI()
{
    return URTISubsystem::GetRTIForComponent(this);
}

URTISubsystem *URTISceneComponent::GetSubsystem()
{
    return URTISubsystem::GetSubsystemForComponent(this);
}

