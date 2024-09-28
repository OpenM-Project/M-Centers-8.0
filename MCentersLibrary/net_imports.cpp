#include "net_pch.h"
#include "net_imports.h"
using namespace System::Reflection;
using namespace System;
namespace MCentersLibrary {


	private ref  class Logger {
		static MethodInfo^ StartOperationMethodInfo;
		static MethodInfo^ CompleteOperationMethodInfo;
		static MethodInfo^ WriteMethodInfo;

		static bool initialized = false;
	public:
		static bool Initialize(Type^ loggerT) {
			StartOperationMethodInfo = loggerT->GetMethod("StartOperation", gcnew array<Type^> { String::typeid });
			CompleteOperationMethodInfo = loggerT->GetMethod("CompleteOperation", gcnew array<Type^> { String::typeid });
			WriteMethodInfo = loggerT->GetMethod("Write", gcnew array<Type^> { String::typeid, bool::typeid });
			if (StartOperationMethodInfo == nullptr || CompleteOperationMethodInfo == nullptr || WriteMethodInfo == nullptr) return false;
			initialized = true;
			return true;
		}


		static void StartOperation(String^ OperationDescription) {
			StartOperationMethodInfo->Invoke(nullptr, gcnew array<Object^> { OperationDescription });
		}

		static void CompleteOperation(String^ OperationDescription) {
			CompleteOperationMethodInfo->Invoke(nullptr, gcnew array<Object^> { OperationDescription });
		}
		static void Write(String^ message, bool IgnoreIfNotInitialized) {
			WriteMethodInfo->Invoke(nullptr, gcnew array<Object^> { message, IgnoreIfNotInitialized });
		}
		static void Write(String^ message) {
			WriteMethodInfo->Invoke(nullptr, gcnew array<Object^> { message, false });
		}
	};



 public ref class RawImports {
	  static Assembly^ MainAssembly;
	  static Type^ LoggerT;
	  
	  static bool initialized = false;
 public: static  void Initialize() {
		  MainAssembly=Assembly::GetEntryAssembly();
		  if (MainAssembly == nullptr) return;
		  LoggerT=MainAssembly->GetType("MCenters.Logger");
		  if (LoggerT == nullptr) return;
		  initialized = Logger::Initialize(LoggerT);
	  }

};
 

 namespace NetImports {
	 void Initialise() {
		 RawImports::Initialize();
	 }
		 
		  void Logger::StartOperation(const wchar_t* operationDescription) {
			 MCentersLibrary::Logger::StartOperation(gcnew String(operationDescription));
	}
		 void Logger::CompleteOperation(const wchar_t* operationDescription) {
			 MCentersLibrary::Logger::CompleteOperation(gcnew String(operationDescription));
		 }
		   void Logger::Write(const wchar_t* message, bool IgnoreIfNotInitialized) {
			  MCentersLibrary::Logger::Write(gcnew String(message), IgnoreIfNotInitialized);
			 
		 }
		 void Logger::Write(const wchar_t* message) {
			  MCentersLibrary::Logger::Write(gcnew String(message));
		 }

	


 }

}