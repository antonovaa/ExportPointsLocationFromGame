// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
//
#include "CoreMinimal.h"
#include "SteamVRFunctionLibrary.h"
#include "SteamVRPrivate.h"
#include "SteamVRHMD.h"
#include "XRMotionControllerBase.h"

USteamVRFunctionLibrary::USteamVRFunctionLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

#if STEAMVR_SUPPORTED_PLATFORMS
FSteamVRHMD* GetSteamVRHMD()
{
	if (GEngine->XRSystem.IsValid() && (GEngine->XRSystem->GetSystemName() == FSteamVRHMD::SteamSystemName))
	{
		return static_cast<FSteamVRHMD*>(GEngine->XRSystem.Get());
	}

	return nullptr;
}

ISteamVRPlugin* SteamVRPlugin;

inline vr::IVRSystem* GetVRSystem()
{
	if (SteamVRPlugin == nullptr)
	{
		SteamVRPlugin = &FModuleManager::LoadModuleChecked<ISteamVRPlugin>(TEXT("SteamVR"));
	}

	return SteamVRPlugin->GetVRSystem();
}



IMotionController* GetSteamMotionController()
{
	static FName DeviceTypeName(TEXT("SteamVRController"));
	TArray<IMotionController*> MotionControllers = IModularFeatures::Get().GetModularFeatureImplementations<IMotionController>(IMotionController::GetModularFeatureName());
	for (IMotionController* MotionController : MotionControllers)
	{
		if (MotionController->GetMotionControllerDeviceTypeName() == DeviceTypeName)
		{
			return MotionController;
		}
	}
	return nullptr;
}
#endif // STEAMVR_SUPPORTED_PLATFORMS

void USteamVRFunctionLibrary::GetValidTrackedDeviceIds(ESteamVRTrackedDeviceType DeviceType, TArray<int32>& OutTrackedDeviceIds)
{
#if STEAMVR_SUPPORTED_PLATFORMS
	OutTrackedDeviceIds.Empty();

	EXRTrackedDeviceType XRDeviceType = EXRTrackedDeviceType::Invalid;
	switch (DeviceType)
	{
	case ESteamVRTrackedDeviceType::Controller:
		XRDeviceType = EXRTrackedDeviceType::Controller;
		break;
	case ESteamVRTrackedDeviceType::TrackingReference:
		XRDeviceType = EXRTrackedDeviceType::TrackingReference;
		break;
	case ESteamVRTrackedDeviceType::Other:
		XRDeviceType = EXRTrackedDeviceType::Other;
		break;
	case ESteamVRTrackedDeviceType::Invalid:
		XRDeviceType = EXRTrackedDeviceType::Invalid;
		break;
	default:
		break;
	}


	FSteamVRHMD* SteamVRHMD = GetSteamVRHMD();
	if (SteamVRHMD)
	{
		SteamVRHMD->EnumerateTrackedDevices(OutTrackedDeviceIds, XRDeviceType);
	}
#endif // STEAMVR_SUPPORTED_PLATFORMS
}

bool USteamVRFunctionLibrary::GetTrackedDevicePositionAndOrientation(int32 DeviceId, FVector& OutPosition, FRotator& OutOrientation)
{
	bool RetVal = false;

#if STEAMVR_SUPPORTED_PLATFORMS
	FSteamVRHMD* SteamVRHMD = GetSteamVRHMD();
	if (SteamVRHMD)
	{
		FQuat DeviceOrientation = FQuat::Identity;
		RetVal = SteamVRHMD->GetCurrentPose(DeviceId, DeviceOrientation, OutPosition);
		OutOrientation = DeviceOrientation.Rotator();
	}
#endif // STEAMVR_SUPPORTED_PLATFORMS

	return RetVal;
}

bool USteamVRFunctionLibrary::GetControllerDevicePositionAndOrientation(int32 Number, FVector& OutPosition, FRotator& OutOrientation)
{
	bool RetVal = false;

#if STEAMVR_SUPPORTED_PLATFORMS
	vr::IVRSystem* VRSystem = GetVRSystem();
	FSteamVRHMD* SteamVRHMD = GetSteamVRHMD();
	if (VRSystem != nullptr&&SteamVRHMD)
	{
		int count = 0;
		for (uint32 DeviceIndex = 0; DeviceIndex < vr::k_unMaxTrackedDeviceCount; ++DeviceIndex)
		{
			// see what kind of hardware this is
			vr::ETrackedDeviceClass DeviceClass = VRSystem->GetTrackedDeviceClass(DeviceIndex);

			// skip non-controller or non-tracker devices
			if (DeviceClass != vr::TrackedDeviceClass_Controller && DeviceClass != vr::TrackedDeviceClass_GenericTracker&&DeviceClass!= vr::TrackedDeviceClass_HMD)
			{
				continue;
			}
			if (DeviceClass == vr::TrackedDeviceClass_Controller)
			{			
				if (count == Number) {

				FQuat DeviceOrientation = FQuat::Identity;
				RetVal = SteamVRHMD->GetCurrentPose(DeviceIndex, DeviceOrientation, OutPosition);
				OutOrientation = DeviceOrientation.Rotator();		
				}
				count++;
			}	
			if (DeviceClass == vr::TrackedDeviceClass_HMD&&Number == 2)
			{			
				FQuat DeviceOrientation = FQuat::Identity;
				RetVal = SteamVRHMD->GetCurrentPose(DeviceIndex, DeviceOrientation, OutPosition);
				OutOrientation = DeviceOrientation.Rotator();		
			}	
			if (DeviceClass == vr::TrackedDeviceClass_GenericTracker&&Number > 2)
			{			
				FQuat DeviceOrientation = FQuat::Identity;
				RetVal = SteamVRHMD->GetCurrentPose(DeviceIndex, DeviceOrientation, OutPosition);
				OutOrientation = DeviceOrientation.Rotator();		
			}
		}
		return RetVal;
	}
	else if(SteamVRHMD)
	{
		SteamVRPlugin = &FModuleManager::LoadModuleChecked<ISteamVRPlugin>(TEXT("SteamVR"));
	}

#endif // STEAMVR_SUPPORTED_PLATFORMS

	return RetVal;
}

bool USteamVRFunctionLibrary::GetHandPositionAndOrientation(int32 ControllerIndex, EControllerHand Hand, FVector& OutPosition, FRotator& OutOrientation)
{
	bool RetVal = false;

#if STEAMVR_SUPPORTED_PLATFORMS
	IMotionController* SteamMotionController = GetSteamMotionController();
	if (SteamMotionController)
	{
		// Note: the steam motion controller ignores the WorldToMeters scale argument.
		RetVal = static_cast<FXRMotionControllerBase*>(SteamMotionController)->GetControllerOrientationAndPosition(ControllerIndex, Hand, OutOrientation, OutPosition, -1.0f);
	}
#endif // STEAMVR_SUPPORTED_PLATFORMS

	return RetVal;
}
