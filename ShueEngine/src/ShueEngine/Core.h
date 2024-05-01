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

#define SH_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)