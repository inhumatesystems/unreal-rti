//
// Inhumate Unreal Engine RTI Plugin
// Copyright 2025 Inhumate AB
//

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogRTIEditor, Log, All);

class FInhumateRTIEditorModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};