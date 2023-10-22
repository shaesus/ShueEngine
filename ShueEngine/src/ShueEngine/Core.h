#pragma once

#ifdef SH_PLATFORM_WINDOWS
#ifdef SH_BUILD_DLL
#define SHUE_API __declspec(dllexport)
#else
#define SHUE_API __declspec(dllimport)
#endif	
#else 
#error ShueEngine only supports Windows!
#endif

#define BIT(x) (1 << x)