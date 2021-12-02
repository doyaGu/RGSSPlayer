#include "RGSS.h"

#include <string.h>
#include <tchar.h>

#include "macros.h"

#define MAX_MSG_SIZE 1024
#define MAX_PATH_SIZE 1024

//typedef void (APIENTRY *RGSSAddRTPPathAProc)(LPCSTR lpPath);
//typedef void (APIENTRY *RGSSAddRTPPathWProc)(LPCWSTR lpPath);
//typedef void (APIENTRY *RGSSAudioFinalizeProc)(void);
//typedef BOOL (APIENTRY *RGSSAudioInitializeProc)(HWND hWnd);
//typedef void (APIENTRY *RGSSClearRTPPathProc)(void);
//typedef LPSTR (APIENTRY *RGSSErrorMessageAProc)(void);
//typedef LPWSTR (APIENTRY *RGSSErrorMessageWProc)(void);
//typedef LPSTR (APIENTRY *RGSSErrorTypeAProc)(void);
//typedef LPWSTR (APIENTRY *RGSSErrorTypeWProc)(void);
//typedef int (APIENTRY *RGSSEvalProc)(LPCSTR lpStr);
//typedef void (APIENTRY *RGSSFinalizeProc)(void);
//typedef void (APIENTRY *RGSSGCProc)(void);
//typedef void (APIENTRY *RGSSGameMainAProc)(HWND hWnd, LPCSTR lpScript, LPCSTR lpArchive);
//typedef void (APIENTRY *RGSSGameMainWProc)(HWND hWnd, LPCWSTR lpScript, LPCWSTR lpArchive);
//typedef BOOL (APIENTRY *RGSSGetBoolProc)(LPCSTR lpStr);
//typedef double (APIENTRY *RGSSGetDoubleProc)(LPCSTR lpStr);
//typedef int (APIENTRY *RGSSGetIntProc)(LPCSTR lpStr);
//typedef LPSTR (APIENTRY *RGSSGetPathWithRTPAProc)(LPCSTR lpRTP);
//typedef LPWSTR (APIENTRY *RGSSGetPathWithRTPWProc)(LPCWCHAR lpRTP);
//typedef LPSTR (APIENTRY *RGSSGetRTPPathAProc)(UINT uIndex);
//typedef LPWSTR (APIENTRY *RGSSGetRTPPathWProc)(UINT uIndex);
//typedef LPSTR (APIENTRY *RGSSGetStringACPProc)(LPCSTR lpStr);
//typedef LPWSTR (APIENTRY *RGSSGetStringUTF16Proc)(LPCSTR lpStr);
//typedef LPSTR (APIENTRY *RGSSGetStringUTF8Proc)(LPCSTR lpStr);
//typedef LPSTR (APIENTRY *RGSSGetSymbolProc)(LPCSTR lpStr);
//typedef RGSSTABLE *(APIENTRY *RGSSGetTableProc)(LPCSTR lpStr);
//typedef void (APIENTRY *RGSSInitializeProc)(HMODULE hModule);
//typedef BOOL (APIENTRY *RGSSSetStringProc)(LPCSTR lpName, LPCSTR lpStr, SIZE_T cch);
//typedef BOOL (APIENTRY *RGSSSetStringACPProc)(LPCSTR lpName, LPCSTR lpStr);
//typedef BOOL (APIENTRY *RGSSSetStringUTF16Proc)(LPCSTR lpName, LPCWSTR lpStr);
//typedef BOOL (APIENTRY *RGSSSetStringUTF8Proc)(LPCSTR lpName, LPCSTR lpStr);
//typedef BOOL (APIENTRY *RGSSSetupFontsProc)(void);
//typedef BOOL (APIENTRY *RGSSSetupRTPAProc)(LPCSTR lpIniFile, LPSTR lpRTPPath, size_t cch);
//typedef BOOL (APIENTRY *RGSSSetupRTPWProc)(LPCWSTR lpIniFile, LPCWSTR lpRTPPath, size_t cch);

DLL_FUNC_DECL(void, RGSSAddRTPPathA, LPCSTR lpPath);
DLL_FUNC_DECL(void, RGSSAddRTPPathW, LPCWSTR lpPath);
DLL_FUNC_DECL(void, RGSSAudioFinalize, void);
DLL_FUNC_DECL(BOOL, RGSSAudioInitialize, HWND hWnd);
DLL_FUNC_DECL(void, RGSSClearRTPPath, void);
DLL_FUNC_DECL(LPSTR, RGSSErrorMessageA, void);
DLL_FUNC_DECL(LPWSTR, RGSSErrorMessageW, void);
DLL_FUNC_DECL(LPSTR, RGSSErrorTypeA, void);
DLL_FUNC_DECL(LPWSTR, RGSSErrorTypeW, void);
DLL_FUNC_DECL(int, RGSSEval, LPCSTR lpStr);
DLL_FUNC_DECL(void, RGSSFinalize, void);
DLL_FUNC_DECL(void, RGSSGC, void);
DLL_FUNC_DECL(void, RGSSGameMainA, HWND hWnd, LPCSTR lpScript, LPCSTR lpArchive);
DLL_FUNC_DECL(void, RGSSGameMainW, HWND hWnd, LPCWSTR lpScript, LPCWSTR lpArchive);
DLL_FUNC_DECL(BOOL, RGSSGetBool, LPCSTR lpStr);
DLL_FUNC_DECL(double, RGSSGetDouble, LPCSTR lpStr);
DLL_FUNC_DECL(int, RGSSGetInt, LPCSTR lpStr);
DLL_FUNC_DECL(LPSTR, RGSSGetPathWithRTPA, LPCSTR lpRTP);
DLL_FUNC_DECL(LPWSTR, RGSSGetPathWithRTPW, LPCWCHAR lpRTP);
DLL_FUNC_DECL(LPSTR, RGSSGetRTPPathA, UINT uIndex);
DLL_FUNC_DECL(LPWSTR, RGSSGetRTPPathW, UINT uIndex);
DLL_FUNC_DECL(LPSTR, RGSSGetStringACP, LPCSTR lpStr);
DLL_FUNC_DECL(LPWSTR, RGSSGetStringUTF16, LPCSTR lpStr);
DLL_FUNC_DECL(LPSTR, RGSSGetStringUTF8, LPCSTR lpStr);
DLL_FUNC_DECL(LPSTR, RGSSGetSymbol, LPCSTR lpStr);
DLL_FUNC_DECL(RGSSTABLE *, RGSSGetTable, LPCSTR lpStr); 
DLL_FUNC_DECL(void, RGSSInitialize, HMODULE hModule); 
DLL_FUNC_DECL(BOOL, RGSSSetString, LPCSTR lpName, LPCSTR lpStr, SIZE_T cch); 
DLL_FUNC_DECL(BOOL, RGSSSetStringACP, LPCSTR lpName, LPCSTR lpStr); 
DLL_FUNC_DECL(BOOL, RGSSSetStringUTF16, LPCSTR lpName, LPCWSTR lpStr); 
DLL_FUNC_DECL(BOOL, RGSSSetStringUTF8, LPCSTR lpName, LPCSTR lpStr); 
DLL_FUNC_DECL(BOOL, RGSSSetupFonts, void);
DLL_FUNC_DECL(BOOL, RGSSSetupRTPA, LPCSTR lpIniFile, LPSTR lpRTPPath, size_t cch);
DLL_FUNC_DECL(BOOL, RGSSSetupRTPW, LPCWSTR lpIniFile, LPWSTR lpRTPPath, size_t cch);

static DLL_FUNC_DEF(RGSSAddRTPPathA);
static DLL_FUNC_DEF(RGSSAddRTPPathW);
static DLL_FUNC_DEF(RGSSAudioFinalize);
static DLL_FUNC_DEF(RGSSAudioInitialize);
static DLL_FUNC_DEF(RGSSClearRTPPath);
static DLL_FUNC_DEF(RGSSErrorMessageA);
static DLL_FUNC_DEF(RGSSErrorMessageW);
static DLL_FUNC_DEF(RGSSErrorTypeA);
static DLL_FUNC_DEF(RGSSErrorTypeW);
static DLL_FUNC_DEF(RGSSEval);
static DLL_FUNC_DEF(RGSSFinalize);
static DLL_FUNC_DEF(RGSSGC);
static DLL_FUNC_DEF(RGSSGameMainA);
static DLL_FUNC_DEF(RGSSGameMainW);
static DLL_FUNC_DEF(RGSSGetBool);
static DLL_FUNC_DEF(RGSSGetDouble);
static DLL_FUNC_DEF(RGSSGetInt);
static DLL_FUNC_DEF(RGSSGetPathWithRTPA);
static DLL_FUNC_DEF(RGSSGetPathWithRTPW);
static DLL_FUNC_DEF(RGSSGetRTPPathA);
static DLL_FUNC_DEF(RGSSGetRTPPathW);
static DLL_FUNC_DEF(RGSSGetStringACP);
static DLL_FUNC_DEF(RGSSGetStringUTF16);
static DLL_FUNC_DEF(RGSSGetStringUTF8);
static DLL_FUNC_DEF(RGSSGetSymbol);
static DLL_FUNC_DEF(RGSSGetTable);
static DLL_FUNC_DEF(RGSSInitialize);
static DLL_FUNC_DEF(RGSSSetString);
static DLL_FUNC_DEF(RGSSSetStringACP);
static DLL_FUNC_DEF(RGSSSetStringUTF16);
static DLL_FUNC_DEF(RGSSSetStringUTF8);
static DLL_FUNC_DEF(RGSSSetupFonts);
static DLL_FUNC_DEF(RGSSSetupRTPA);
static DLL_FUNC_DEF(RGSSSetupRTPW);

static HMODULE hDll = NULL;
static UINT uRgssVersion = 0;

static inline void CharToWchar(LPCSTR pCharStr, LPWSTR pWCharStr, INT iSize)
{
	MultiByteToWideChar(CP_ACP, 0, pCharStr, -1, pWCharStr, iSize);
}

static inline void WcharToChar(LPCWSTR pWCharStr, LPSTR pCharStr, INT iSize)
{
	WideCharToMultiByte(CP_ACP, 0, pWCharStr, -1, pCharStr, iSize, NULL, NULL);
}

BOOL RGSSLibraryInitialize(LPTSTR lpLibFileName, LPTSTR pPath)
{
	static TCHAR szLibPath[MAX_PATH_SIZE] = {0};

	if (hDll)
	{
		return TRUE;
	}

	if (!lpLibFileName)
	{
		return FALSE;
	}
	
	_tcsncpy(szLibPath, __T(".\\"), MAX_PATH_SIZE);
	_tcsncat(szLibPath, lpLibFileName, MAX_PATH_SIZE);
	hDll = LoadLibrary(szLibPath);

	if (!hDll && pPath)
	{
		_tcsncpy(szLibPath, pPath, MAX_PATH_SIZE);
		_tcsncat(szLibPath, __T("\\"), MAX_PATH_SIZE);
		_tcsncat(szLibPath, lpLibFileName, MAX_PATH_SIZE);
		hDll = LoadLibrary(szLibPath);
	}

	if (!hDll)
	{
		return FALSE;
	}

	RGSSGetVersion(lpLibFileName);

	DLL_FUNC_GET_FAIL_RET(hDll, RGSSAudioFinalize, FALSE);
	DLL_FUNC_GET_FAIL_RET(hDll, RGSSAudioInitialize, FALSE);
	DLL_FUNC_GET_FAIL_RET(hDll, RGSSClearRTPPath, FALSE);
	DLL_FUNC_GET_FAIL_RET(hDll, RGSSEval, FALSE);
	DLL_FUNC_GET_FAIL_RET(hDll, RGSSFinalize, FALSE);
	DLL_FUNC_GET_FAIL_RET(hDll, RGSSGC, FALSE);
	DLL_FUNC_GET_FAIL_RET(hDll, RGSSGetBool, FALSE);
	DLL_FUNC_GET_FAIL_RET(hDll, RGSSGetDouble, FALSE);
	DLL_FUNC_GET_FAIL_RET(hDll, RGSSGetInt, FALSE);
	DLL_FUNC_GET_FAIL_RET(hDll, RGSSGetStringACP, FALSE);
	DLL_FUNC_GET_FAIL_RET(hDll, RGSSGetStringUTF8, FALSE);
	DLL_FUNC_GET_FAIL_RET(hDll, RGSSGetTable, FALSE);
	DLL_FUNC_GET_FAIL_RET(hDll, RGSSSetString, FALSE);
	DLL_FUNC_GET_FAIL_RET(hDll, RGSSSetStringACP, FALSE);
	DLL_FUNC_GET_FAIL_RET(hDll, RGSSSetStringUTF8, FALSE);

	if (RGSS_VERSION_MAJOR(uRgssVersion) == 1)
	{
		DLL_FUNC_GET_FAIL_RET(hDll, RGSSInitialize, FALSE);

		DLL_FUNC_GET2_FAIL_RET(hDll, RGSSAddRTPPathA, RGSSAddRTPPath, FALSE);
		DLL_FUNC_GET2_FAIL_RET(hDll, RGSSErrorMessageA, RGSSErrorMessage, FALSE);
		DLL_FUNC_GET2_FAIL_RET(hDll, RGSSErrorTypeA, RGSSErrorType, FALSE);
		DLL_FUNC_GET2_FAIL_RET(hDll, RGSSGameMainA, RGSSGameMain, FALSE);
		DLL_FUNC_GET2_FAIL_RET(hDll, RGSSGetPathWithRTPA, RGSSGetPathWithRTP, FALSE);
		DLL_FUNC_GET2_FAIL_RET(hDll, RGSSGetRTPPathA, RGSSGetRTPPath, FALSE);
		DLL_FUNC_GET2_FAIL_RET(hDll, RGSSSetupRTPA, RGSSSetupRTP, FALSE);
	}
	else
	{
		if (RGSS_VERSION_MAJOR(uRgssVersion) == 2)
		{
			DLL_FUNC_GET2_FAIL_RET(hDll, RGSSInitialize, RGSSInitialize2, FALSE);
		}
		else if (RGSS_VERSION_MAJOR(uRgssVersion) == 3)
		{
			DLL_FUNC_GET_FAIL_RET(hDll, RGSSGetSymbol, FALSE);
			DLL_FUNC_GET2_FAIL_RET(hDll, RGSSInitialize, RGSSInitialize3, FALSE);
		}

		DLL_FUNC_GET_FAIL_RET(hDll, RGSSGetStringUTF16, FALSE);
		DLL_FUNC_GET_FAIL_RET(hDll, RGSSSetupFonts, FALSE);
		DLL_FUNC_GET_FAIL_RET(hDll, RGSSSetStringUTF16, FALSE);
		DLL_FUNC_GET2_FAIL_RET(hDll, RGSSAddRTPPathW, RGSSAddRTPPath, FALSE);
		DLL_FUNC_GET2_FAIL_RET(hDll, RGSSErrorMessageW, RGSSErrorMessage, FALSE);
		DLL_FUNC_GET2_FAIL_RET(hDll, RGSSErrorTypeW, RGSSErrorType, FALSE);
		DLL_FUNC_GET2_FAIL_RET(hDll, RGSSGameMainW, RGSSGameMain, FALSE);
		DLL_FUNC_GET2_FAIL_RET(hDll, RGSSGetPathWithRTPW, RGSSGetPathWithRTP, FALSE);
		DLL_FUNC_GET2_FAIL_RET(hDll, RGSSGetRTPPathW, RGSSGetRTPPath, FALSE);
		DLL_FUNC_GET2_FAIL_RET(hDll, RGSSSetupRTPW, RGSSSetupRTP, FALSE);

	}

	return TRUE;
}

void RGSSLibraryFinalize()
{
	if (hDll)
	{
		FreeLibrary(hDll);
		hDll = NULL;
	}
}

HMODULE RGSSGetHandle()
{
	return hDll;
}

UINT RGSSGetVersion(LPTSTR lpLibFileName)
{
	LPTSTR pStr, pPrvStr;
	int i;

	if (uRgssVersion != 0)
	{
		return uRgssVersion;
	}

	if (!lpLibFileName || !_tcscmp(lpLibFileName, __T("")))
	{
		return 0;
	}

	pStr = _tcsstr(lpLibFileName, __T("RGSS"));
	pStr += 4;
	pPrvStr = pStr;
	while (pStr && (pStr = _tcsstr(pStr, __T("RGSS"))))
	{
		pStr += 4;
		pPrvStr = pStr;
	}
	pStr = pPrvStr;
	if (!pStr)
	{
		return 0;
	}

	for (i = 0; i < 3; ++i)
	{
		uRgssVersion <<= 4;
		uRgssVersion |= ((*(pStr + i) - __T('0')) % 0xF);
	}

	return uRgssVersion;
}

void RGSSAddRTPPath(LPCTSTR lpPath)
{
	size_t len;
#ifdef UNICODE
	char *cp;
#else
	wchar_t *wp;
#endif

	if (RGSS_VERSION_MAJOR(uRgssVersion) == 1)
	{
		if (!DLL_FUNC(RGSSAddRTPPathA))
		{
			return;
		}

#ifdef UNICODE
		len = wcslen(lpPath);
		cp = (char *)malloc(sizeof(char) * (len + 1));
		memset(cp, 0, sizeof(char) * (len + 1));
		WcharToChar(lpPath, cp, len);

		DLL_FUNC_CALL(RGSSAddRTPPathA, cp);

		free(cp);
#else
		DLL_FUNC_CALL(RGSSAddRTPPathA, lpPath);
#endif
	}
	else
	{
		if (!DLL_FUNC(RGSSAddRTPPathW))
		{
			return;
		}

#ifndef UNICODE
		len = strlen(lpPath);
		wp = (wchar_t *)malloc(sizeof(wchar_t) * (len + 1));
		memset(wp, 0, sizeof(wchar_t) * (len + 1));
		CharToWchar(lpPath, wp, len);

		DLL_FUNC_CALL(RGSSAddRTPPathW, wp);

		free(wp);
#else
		DLL_FUNC_CALL(RGSSAddRTPPathW, lpPath);
#endif
	}
}

void RGSSAudioFinalize()
{
	if (!DLL_FUNC(RGSSAudioFinalize))
	{
		return;
	}

	DLL_FUNC_CALL(RGSSAudioFinalize);
}

BOOL RGSSAudioInitialize(HWND hWnd)
{
	if (!DLL_FUNC(RGSSAudioInitialize))
	{
		return FALSE;
	}

	return DLL_FUNC_CALL(RGSSAudioInitialize, hWnd);
}

void RGSSClearRTPPath()
{
	if (!DLL_FUNC(RGSSClearRTPPath))
	{
		return;
	}

	DLL_FUNC_CALL(RGSSClearRTPPath);
}

LPTSTR RGSSErrorMessage()
{
	static char msg[MAX_MSG_SIZE] = {0};
	static wchar_t wmsg[MAX_MSG_SIZE] = {0};

#ifdef UNICODE
	char *cp;
#else
	wchar_t *wp;
#endif

	if (RGSS_VERSION_MAJOR(uRgssVersion) == 1)
	{
		if (!DLL_FUNC(RGSSErrorMessageA))
		{
			return NULL;
		}

#ifdef UNICODE
		cp = DLL_FUNC_CALL(RGSSErrorMessageA);
		CharToWchar(cp, (LPWSTR)wmsg, MAX_MSG_SIZE);
		return (LPWSTR)wmsg;
#else
		return DLL_FUNC_CALL(RGSSErrorMessageA);
#endif
	}
	else
	{
		if (!DLL_FUNC(RGSSErrorMessageW))
		{
			return NULL;
		}

#ifndef UNICODE
		wp = DLL_FUNC_CALL(RGSSErrorMessageW);
		WcharToChar(wp, &msg, MAX_MSG_SIZE);
		return &msg;
#else
		return DLL_FUNC_CALL(RGSSErrorMessageW);
#endif
	}
}

LPTSTR RGSSErrorType()
{
	static char type[MAX_MSG_SIZE] = {0};
	static wchar_t wtype[MAX_MSG_SIZE] = {0};

#ifdef UNICODE
	char *cp;
#else
	wchar_t *wp;
#endif

	if (RGSS_VERSION_MAJOR(uRgssVersion) == 1)
	{
		if (!DLL_FUNC(RGSSErrorTypeA))
		{
			return NULL;
		}

#ifdef UNICODE
		cp = DLL_FUNC_CALL(RGSSErrorTypeA);
		CharToWchar(cp, (LPWSTR)wtype, MAX_MSG_SIZE);
		return (LPWSTR)wtype;
#else
		return DLL_FUNC_CALL(RGSSErrorTypeA);
#endif
	}
	else
	{
		if (!DLL_FUNC(RGSSErrorTypeW))
		{
			return NULL;
		}

#ifndef UNICODE
		wp = DLL_FUNC_CALL(RGSSErrorTypeW);
		WcharToChar(wp, &type, MAX_MSG_SIZE);
		return &type;
#else
		return DLL_FUNC_CALL(RGSSErrorTypeW);
#endif
	}
}

int RGSSEval(LPCSTR lpStr)
{
	if (!DLL_FUNC(RGSSEval))
	{
		return -1;
	}

	return DLL_FUNC_CALL(RGSSEval, lpStr);
}

void RGSSFinalize()
{
	if (!DLL_FUNC(RGSSFinalize))
	{
		return;
	}

	DLL_FUNC_CALL(RGSSFinalize);
}


void RGSSGC()
{
	if (!DLL_FUNC(RGSSGC))
	{
		return;
	}

	DLL_FUNC_CALL(RGSSGC);
}

void RGSSGameMain(HWND hWnd, LPCTSTR lpScript, LPCTSTR lpArchive)
{
	size_t len;
#ifdef UNICODE
	char *cs, *ca;
#else
	wchar_t *ws, *wa;
#endif

	if (RGSS_VERSION_MAJOR(uRgssVersion) == 1)
	{
		if (!DLL_FUNC(RGSSGameMainA))
		{
			return;
		}

#ifdef UNICODE
		len = wcslen(lpScript);
		cs = (char *)malloc(sizeof(char) * (len + 1));
		memset(cs, 0, sizeof(char) * (len + 1));
		WcharToChar(lpScript, cs, len);

		len = wcslen(lpArchive);
		ca = (char *)malloc(sizeof(char) * (len + 1));
		memset(ca, 0, sizeof(char) * (len + 1));
		WcharToChar(lpArchive, ca, len);

		DLL_FUNC_CALL(RGSSGameMainA, hWnd, cs, ca);

		free(cs);
		free(ca);
#else
		DLL_FUNC_CALL(RGSSGameMainA, hWnd, lpScript, lpArchive);
#endif
	}
	else
	{
		if (!DLL_FUNC(RGSSGameMainW))
		{
			return;
		}

#ifndef UNICODE
		len = strlen(lpScript);
		ws = (wchar_t *)malloc(sizeof(wchar_t) * (len + 1));
		memset(ws, 0, sizeof(wchar_t) * (len + 1));
		CharToWchar(lpScript, ws, len);

		len = strlen(lpArchive);
		wa = (wchar_t *)malloc(sizeof(wchar_t) * (len + 1));
		memset(wa, 0, sizeof(wchar_t) * (len + 1));
		CharToWchar(lpArchive, wa, len);

		DLL_FUNC_CALL(RGSSGameMainW, hWnd, ws, wa);

		free(ws);
		free(wa);
#else
		DLL_FUNC_CALL(RGSSGameMainW, hWnd, lpScript, lpArchive);
#endif
	}
}

BOOL RGSSGetBool(LPCSTR lpStr)
{
	if (!DLL_FUNC(RGSSGetBool))
	{
		return FALSE;
	}

	return DLL_FUNC_CALL(RGSSGetBool, lpStr);
}

double RGSSGetDouble(LPCSTR lpStr)
{
	if (!DLL_FUNC(RGSSGetDouble))
	{
		return 0;
	}

	return DLL_FUNC_CALL(RGSSGetDouble, lpStr);
}

int RGSSGetInt(LPCSTR lpStr)
{
	if (!DLL_FUNC(RGSSGetInt))
	{
		return 0;
	}

	return DLL_FUNC_CALL(RGSSGetInt, lpStr);
}

LPTSTR RGSSGetPathWithRTP(LPCTSTR lpRTP)
{
	static char path[MAX_MSG_SIZE] = {0};
	static wchar_t wpath[MAX_MSG_SIZE] = {0};

	size_t len;
#ifdef UNICODE
	char *cr, *cp;
#else
	wchar_t *wr ,*wp;
#endif

	if (RGSS_VERSION_MAJOR(uRgssVersion) == 1)
	{
		if (!DLL_FUNC(RGSSGetPathWithRTPA))
		{
			return NULL;
		}

#ifdef UNICODE
		len = wcslen(lpRTP);
		cr = (char *)malloc(sizeof(char) * (len + 1));
		memset(cr, 0, sizeof(char) * (len + 1));
		WcharToChar(lpRTP, cr, len);

		cp = DLL_FUNC_CALL(RGSSGetPathWithRTPA, cr);

		CharToWchar(cp, (LPWSTR)wpath, MAX_MSG_SIZE);
		free(cr);
		return (LPWSTR)wpath;
#else
		return DLL_FUNC_CALL(RGSSGetPathWithRTPA, lpRTP);
#endif
	}
	else
	{
		if (!DLL_FUNC(RGSSGetPathWithRTPW))
		{
			return NULL;
		}

#ifndef UNICODE
		len = strlen(lpRTP);
		wr = (wchar_t *)malloc(sizeof(wchar_t) * (len + 1));
		memset(wr, 0, sizeof(wchar_t) * (len + 1));
		CharToWchar(lpRTP, wr, len);

		wp = DLL_FUNC_CALL(RGSSGetPathWithRTPW, wr);

		WcharToChar(wp, (LPSTR)path, MAX_MSG_SIZE);
		free(wr);
		return (LPSTR)path;
#else
		return DLL_FUNC_CALL(RGSSGetPathWithRTPW, lpRTP);
#endif
	}
}

LPTSTR RGSSGetRTPPath(UINT uIndex)
{
	static char path[MAX_MSG_SIZE] = {0};
	static wchar_t wpath[MAX_MSG_SIZE] = {0};

#ifdef UNICODE
	char *cp;
#else
	wchar_t *wp;
#endif

	if (RGSS_VERSION_MAJOR(uRgssVersion) == 1)
	{
		if (!DLL_FUNC(RGSSGetRTPPathA))
		{
			return NULL;
		}

#ifdef UNICODE
		cp = DLL_FUNC_CALL(RGSSGetRTPPathA, uIndex);
		CharToWchar(cp, (LPWSTR)wpath, MAX_MSG_SIZE);
		return (LPWSTR)wpath;
#else
		return DLL_FUNC_CALL(RGSSGetRTPPathA, uIndex);
#endif
	}
	else
	{
		if (!DLL_FUNC(RGSSGetRTPPathW))
		{
			return NULL;
		}

#ifndef UNICODE
		wp = DLL_FUNC_CALL(RGSSGetRTPPathW, uIndex);
		WcharToChar(wp, (LPSTR)path, MAX_MSG_SIZE);
		return (LPSTR)path;
#else
		return DLL_FUNC_CALL(RGSSGetRTPPathW, uIndex);
#endif
	}
}

LPSTR RGSSGetStringACP(LPCSTR lpStr)
{
	if (!DLL_FUNC(RGSSGetStringACP))
	{
		return NULL;
	}

	return DLL_FUNC_CALL(RGSSGetStringACP, lpStr);
}

LPWSTR RGSSGetStringUTF16(LPCSTR lpStr)
{
	if (!DLL_FUNC(RGSSGetStringUTF16))
	{
		return NULL;
	}

	return DLL_FUNC_CALL(RGSSGetStringUTF16, lpStr);
}

LPSTR RGSSGetStringUTF8(LPCSTR lpStr)
{
	if (!DLL_FUNC(RGSSGetStringUTF8))
	{
		return NULL;
	}

	return DLL_FUNC_CALL(RGSSGetStringUTF8, lpStr);
}

LPSTR RGSSGetSymbol(LPCSTR lpStr)
{
	if (!DLL_FUNC(RGSSGetSymbol))
	{
		return NULL;
	}

	return DLL_FUNC_CALL(RGSSGetSymbol, lpStr);
}

RGSSTABLE *RGSSGetTable(LPCSTR lpStr)
{
	if (!DLL_FUNC(RGSSGetTable))
	{
		return NULL;
	}

	return DLL_FUNC_CALL(RGSSGetTable, lpStr);
}

void RGSSInitialize(HMODULE hModule)
{
	if (!DLL_FUNC(RGSSInitialize))
	{
		return;
	}

	DLL_FUNC_CALL(RGSSInitialize, hModule);
}

BOOL RGSSSetString(LPCSTR lpName, LPCSTR lpStr, size_t cch)
{
	if (!DLL_FUNC(RGSSSetString))
	{
		return FALSE;
	}

	return DLL_FUNC_CALL(RGSSSetString, lpName, lpStr, cch);
}

BOOL RGSSSetStringACP(LPCSTR lpName, LPCSTR lpStr)
{
	if (!DLL_FUNC(RGSSSetStringACP))
	{
		return FALSE;
	}

	return DLL_FUNC_CALL(RGSSSetStringACP, lpName, lpStr);
}

BOOL RGSSSetStringUTF16(LPCSTR lpName, LPCWSTR lpStr)
{
	if (!DLL_FUNC(RGSSSetStringUTF16))
	{
		return FALSE;
	}

	return DLL_FUNC_CALL(RGSSSetStringUTF16, lpName, lpStr);
}

BOOL RGSSSetStringUTF8(LPCSTR lpName, LPCSTR lpStr)
{
	if (!DLL_FUNC(RGSSSetStringUTF8))
	{
		return FALSE;
	}

	return DLL_FUNC_CALL(RGSSSetStringUTF8, lpName, lpStr);
}

BOOL RGSSSetupFonts()
{
	if (!DLL_FUNC(RGSSSetupFonts))
	{
		return FALSE;
	}

	return DLL_FUNC_CALL(RGSSSetupFonts);
}

BOOL RGSSSetupRTP(LPCTSTR lpIniFile, LPTSTR lpRTPPath, size_t cch)
{
	BOOL ret;
	size_t len;
#ifdef UNICODE
	char *ci, *cr;
#else
	wchar_t *wi, *wr;
#endif

	if (RGSS_VERSION_MAJOR(uRgssVersion) == 1)
	{
		if (!DLL_FUNC(RGSSSetupRTPA))
		{
			return FALSE;
		}

#ifdef UNICODE
		len = wcslen(lpIniFile);
		ci = (char *)malloc(sizeof(char) * (len + 1));
		memset(ci, 0, sizeof(char) * (len + 1));
		WcharToChar(lpIniFile, ci, len);

		cr = (char *)malloc(sizeof(char) * (cch + 1));
		memset(cr, 0, sizeof(char) * (cch + 1));
		WcharToChar(lpRTPPath, cr, cch);

		ret = DLL_FUNC_CALL(RGSSSetupRTPA, ci, cr, cch);

		CharToWchar(cr, lpRTPPath, cch);
		free(ci);
		free(cr);
		return ret;
#else
		return DLL_FUNC_CALL(RGSSSetupRTPA, lpIniFile, lpRTPPath, cch);
#endif
	}
	else
	{
		if (!DLL_FUNC(RGSSSetupRTPW))
		{
			return FALSE;
		}

#ifndef UNICODE
		len = strlen(lpIniFile);
		wi = (wchar_t *)malloc(sizeof(wchar_t) * (len + 1));
		memset(wi, 0, sizeof(wchar_t) * (len + 1));
		CharToWchar(lpIniFile, wi, len);

		wr = (wchar_t *)malloc(sizeof(wchar_t) * (cch + 1));
		memset(wr, 0, sizeof(wchar_t) * (cch + 1));
		CharToWchar(lpRTPPath, wr, cch);

		ret = DLL_FUNC_CALL(RGSSSetupRTPW, wi, wr, cch);

		WcharToChar(wr, lpRTPPath, cch);
		free(wi);
		free(wr);
		return ret;
#else
		return DLL_FUNC_CALL(RGSSSetupRTPW, lpIniFile, lpRTPPath, cch);
#endif
	}
}
