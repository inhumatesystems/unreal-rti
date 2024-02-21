#include "InhumateRTI.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "Developer/Settings/Public/ISettingsModule.h"
#include "RTISettings.h"
#include "inhumaterti.hpp"

#define LOCTEXT_NAMESPACE "FInhumateRTIModule"

DEFINE_LOG_CATEGORY(LogRTI);

void FInhumateRTIModule::StartupModule()
{
	FString BaseDir = IPluginManager::Get().FindPlugin("InhumateRTI")->GetBaseDir();

/*
Delayed loading disabled - see InhumateRTILibrary.Build.cs
#if PLATFORM_WINDOWS
    FString LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/InhumateRTILibrary/win64/libprotobuf.dll"));
    LibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;
    FString LibraryPath2 = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/InhumateRTILibrary/win64/inhumaterti_shared_protos.dll"));
    LibraryHandle2 = !LibraryPath2.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath2) : nullptr;
    FString LibraryPath3 = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/InhumateRTILibrary/win64/inhumaterti_shared.dll"));
    LibraryHandle3 = !LibraryPath3.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath3) : nullptr;
#endif
*/

    if (ISettingsModule *SettingModule =
        FModuleManager::GetModulePtr<ISettingsModule>("Settings")) {
        SettingModule->RegisterSettings("Project", "Plugins", "InhumateRTI",
                                        LOCTEXT("RuntimeSettingsName", "Inhumate RTI"),
                                        LOCTEXT("RuntimeSettingsDescription",
                                                "Configure Inhumate RTI settings"),
                                        GetMutableDefault<URTISettings>());
    }
}

void FInhumateRTIModule::ShutdownModule()
{
	if (LibraryHandle) FPlatformProcess::FreeDllHandle(LibraryHandle);
    LibraryHandle = nullptr;
    if (LibraryHandle2) FPlatformProcess::FreeDllHandle(LibraryHandle2);
    LibraryHandle2 = nullptr;
    if (LibraryHandle3) FPlatformProcess::FreeDllHandle(LibraryHandle3);
    LibraryHandle3 = nullptr;

    if (ISettingsModule *SettingsModule =
        FModuleManager::GetModulePtr<ISettingsModule>("Settings")) {
        SettingsModule->UnregisterSettings("Project", "Plugins", "Inhumate RTI");
    }
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FInhumateRTIModule, InhumateRTI)
