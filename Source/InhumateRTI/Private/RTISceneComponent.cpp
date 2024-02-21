#include "RTISceneComponent.h"

inhumate::rti::RTIClient *URTISceneComponent::RTI()
{
    return URTISubsystem::GetRTIForComponent(this);
}

URTISubsystem *URTISceneComponent::GetSubsystem()
{
    return URTISubsystem::GetSubsystemForComponent(this);
}

