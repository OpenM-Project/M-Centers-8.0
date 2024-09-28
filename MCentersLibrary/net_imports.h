#pragma once
namespace MCentersLibrary {

	namespace NetImports {
		void Initialise();
		class Logger {
		public:
			static void StartOperation(const wchar_t* operationDescription);
			static 	void CompleteOperation(const wchar_t* operationDescription);
			static void Write(const wchar_t* message, bool IgnoreIfNotInitialized);
			static void Write(const wchar_t* message);
		};
	}
}