#include "net_pch.h"
#include "net_exports.h"
#include "native.h"
#include "MCenter5.h"
#include <msclr/marshal_cppstd.h> // Include this header for string conversion

using namespace msclr::interop; // Namespace for string conversion
namespace MCentersLibrary {
	public  ref class DllMethod
	{
	
	public: static bool Patchx64Dll() {
		return	MCentersNative::DllMethod::Patchx64Dll();
	}

	public: static bool Patchx86Dll() {
		return	MCentersNative::DllMethod::Patchx86Dll();
	}
    
	/// <summary>
	/// Determines Platform Type for a specified dll
	/// </summary>
	/// <param name="dllFilePath">path of dll file</param>
	/// <returns>
	/// 0 means unknown platform or error
	/// <para>1 means AMD x64</para>
	/// <para>2 means x86</para></returns>
	public: static int GetPlatform(System::String^ dllFilePath) {
		return MCentersNative::DllMethod::GetPlatform(marshal_as<std::string>(dllFilePath));
    }

	public: static bool IsPresent() {
		return MCentersNative::DllMethod::IsPresent();
	}
	};

	public ref class MCenters5 {

	public: static void GetHandles()
	{
		MCentersNative::MCenter5::GetHandles();
	}
	public: static int EnableDebugPriv()
	{
		return	MCentersNative::MCenter5::EnableDebugPriv();
	}
	public: static int IsValidApp(int processId, System::IntPtr^ baseAddress)
	{
		return	MCentersNative::MCenter5::IsValidApp(processId, baseAddress->ToPointer());
	}
	public: static int ModifyApp(int processId, void* baseAddress, bool trial, bool ignoreVerification)
	{
		return	MCentersNative::MCenter5::ModifyApp(processId, baseAddress, trial, ignoreVerification);
	}
	public: static   int LaunchApp(bool launchPreviewEdition)
	{
		return MCentersNative::MCenter5::LaunchApp(launchPreviewEdition);
	}
	public: static void  ChangePatchValues(System::Int64 trialDisable, System::Int64 trialEnable, System::Int64 normal, System::Int64 position)
	{
		MCentersNative::MCenter5::ChangePatchValues(trialDisable, trialEnable, normal, position);
	}
	public: static __int64 TryFindValue(int* count,bool shouldOpenBetaEdition)
	{
		return	MCentersNative::MCenter5::TryFindValue(count,shouldOpenBetaEdition);
	}
	public: static SIZE_T SetDataSource(int processId, void* baseAddress, int size)
	{
		return	MCentersNative::MCenter5::SetDataSource(processId, baseAddress, size);
	}


	};
}