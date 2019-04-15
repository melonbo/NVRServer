/****************************************************************************
 *                                                                           *
 * ctypedef.h -- Basic Linux Type Definitions  Compitable for windows                                *
 *                                                                           *
 * Copyright (c) Sunlink Co, Ltd. All rights reserved.                 *
 *                                                                           *
 ****************************************************************************/
#include <stddef.h>
#include <sys/types.h>
#include <stdint.h>
#ifndef CTYPEDEF_H
#define CTYPEDEF_H

#ifndef NO_STRICT
#ifndef STRICT
#define STRICT 1
#endif
#endif /* NO_STRICT */

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * BASETYPES is defined in ntdef.h if these types are already defined
 */

#ifndef BASETYPES
#define BASETYPES

typedef unsigned long ULONG;
typedef ULONG * PULONG;
typedef unsigned short USHORT;
typedef USHORT * PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR * PUCHAR;
typedef char * PSZ;
typedef uint8_t UINT8;


#endif  /* !BASETYPES */

#define MAX_PATH          260

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

#undef far
#undef near
#undef pascal

#define far
#define near
#if (defined(_STDCALL_SUPPORTED))
#define pascal __stdcall
#else
#define pascal
#endif

#if (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED)
#define CALLBACK    __stdcall
#define WINAPI      __stdcall
#define WINAPIV     __cdecl
#define APIENTRY    WINAPI
#define APIPRIVATE  __stdcall
#define PASCAL      __stdcall
#else
#define CALLBACK
#define WINAPI
#define WINAPIV
#define APIENTRY    WINAPI
#define APIPRIVATE
#define PASCAL      pascal
#endif

#ifdef _M_CEE_PURE
#define WINAPI_INLINE  __clrcall
#else
#define WINAPI_INLINE  WINAPI
#endif

#undef FAR
#undef  NEAR
#define FAR                 far
#define NEAR                near
#ifndef CONST
#define CONST               const
#endif

//typedef unsigned long        DWORD;
typedef unsigned int DWORD;
typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef float FLOAT;
typedef FLOAT* PFLOAT;
//typedef BOOL near *			PBOOL;
//typedef BOOL far *			LPBOOL;
typedef BYTE near * PBYTE;
typedef BYTE far * LPBYTE;
typedef int near * PINT;
typedef int far * LPINT;
typedef WORD near * PWORD;
typedef WORD far * LPWORD;
typedef long far * LPLONG;
typedef DWORD near * PDWORD;
typedef DWORD far * LPDWORD;
typedef void far * LPVOID;
typedef CONST void far * LPCVOID;

typedef int INT;
typedef unsigned int UINT;
typedef unsigned int * PUINT;

//
// Void
//

typedef void *PVOID;
//** typedef void * POINTER_64 PVOID64;


#if (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED)
#define NTAPI __stdcall
#else
#define _cdecl
#define NTAPI
#endif

//
// Define API decoration for direct importing system DLL references.
//

#if !defined(_NTSYSTEM_)
#define NTSYSAPI     DECLSPEC_IMPORT
#define NTSYSCALLAPI DECLSPEC_IMPORT
#else
#define NTSYSAPI
#if defined(_NTDLLBUILD_)
#define NTSYSCALLAPI
#else
#define NTSYSCALLAPI DECLSPEC_ADDRSAFE
#endif

#endif

//
// Basics
//

#ifndef VOID
#define VOID void
typedef char CHAR;
typedef short SHORT;
typedef long LONG;

#endif

//
// UNICODE (Wide Character) types
//

typedef wchar_t WCHAR;

typedef WCHAR *PWCHAR, *LPWCH, *PWCH;
typedef CONST WCHAR *LPCWCH, *PCWCH;
// useing __nullterminated
#define UNALIGNED
typedef WCHAR *NWPSTR, *LPWSTR, *PWSTR;
typedef PWSTR *PZPWSTR;
typedef CONST PWSTR *PCZPWSTR;
typedef WCHAR UNALIGNED *LPUWSTR, *PUWSTR;
typedef CONST WCHAR *LPCWSTR, *PCWSTR;
typedef PCWSTR *PZPCWSTR;
typedef CONST WCHAR UNALIGNED *LPCUWSTR, *PCUWSTR;

//
// ANSI (Multi-byte Character) types
//
typedef CHAR *PCHAR, *LPCH, *PCH;
typedef CONST CHAR *LPCCH, *PCCH;

// useing __nullterminated
typedef CHAR *NPSTR, *LPSTR, *PSTR;
typedef PSTR *PZPSTR;
typedef CONST PSTR *PCZPSTR;
typedef CONST CHAR *LPCSTR, *PCSTR;
typedef PCSTR *PZPCSTR;

//
// Neutral ANSI/UNICODE types and macros
//
#ifdef  UNICODE                     // r_winnt
#ifndef _TCHAR_DEFINED
typedef WCHAR TCHAR, *PTCHAR;
typedef WCHAR TBYTE , *PTBYTE;
#define _TCHAR_DEFINED
#endif /* !_TCHAR_DEFINED */

typedef LPWSTR LPTCH, PTCH;
typedef LPWSTR PTSTR, LPTSTR;
typedef LPCWSTR PCTSTR, LPCTSTR;
typedef LPUWSTR PUTSTR, LPUTSTR;
typedef LPCUWSTR PCUTSTR, LPCUTSTR;
typedef LPWSTR LP;
#define __TEXT(quote) L##quote      // r_winnt
#else   /* UNICODE */               // r_winnt
#ifndef _TCHAR_DEFINED
typedef char TCHAR, *PTCHAR;
typedef unsigned char TBYTE, *PTBYTE;
#define _TCHAR_DEFINED
#endif /* !_TCHAR_DEFINED */

typedef LPSTR LPTCH, PTCH;
typedef LPSTR PTSTR, LPTSTR, PUTSTR, LPUTSTR;
typedef LPCSTR PCTSTR, LPCTSTR, PCUTSTR, LPCUTSTR;
#define __TEXT(quote) quote         // r_winnt
#endif /* UNICODE */                // r_winnt
#define TEXT(quote) __TEXT(quote)   // r_winnt
typedef SHORT *PSHORT;
typedef LONG *PLONG;

#ifdef STRICT
typedef void *HANDLE;
#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
#else
typedef PVOID HANDLE;
#define DECLARE_HANDLE(name) typedef HANDLE name
#endif
typedef HANDLE *PHANDLE;

//
// Flag (bit) fields
//

typedef BYTE FCHAR;
typedef WORD FSHORT;
typedef DWORD FLONG;

// Component Object Model defines, and macros

#ifndef _HRESULT_DEFINED
#define _HRESULT_DEFINED
typedef LONG HRESULT;

#endif // !_HRESULT_DEFINED
#ifdef __cplusplus
#define EXTERN_C    extern "C"
#else
#define EXTERN_C    extern
#endif

#if defined(_WIN32) || defined(_MPPC_)

// Win32 doesn't support __export

#ifdef _68K_
#define STDMETHODCALLTYPE       __cdecl
#else
#define STDMETHODCALLTYPE       __stdcall
#endif
#define STDMETHODVCALLTYPE      __cdecl

#define STDAPICALLTYPE          __stdcall
#define STDAPIVCALLTYPE         __cdecl

#else

#define STDMETHODCALLTYPE       __export __stdcall
#define STDMETHODVCALLTYPE      __export __cdecl

#define STDAPICALLTYPE          __export __stdcall
#define STDAPIVCALLTYPE         __export __cdecl

#endif

#define STDAPI                  EXTERN_C HRESULT STDAPICALLTYPE
#define STDAPI_(type)           EXTERN_C type STDAPICALLTYPE

#define STDMETHODIMP            HRESULT STDMETHODCALLTYPE
#define STDMETHODIMP_(type)     type STDMETHODCALLTYPE

// The 'V' versions allow Variable Argument lists.

#define STDAPIV                 EXTERN_C HRESULT STDAPIVCALLTYPE
#define STDAPIV_(type)          EXTERN_C type STDAPIVCALLTYPE

#define STDMETHODIMPV           HRESULT STDMETHODVCALLTYPE
#define STDMETHODIMPV_(type)    type STDMETHODVCALLTYPE

typedef char CCHAR;
typedef DWORD LCID;
typedef PDWORD PLCID;
typedef WORD LANGID;
#define APPLICATION_ERROR_MASK       0x20000000
#define ERROR_SEVERITY_SUCCESS       0x00000000
#define ERROR_SEVERITY_INFORMATIONAL 0x40000000
#define ERROR_SEVERITY_WARNING       0x80000000
#define ERROR_SEVERITY_ERROR         0xC0000000

//
// _M_IX86 included so that EM CONTEXT structure compiles with
// x86 programs. *** TBD should this be for all architectures?
//

//
// 16 byte aligned type for 128 bit floats
//


//
// __int64 is only supported by 2.0 and later midl.
// __midl is set by the 2.0 midl and not by 1.0 midl.
//

#define _ULONGLONG_
#if (!defined (_MAC) && (!defined(MIDL_PASS) || defined(__midl)) && (!defined(_M_IX86) || (defined(_INTEGRAL_MAX_BITS) && _INTEGRAL_MAX_BITS >= 64)))
typedef long long LONGLONG;
typedef unsigned long long ULONGLONG;

#define MAXLONGLONG                      (0x7fffffffffffffff)
#else

#if defined(_MAC) && defined(_MAC_INT_64)
typedef __int64 LONGLONG;
typedef unsigned __int64 ULONGLONG;

#define MAXLONGLONG                      (0x7fffffffffffffff)
#else
typedef double LONGLONG;
typedef double ULONGLONG;
#endif //_MAC and int64
#endif

typedef LONGLONG *PLONGLONG;
typedef ULONGLONG *PULONGLONG;

// Update Sequence Number

typedef LONGLONG USN;





// end_ntminiport end_ntndis end_ntminitape


/* Types use for passing & returning polymorphic values */

typedef unsigned int UINT_PTR, *PINT_PTR;
typedef long LONG_PTR, *PLONG_PTR;

typedef UINT_PTR WPARAM;
typedef LONG_PTR LPARAM;
typedef LONG_PTR LRESULT;

#ifndef NOMINMAX

//#ifndef max
//#define max(a,b)            (((a) > (b)) ? (a) : (b))
//#endif

//#ifndef min
//#define min(a,b)            (((a) < (b)) ? (a) : (b))
//#endif

#endif  /* NOMINMAX */
typedef DWORD DWORD_PTR, *PDWORD_PTR;


#define MAKEWORD(a, b)      ((WORD)(((BYTE)((DWORD_PTR)(a) & 0xff)) | ((WORD)((BYTE)((DWORD_PTR)(b) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)((DWORD_PTR)(a) & 0xffff)) | ((DWORD)((WORD)((DWORD_PTR)(b) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)((DWORD_PTR)(l) & 0xffff))
#define HIWORD(l)           ((WORD)((DWORD_PTR)(l) >> 16))
#define LOBYTE(w)           ((BYTE)((DWORD_PTR)(w) & 0xff))
#define HIBYTE(w)           ((BYTE)((DWORD_PTR)(w) >> 8))

#ifndef WIN_INTERNAL
DECLARE_HANDLE (HWND)
;
DECLARE_HANDLE (HHOOK)
;
#ifdef WINABLE
DECLARE_HANDLE (HEVENT);
#endif
#endif

typedef WORD ATOM;

typedef HANDLE NEAR *SPHANDLE;
typedef HANDLE FAR *LPHANDLE;
typedef HANDLE HGLOBAL;
typedef HANDLE HLOCAL;
typedef HANDLE GLOBALHANDLE;
typedef HANDLE LOCALHANDLE;

#ifdef _WIN64
typedef INT_PTR (FAR WINAPI *FARPROC)();
typedef INT_PTR (NEAR WINAPI *NEARPROC)();
typedef INT_PTR (WINAPI *PROC)();
#else
typedef int (FAR WINAPI *FARPROC)();
typedef int (NEAR WINAPI *NEARPROC)();
typedef int (WINAPI *PROC)();
#endif  // _WIN64
#ifdef STRICT
typedef void NEAR* HGDIOBJ;
#else
DECLARE_HANDLE(HGDIOBJ);
#endif

DECLARE_HANDLE(HKEY)
;
typedef HKEY *PHKEY;

DECLARE_HANDLE(HACCEL)
;
DECLARE_HANDLE(HBITMAP)
;
DECLARE_HANDLE(HBRUSH)
;
DECLARE_HANDLE(HCOLORSPACE)
;
DECLARE_HANDLE(HDC)
;
DECLARE_HANDLE(HGLRC)
; // OpenGL
DECLARE_HANDLE(HDESK)
;
DECLARE_HANDLE(HENHMETAFILE)
;
DECLARE_HANDLE(HFONT)
;
DECLARE_HANDLE(HICON)
;
DECLARE_HANDLE(HMENU)
;
DECLARE_HANDLE(HMETAFILE)
;
DECLARE_HANDLE(HINSTANCE)
;
typedef HINSTANCE HMODULE; /* HMODULEs can be used in place of HINSTANCEs */
DECLARE_HANDLE(HPALETTE)
;
DECLARE_HANDLE(HPEN)
;
DECLARE_HANDLE(HRGN)
;
DECLARE_HANDLE(HRSRC)
;
DECLARE_HANDLE(HSTR)
;
DECLARE_HANDLE(HTASK)
;
DECLARE_HANDLE(HWINSTA)
;
DECLARE_HANDLE(HKL)
;

DECLARE_HANDLE(HMONITOR)
;
DECLARE_HANDLE(HWINEVENTHOOK)
;
DECLARE_HANDLE(HUMPD)
;

typedef int HFILE;
typedef HICON HCURSOR; /* HICONs & HCURSORs are polymorphic */

typedef DWORD COLORREF;
typedef DWORD *LPCOLORREF;

#define HFILE_ERROR ((HFILE)-1)

//typedef struct tagRECT
//{
//	LONG left;
//	LONG top;
//	LONG right;
//	LONG bottom;
//} RECT, *PRECT, NEAR *NPRECT, FAR *LPRECT;
//
//typedef const RECT FAR* LPCRECT;

//typedef struct _RECTL /* rcl */
//{
//	LONG left;
//	LONG top;
//	LONG right;
//	LONG bottom;
//} RECTL, *PRECTL, *LPRECTL;

//typedef const RECTL FAR* LPCRECTL;

//typedef struct tagPOINT
//{
//	LONG x;
//	LONG y;
//} POINT, *PPOINT, NEAR *NPPOINT, FAR *LPPOINT;

//typedef struct _POINTL /* ptl  */
//{
//	LONG x;
//	LONG y;
//} POINTL, *PPOINTL;

//typedef struct tagSIZE
//{
//	LONG cx;
//	LONG cy;
//} SIZE, *PSIZE, *LPSIZE;
//
//typedef SIZE SIZEL;
//typedef SIZE *PSIZEL, *LPSIZEL;

//typedef struct tagPOINTS
//{
//	SHORT x;
//	SHORT y;
//} POINTS, *PPOINTS, *LPPOINTS;

//
//  File System time stamps are represented with the following structure:
//

//typedef struct _FILETIME
//{
//	DWORD dwLowDateTime;
//	DWORD dwHighDateTime;
//} FILETIME, *PFILETIME, *LPFILETIME;
#define _FILETIME_

/* mode selections for the device mode function */
#define DM_UPDATE           1
#define DM_COPY             2
#define DM_PROMPT           4
#define DM_MODIFY           8

#define DM_IN_BUFFER        DM_MODIFY
#define DM_IN_PROMPT        DM_PROMPT
#define DM_OUT_BUFFER       DM_COPY
#define DM_OUT_DEFAULT      DM_UPDATE

/* device capabilities indices */
#define DC_FIELDS           1
#define DC_PAPERS           2
#define DC_PAPERSIZE        3
#define DC_MINEXTENT        4
#define DC_MAXEXTENT        5
#define DC_BINS             6
#define DC_DUPLEX           7
#define DC_SIZE             8
#define DC_EXTRA            9
#define DC_VERSION          10
#define DC_DRIVER           11
#define DC_BINNAMES         12
#define DC_ENUMRESOLUTIONS  13
#define DC_FILEDEPENDENCIES 14
#define DC_TRUETYPE         15
#define DC_PAPERNAMES       16
#define DC_ORIENTATION      17
#define DC_COPIES           18

#ifdef __cplusplus
}
#endif

#endif /* _ctypedef_ */

