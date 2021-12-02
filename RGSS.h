#ifndef RGSS_H
#define RGSS_H

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include <stdlib.h>

#if defined(_MSC_VER)
#define inline __inline
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define RGSS_VERSION_MAJOR(version) \
	(((version) & 0xF00) >> 8)

#define RGSS_VERSION_MINOR(version) \
	(((version) & 0x0F0) >> 4)

#define RGSS_VERSION_PATCH(version) \
	((version) & 0x00F)

typedef struct tagRGSSTABLE
{
	int xs;
	int ys;
	int zs;
	WORD *data;
} RGSSTABLE;

void RGSSAddRTPPath(LPCTSTR lpPath);
void RGSSAudioFinalize();
BOOL RGSSAudioInitialize(HWND hWnd);
void RGSSClearRTPPath();
LPTSTR RGSSErrorMessage();
LPTSTR RGSSErrorType();
int RGSSEval(LPCSTR lpStr);
void RGSSFinalize();
void RGSSGC();
void RGSSGameMain(HWND hWnd, LPCTSTR lpScript, LPCTSTR lpArchive);
BOOL RGSSGetBool(LPCSTR lpStr);
double RGSSGetDouble(LPCSTR lpStr);
int RGSSGetInt(LPCSTR lpStr);
LPTSTR RGSSGetPathWithRTP(LPCTSTR lpRTP);
LPTSTR RGSSGetRTPPath(UINT uIndex);
LPSTR RGSSGetStringACP(LPCSTR lpStr);
LPWSTR RGSSGetStringUTF16(LPCSTR lpStr);
LPSTR RGSSGetStringUTF8(LPCSTR lpStr);
LPSTR RGSSGetSymbol(LPCSTR lpStr);
RGSSTABLE *RGSSGetTable(LPCSTR lpStr);
void RGSSInitialize(HMODULE hModule);
BOOL RGSSSetString(LPCSTR lpName, LPCSTR lpStr, size_t cch);
BOOL RGSSSetStringACP(LPCSTR lpName, LPCSTR lpStr);
BOOL RGSSSetStringUTF16(LPCSTR lpName, LPCWSTR lpStr);
BOOL RGSSSetStringUTF8(LPCSTR lpName, LPCSTR lpStr);
BOOL RGSSSetupFonts();
BOOL RGSSSetupRTP(LPCTSTR lpIniFile, LPTSTR lpRTPPath, size_t cch);

BOOL RGSSLibraryInitialize(LPTSTR lpLibFileName, LPTSTR pPath);
void RGSSLibraryFinalize();
HMODULE RGSSGetHandle();
UINT RGSSGetVersion(LPTSTR lpLibFileName);

#ifdef __cplusplus
}
#endif

#endif /* RGSS_H */