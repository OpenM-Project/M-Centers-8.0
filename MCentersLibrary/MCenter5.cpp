#include "pch.h"
#include "MCenter5.h"
#include <cstdio>
#include <windows.h>
#include <tlhelp32.h>
#include <shobjidl_core.h>
#include <ShObjIdl.h>
#include <atlbase.h>
#include <stdio.h>
#include <wchar.h>
#include <string>
#include <vector>

#include <sstream>
#include <iomanip>

#include "net_imports.h"
#include "Utility.h"
using MCentersLibrary::NetImports::Logger;
using MCentersNative::Utility;


namespace MCentersNative::MCenter5 {


	std::string* DataSource;
	
	char* secondBuffer;
	SIZE_T SetDataSource(int processId, void* baseAddress, int size) {

		INT64 baseAddress1 = (INT64)baseAddress;
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
		char* buffer =new char[size + 1];


		SIZE_T x = size;

		SIZE_T bytesRead = 0;
		//	for (size_t i = 0; i < x; i++)
		//	{
			//	secondBuffer = buffer + i;
			///		SIZE_T Read = 0;
			//		if (ReadProcessMemory(hProcess, (LPCVOID)(baseAddress1), &buffer, 1, &Read))
			//			bytesRead += Read;

		//	}
		if (ReadProcessMemory(hProcess, (LPCVOID)(baseAddress1), buffer, x, &bytesRead) == false)
		{
			delete[] buffer;
			CloseHandle(hProcess);
			return -1;
		}
		DataSource = new std::string(buffer, bytesRead);
		delete[] buffer;
		CloseHandle(hProcess);
		return bytesRead;

	}


	 std::string static convert_to_string(size_t number)
	{

		std::ostringstream oss; // output string stream
		oss << std::hex << std::noshowbase << number; // set base and no padding
		std::string hex_str = oss.str(); // get the hex string

		return hex_str;
	}
	__int64 TryFindValue(int* count, bool shouldOpenBetaEdition) {
		Logger::StartOperation(L"Try Find Value");
		if (shouldOpenBetaEdition) {
			char value[] = "\x0f\xb6\x81\x28\x01\x00\x00\x48\x83\xc4\x30\x5b\xc3";

			std::string search = std::string(value, 9);
			Logger::Write((L"Data Size\t\t"+ Utility::Join(L" \t", DataSource->size())).c_str());
			size_t offset = -1;


			*count = 0;
			offset = (*DataSource).find(search);


			if (offset != std::string::npos) {
				Logger::Write(Utility::Join(L" ", offset).c_str());
				*count = 1;
				size_t secondOffset = -1;
				secondOffset = (*DataSource).find(search, offset + (size_t)6);

				if (secondOffset != std::string::npos)
					*count = 2;


			}
			Logger::CompleteOperation(L"Try Find Value");
			return offset;
		}
		else
		{
			char value[9] = { 0 };
			INT64* val = (INT64*)&value;

			*val = 0xC30000012881B60F;

			value[8] = 0x00;

			std::string search = std::string(value, 8);
			Logger::Write(L"Data Size", Utility::Join(L" \t", DataSource->size()).c_str());
			size_t offset = -1;


			*count = 0;
			offset = (*DataSource).find(search);
			Logger::Write(Utility::Join(L" ", offset).c_str());

			if (offset != std::string::npos) {
				*count = 1;
				size_t secondOffset = -1;
				secondOffset = (*DataSource).find(search, offset + (size_t)6);

				if (secondOffset != std::string::npos)
					*count = 2;


			}
			Logger::CompleteOperation(L"Try Find Value");
			return offset;
		}
		
	}





	int LaunchApp(bool launchPreviewEdition) {
		Logger::StartOperation(L"Opening Minecraft");
		const  wchar_t* appId = launchPreviewEdition ? L"Microsoft.MinecraftWindowsBeta_8wekyb3d8bbwe!App" : L"Microsoft.MinecraftUWP_8wekyb3d8bbwe!App";
		Logger::Write(appId);
		auto pid = Utility::LaunchAppId((LPCWSTR)appId);
		Logger::CompleteOperation(L"Opening Minecraft");
		return pid;



	}

	int EnableDebugPriv()
	{
		HANDLE hToken;
		LUID luid;
		
		OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);

		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid);

		TOKEN_PRIVILEGES tkp = { 1, { { luid,SE_PRIVILEGE_ENABLED } } };


		AdjustTokenPrivileges(hToken, false, &tkp, sizeof(tkp), NULL, NULL);

		CloseHandle(hToken);
		return 1;
	}

	__int64 offset = 0xDF1A60;

	INT64 disableTrial = 0x90909000B0C031;
	INT64 enableTrial = 0x90909001B0C031;
	INT64 defaultvalue = 0x0000012881B60F;

	void ChangePatchValues(INT64 trialDisable, INT64 trialEnable, INT64 normal, __int64 position) {
		offset = position;
		disableTrial = trialDisable;
		enableTrial = trialEnable;
		defaultvalue = normal;
	}


	char defaultData[] = {
	'\x0F', '\xB6', '\x44', '\x24', '\x78'
	};

	char patchBytes[] = {
		'\x31', '\xC0', '\xB0', '\x00', '\x90'
	};

	int IsValidApp(int processId, void* baseAddress)
	{
		INT64 baseAddress1 = (INT64)baseAddress;
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
		char buffer[5] = {};
		SIZE_T bytesRead = 0;
		if (ReadProcessMemory(hProcess, (LPCVOID)(baseAddress1 + offset), &buffer, 5, &bytesRead) == false)
		{
			CloseHandle(hProcess);
			return -1;
		}
		if (bytesRead != 5) {
			CloseHandle(hProcess);
			return -2;
		}
		bool matched = true;
		for (int i = 0; i < 5; i++)
		{
			matched = buffer[i] == defaultData[i];
			if (!matched)
				break;
		}

		CloseHandle(hProcess);
		if (matched)
			return 1;
		return 0;
	}
	int static Write(HANDLE hProcess, INT64 baseAddress1, bool trial) {
		Logger::StartOperation(L"Started Write Operation");
		SIZE_T bytesWritten = 0;
		LPVOID writeAddress = (LPVOID)(baseAddress1 + offset);
		auto write = trial ? enableTrial : disableTrial;
		if (!WriteProcessMemory(hProcess, writeAddress, &write, 7, &bytesWritten))
		{
			CloseHandle(hProcess);
			Logger::Write(L"Failed to Write");
			Logger::CompleteOperation(L"Started Write Operation");
			return -3;
		}

		Logger::Write(Utility::Join(L"Bytes Written:", Utility::Join(L" \t", bytesWritten)).c_str());
		if (bytesWritten != 7) {
			CloseHandle(hProcess);
			Logger::Write(L"Written bytes count is not 7");
			Logger::CompleteOperation(L"Started Write Operation");
			return -4;
		}
		CloseHandle(hProcess);
		Logger::CompleteOperation(L"Started Write Operation");
		return 1;
	}
	int ModifyApp(int processId, void* baseAddress, bool trial, bool ignoreVerification)
	{


		INT64 baseAddress1 = (INT64)baseAddress;
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
		if (ignoreVerification)
			return Write(hProcess, baseAddress1, trial);
		
		LPCVOID address = (LPCVOID)(baseAddress1 + offset);
		char buffer[8] = {};
		SIZE_T bytesRead = 0;
		INT64 g = 0;
		ReadProcessMemory(hProcess, address, &g, 7, &bytesRead);

		//AddLog(L"Bytes Read:", Utility::(L" \t", bytesRead));
		if (bytesRead != 7) {
			CloseHandle(hProcess);
			return -2;
		}


		bool matched = g == defaultvalue || g == enableTrial || g == disableTrial;



		if (matched)
			return Write(hProcess, baseAddress1, trial);
		CloseHandle(hProcess);
		return 0;
	}


	HANDLE Handles[20] = {};
	int HandleCount = 0;
	void GetHandles()
	{
		int i = -1;


		EnableDebugPriv();

		PROCESSENTRY32 entry = { sizeof(PROCESSENTRY32) };

		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		if (Process32First(snapshot, &entry) == TRUE)
		{
			while (Process32Next(snapshot, &entry) == TRUE)
			{
				if (_stricmp((const char*)entry.szExeFile, "Minecraft.Windows.exe") == 0)
				{
					HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
					i++;
					Handles[i] = hProcess;
					if (i == 20)break;



				}
			}
		}

		CloseHandle(snapshot);
		HandleCount = i;


	}





}