#pragma once
#include <Windows.h>
#include <vector>
#include <fstream>
#include <cstdio>
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
namespace MCentersNative {

	struct RecordPEx86
	{
		IMAGE_DOS_HEADER DosHeader = {};
		IMAGE_NT_HEADERS32 NtHeader = {};
		IMAGE_SECTION_HEADER textSectionHeader = {};
		std::vector<IMAGE_SECTION_HEADER> sectionHeaders = {};
	};
	struct RecordPEx64
	{
		IMAGE_DOS_HEADER DosHeader = {};
		IMAGE_NT_HEADERS NtHeader = {};
		IMAGE_SECTION_HEADER textSectionHeader = {};
		IMAGE_SECTION_HEADER rDataSectionHeader = {};
		std::vector<IMAGE_SECTION_HEADER> sectionHeaders = {};
	};
	
	class Utility {
	private:
		static bool isLittleEndian;
     public:
		static bool IsLittleEndian();
		template <typename T>
		static std::wstring Join(const wchar_t* first, T second) {
			std::wstringstream wss;        // Create a wide string stream
			wss << second;                 // Insert 'second' into the stream
			std::wstring secondWstring = wss.str(); // Extract the wide string from the stream

			std::wstring final(first);      // Initialize with the 'first' string
			final += secondWstring;         // Concatenate 'secondWstring' to 'final'
			return final;                   // Return the concatenated string
		}
		static void Initialize();
        static RecordPEx86* GetRecordPEx86(std::fstream& fileStream);
        static RecordPEx64* GetRecordPEx64(std::fstream& fileStream);

        static size_t SearchBytePattern(const std::vector<char>& data, char* pattern, size_t patternLength, size_t startIndex = 0);
        static bool areStringsEqual(const char* str1, const char* str2);
        static bool stringStartsWith(const char* str, const char* prefix);
        static bool writeBytesAtAddress(std::fstream& file, uint64_t address, const char* data, std::size_t dataSize);
        static size_t find_pattern_in_array(const char* source, const char* pattern, size_t sourceSize, size_t patternSize, size_t offset = 0);

		static DWORD LaunchAppId(LPCWSTR AUMID);
    };
	
	
}
