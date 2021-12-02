#ifndef MACROS_H
#define MACROS_H

#define DLL_FUNC(func) \
	Dll##func

#define DLL_FUNC_TYPE(func) \
	func##Proc

// In MSVC's preprocessor, __VA_ARGS__ seems to behave quite differently from the standard specification.
#define DLL_FUNC_DECL(rettype, func, ...) \
	typedef rettype (*DLL_FUNC_TYPE(func))(__VA_ARGS__)

#define DLL_FUNC_DEF(func) \
	DLL_FUNC_TYPE(func) DLL_FUNC(func) = NULL

#define DLL_FUNC_GET(handle, func) \
	DLL_FUNC(func) = (DLL_FUNC_TYPE(func))GetProcAddress(handle, #func)

#define DLL_FUNC_GET2(handle, func, name) \
	DLL_FUNC(func) = (DLL_FUNC_TYPE(func))GetProcAddress(handle, #name)

#define DLL_FUNC_GET_FAIL_RET(handle, func, retval) \
	DLL_FUNC_GET(handle, func); \
	if (!DLL_FUNC(func)) return retval

#define DLL_FUNC_GET2_FAIL_RET(handle, func, name, retval) \
	DLL_FUNC_GET2(handle, func, name); \
	if (!DLL_FUNC(func)) return retval

#define DLL_FUNC_CALL(func, ...) \
	(*DLL_FUNC(func))(__VA_ARGS__)
#endif /* MACROS_H */

