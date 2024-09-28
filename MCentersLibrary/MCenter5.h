#pragma once
#include <Windows.h>
namespace MCentersNative::MCenter5 {
	extern "C" __declspec(dllexport) void GetHandles();
	extern "C" __declspec(dllexport) int EnableDebugPriv();
	extern "C" __declspec(dllexport) int IsValidApp(int processId, void* baseAddress);
	extern "C" __declspec(dllexport) int ModifyApp(int processId, void* baseAddress, bool trial, bool ignoreVerification);
	extern "C" __declspec(dllexport)  int LaunchApp(bool launchPreviewEdition=false);
	extern "C" __declspec(dllexport) void  ChangePatchValues(INT64 trialDisable, INT64 trialEnable, INT64 normal, __int64 position);
	extern "C" __declspec(dllexport)   __int64 TryFindValue(int* count,bool shouldOpenBetaEdition);
	extern "C" __declspec(dllexport)  SIZE_T SetDataSource(int processId, void* baseAddress, int size);
}