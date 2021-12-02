// Player.cpp : Defines the entry point for the application.
//

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Library Header Files
#include "RGSS.h"

// Resource Header Files
#include "resource.h"

// Make sure MSVC can recognize inline keyword in C
#if defined(_MSC_VER)
#define inline __inline
#endif

#define MAX_STR_SIZE 1024

static const TCHAR szWndClass[] = __T("RGSS Player");

// Type Declarations
enum
{
	OPTION_WINDOW = 0x01,
    OPTION_CONSOLE = 0x02,
    OPTION_TEST = 0x04,
    OPTION_BTEST = 0x08,
	OPTION_DEBUG = 0x10
};

typedef struct tagGAMECONTEXT
{
	TCHAR szFileName[MAX_STR_SIZE];	// The path and filename for the running executable file
	TCHAR szIni[MAX_STR_SIZE];			// The path and filename for initialization file
	TCHAR szArchive[MAX_STR_SIZE];		// The path and filename for data archive file
	TCHAR szRTP[MAX_STR_SIZE];			// The name of RTP
	TCHAR szRTPPath[MAX_STR_SIZE];		// The path for RTP
	TCHAR szLibrary[MAX_STR_SIZE];		// The path and filenaem for RGSS library
	TCHAR szTitle[MAX_STR_SIZE];		// The title bar text
	TCHAR szScripts[MAX_STR_SIZE];		// The path and filename for game scripts
	UINT fuRgssVersion;					// The version of the current RGSS library
	UINT fuOption;						// The option from command line
	HINSTANCE hInstance;				// The handle of the current instance
	HWND hWnd;							// The handle of the window for game
} GAMECONTEXT;

// Forward declarations of functions included in this code module:
BOOL GameInit(GAMECONTEXT *ctx, HINSTANCE hInstance, LPTSTR lpCmdLine);
void GameMain(GAMECONTEXT *ctx);

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR lpCmdLine,
					   int nCmdShow)
{
	GAMECONTEXT ctx = {0};

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);

	GameInit(&ctx, hInstance, lpCmdLine);
	GameMain(&ctx);

	return 0;
}

static inline BOOL CmdLineMatchAndShift(LPTSTR *ppSrc, LPTSTR pTgt)
{
	const DWORD cdwLen = _tcslen(pTgt);
	if (!_tcsncmp(*ppSrc, pTgt, cdwLen))
	{
		*ppSrc += cdwLen;
		return TRUE;
	}
	return FALSE;
}

static inline BOOL IsStringEqual(LPTSTR pStr1, LPTSTR pStr2)
{
	return !_tcscmp(pStr1, pStr2);
}

static inline BOOL IsStringEmpty(LPTSTR pStr)
{
	return _tcscmp(pStr, __T("")) == 0;
}

static void GetErrorString(DWORD dwError, LPTSTR pErrorStr, UINT uSize, ...)
{
	va_list args;
	va_start(args, uSize);
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ARGUMENT_ARRAY,
		NULL, dwError, LANG_USER_DEFAULT, pErrorStr, uSize, &args);
}

static UINT ParseCmdLine(LPTSTR lpCmdLine)
{
	UINT fuOption = OPTION_WINDOW;
	while (*lpCmdLine != __T('\0'))
	{
		if (CmdLineMatchAndShift(&lpCmdLine, __T("console")))
		{
			fuOption |= OPTION_CONSOLE;
		}
		if (CmdLineMatchAndShift(&lpCmdLine, __T("test")))
		{
			fuOption |= OPTION_TEST;
		}
		if (CmdLineMatchAndShift(&lpCmdLine, __T("btest")))
		{
			fuOption |= OPTION_BTEST;
		}
		if (CmdLineMatchAndShift(&lpCmdLine, __T("debug")))
		{
			fuOption |= OPTION_DEBUG;
		}
		if (*lpCmdLine == __T(' '))
		{
			++lpCmdLine;
		}
	}

	return fuOption;
}

static void GetFileName(LPTSTR pFilename)
{
	GetModuleFileName(NULL, pFilename, MAX_STR_SIZE);
}

static BOOL LoadInitFile(GAMECONTEXT *ctx)
{
	LPTSTR pStr;

	_tcsncpy(ctx->szIni, ctx->szFileName, MAX_STR_SIZE);
	if (!(pStr = _tcsrchr(ctx->szIni, __T('.'))))
	{
		return FALSE;
	}
	*pStr = __T('\0');
	_tcsncat(ctx->szIni, __T(".ini"), MAX_STR_SIZE - _tcslen(ctx->szIni));
	if (GetFileAttributes(ctx->szIni) == INVALID_FILE_ATTRIBUTES)
	{
		return FALSE;
	}

    GetPrivateProfileString(__T("Game"), __T("RTP"), __T(""),
		ctx->szRTP, MAX_STR_SIZE, ctx->szIni);
	GetPrivateProfileString(__T("Game"), __T("Library"), __T(""),
		ctx->szLibrary, MAX_STR_SIZE, ctx->szIni);
	GetPrivateProfileString(__T("Game"), __T("Title"), __T("Untitled"),
		ctx->szTitle, MAX_STR_SIZE, ctx->szIni);
    GetPrivateProfileString(__T("Game"), __T("Scripts"), __T(""),
		ctx->szScripts, MAX_STR_SIZE, ctx->szIni);

	return TRUE;
}

static BOOL SetGameDir(LPTSTR pFileName)
{
	LPTSTR pStr;

	if (!(pStr = _tcsrchr(pFileName, __T('\\'))))
	{
		return FALSE;
	}
	*pStr = __T('\0');
	SetCurrentDirectory(pFileName);
	*pStr = __T('\\');

	return TRUE;
}

static void GetArchiveName(GAMECONTEXT *ctx)
{
	static const TCHAR *aRGSSArcExts[] = {
		__T(".rgssad"),
		__T(".rgss2a"),
		__T(".rgss3a"),
		NULL
	};

	LPTSTR pStr;

	if (!ctx->fuRgssVersion)
	{
		return;
	}

	_tcsncpy(ctx->szArchive, ctx->szFileName, MAX_STR_SIZE);
	if (!(pStr = _tcsrchr(ctx->szArchive, __T('.'))))
	{
		return;
	}

	*pStr = __T('\0');
	_tcsncat(ctx->szArchive,
		aRGSSArcExts[RGSS_VERSION_MAJOR(ctx->fuRgssVersion) - 1],
		MAX_STR_SIZE - _tcslen(ctx->szArchive));
	if (GetFileAttributes(ctx->szArchive) == INVALID_FILE_ATTRIBUTES)
	{
		_tcscpy(ctx->szArchive, __T(""));
	}
}

static void GetRTPPath(GAMECONTEXT *ctx)
{
    static const TCHAR *aRGSSSubKeys[] = {
		NULL,
		__T("Software\\Enterbrain\\RGSS2\\RTP"),
		__T("Software\\Enterbrain\\RGSS3\\RTP"),
		NULL
	};

	DWORD dwType;
    HKEY hKey;
    DWORD cbData;

	if (RGSS_VERSION_MAJOR(ctx->fuRgssVersion) == 1)
	{
		return;
	}

    RegOpenKeyEx(HKEY_LOCAL_MACHINE, aRGSSSubKeys[RGSS_VERSION_MAJOR(ctx->fuRgssVersion) - 1], 0, KEY_READ, &hKey);
    if (!IsStringEmpty(ctx->szRTP))
    {
		cbData = MAX_STR_SIZE - 1;
		memset(ctx->szRTPPath, 0, sizeof(TCHAR) * MAX_STR_SIZE);
        RegQueryValueEx(hKey, ctx->szRTP, 0, &dwType, (LPBYTE)ctx->szRTPPath, &cbData);
        if (dwType != REG_SZ)
		{
            memset(ctx->szRTPPath, 0, sizeof(TCHAR) * MAX_STR_SIZE);
		}
        if (*(ctx->szRTPPath + (sizeof(TCHAR) * (_tcslen(ctx->szRTPPath) - 1))) == __T('\\'))
		{
			*(ctx->szRTPPath + (sizeof(TCHAR) * (_tcslen(ctx->szRTPPath) - 1))) = __T('\0');
		}
    }
    RegCloseKey(hKey);
}

static ATOM RegisterWndClass(HINSTANCE hInstance)
{
	WNDCLASS wc;

	wc.style = CS_DBLCLKS;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PLAYER));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szWndClass;

	return RegisterClass(&wc);
}

static BOOL InitInstance(GAMECONTEXT *ctx)
{
	RECT rc;
	int iWidth, iHeight;
	LONG cx, cy, x, y;
	HDC hDc;
	HBRUSH hBr;

	ctx->hWnd = CreateWindowEx(WS_EX_WINDOWEDGE, szWndClass, ctx->szTitle,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, NULL, NULL, ctx->hInstance, NULL);

	if (!ctx->hWnd)
	{
		return FALSE;
	}

	if (RGSS_VERSION_MAJOR(ctx->fuRgssVersion) == 1)
	{
		SetRect(&rc, 0, 0, 640, 480);
	}
	else
	{
		SetRect(&rc, 0, 0, 544, 416);
	}

	AdjustWindowRectEx(&rc, GetWindowLong(ctx->hWnd, GWL_STYLE), FALSE, GetWindowLong(ctx->hWnd, GWL_EXSTYLE));

	iWidth = GetSystemMetrics(SM_CXMAXIMIZED) - GetSystemMetrics(SM_CXSIZEFRAME) * 2;
	iHeight = GetSystemMetrics(SM_CYMAXIMIZED) - GetSystemMetrics(SM_CYSIZEFRAME) * 2;
	cx = rc.right - rc.left;
    cy = rc.bottom - rc.top;
    x = (iWidth - cx) / 2;
    y = (iHeight - cy) / 2;
    SetWindowPos(ctx->hWnd, NULL, x, y, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);

    if ((RGSS_VERSION_MAJOR(ctx->fuRgssVersion) == 3) && (ctx->fuOption & OPTION_CONSOLE) && AllocConsole())
    {
        SetConsoleTitle(__T("RGSS Console"));
        freopen("CONOUT$", "w", stdout);
    }

	ShowWindow(ctx->hWnd, SW_SHOW);

	hDc = GetDC(ctx->hWnd);
    hBr = (HBRUSH)(GetStockObject(BLACK_BRUSH));
    FillRect(hDc, &rc, hBr);
    ReleaseDC(ctx->hWnd, hDc);

	return TRUE;
}

static BOOL IsWindow2kOrGreater()
{
	OSVERSIONINFO vi;

	vi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&vi);
	return vi.dwMajorVersion > 4;
}

BOOL GameInit(GAMECONTEXT *ctx, HINSTANCE hInstance, LPTSTR lpCmdLine)
{
	DWORD dwTime;
	MSG msg;

	ctx->hInstance = hInstance;
	ctx->fuOption = ParseCmdLine(lpCmdLine);

	GetFileName(ctx->szFileName);

	if (!LoadInitFile(ctx))
	{
		MessageBox(NULL, __T("No initialization file found."), ctx->szTitle, MB_ICONHAND);
		return FALSE;
	}

	if (!SetGameDir(ctx->szFileName))
	{
		return FALSE;
	}

	ctx->fuRgssVersion = RGSSGetVersion(ctx->szLibrary);
	if (!ctx->fuRgssVersion)
	{
		return FALSE;
	}

	GetArchiveName(ctx);
    GetRTPPath(ctx);

	if (!RegisterWndClass(ctx->hInstance))
	{
		MessageBox(NULL, __T("Cannot register the window class."), ctx->szTitle, MB_ICONHAND);
		return FALSE;
	}

	if (!InitInstance(ctx))
	{
		MessageBox(NULL, __T("Cannot create the window."), ctx->szTitle, MB_ICONHAND);
		return FALSE;
	}
	
    dwTime = GetTickCount();
    while (GetTickCount() - dwTime < 200)
    {
        if (PeekMessage(&msg, NULL, 0, 0, 0))
        {
            if (!GetMessage(&msg, NULL, 0, 0))
			{
                return FALSE;
			}
            DispatchMessage(&msg);
        }
    }

	return TRUE;
}

void GameMain(GAMECONTEXT *ctx)
{
	static TCHAR szErrMessage[MAX_STR_SIZE];
	int iLangShift; // 0 EN; 100 JP; 200 CN;

	if (!IsWindow2kOrGreater())
	{
		MessageBox(ctx->hWnd, __T("Cannot run on this version of Windows."), ctx->szTitle, MB_ICONHAND);
		return;
	}

	if (!RGSSLibraryInitialize(ctx->szLibrary, ctx->szRTPPath))
	{
		DWORD dwError = GetLastError();
		if ( dwError == ERROR_MOD_NOT_FOUND)
		{
			GetErrorString(STG_E_FILENOTFOUND, szErrMessage, MAX_STR_SIZE, ctx->szLibrary);
		}
		else
		{
			GetErrorString(dwError, szErrMessage, MAX_STR_SIZE);
		}

		MessageBox(ctx->hWnd, (LPCTSTR)szErrMessage, ctx->szTitle, MB_ICONHAND);
		return;
	}

	if (PRIMARYLANGID(GetUserDefaultUILanguage) == LANG_JAPANESE)
	{
		iLangShift = 100;
	}
	else if (PRIMARYLANGID(GetUserDefaultUILanguage) == LANG_CHINESE)
	{
		iLangShift = 200;
	}
	else
	{
		iLangShift = 0;
	}

	if (!RGSSSetupRTP(ctx->szIni, ctx->szRTPPath, MAX_STR_SIZE))
	{
		TCHAR szBuffer[MAX_STR_SIZE];
		LoadString(ctx->hInstance, IDS_ERROR_NO_RTP + iLangShift, szBuffer, MAX_STR_SIZE);
#ifdef UNICODE
        swprintf(szErrMessage, MAX_STR_SIZE, szBuffer, ctx->szRTPPath);
#else
		sprintf(szErrMessage, szBuffer, ctx->szRTPPath);
#endif
        MessageBox(ctx->hWnd, (LPCTSTR)szErrMessage, ctx->szTitle, MB_ICONHAND);
	}

	if (RGSS_VERSION_MAJOR(ctx->fuRgssVersion) > 1)
	{
		RGSSSetupFonts();
	}

	RGSSInitialize(RGSSGetHandle());

	if (RGSS_VERSION_MAJOR(ctx->fuRgssVersion) == 1)
	{
		if (ctx->fuOption & OPTION_BTEST)
		{
			_tcscpy(ctx->szArchive, __T(""));
			RGSSEval("$DEBUG = true");
			RGSSEval("$BTEST = true");
		}
		else
		{
			if (ctx->fuOption & OPTION_DEBUG)
			{
				RGSSEval("$DEBUG = true");
			}
			RGSSEval("$TEST = false");
		}	
	}
	else
	{
		if (ctx->fuOption & (OPTION_TEST | OPTION_BTEST))
		{
			_tcscpy(ctx->szArchive, __T(""));
			RGSSEval("$TEST = true");
			if (ctx->fuOption & OPTION_BTEST)
			{
				RGSSEval("$BTEST = true");
			}
		}
		else
		{
			RGSSEval("$TEST = false");
		}
	}

	// Main Loop
	RGSSGameMain(ctx->hWnd, ctx->szScripts, ctx->szArchive);

	RGSSLibraryFinalize();
}