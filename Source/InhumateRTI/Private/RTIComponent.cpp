#include "RTIComponent.h"

inhumate::rti::RTIClient *URTIComponent::RTI()
{
    return URTISubsystem::GetRTIForComponent(this);
}

URTISubsystem *URTIComponent::GetSubsystem()
{
    return URTISubsystem::GetSubsystemForComponent(this);
}
