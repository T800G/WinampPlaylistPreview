#ifndef _IINFOTIPIMPL_317E3CC2_C9EC_4312_8995_8866CE136CB0_
#define _IINFOTIPIMPL_317E3CC2_C9EC_4312_8995_8866CE136CB0_
#pragma once
#ifndef _UNICODE
#error IFileInfotipImpl is Unicode-only class
#endif
#if (_WTL_VER < 0x0800)
#error This project requires ATL/WTL
#endif

#include <atlmisc.h>
#include <comdef.h>
#include <AtlCom.h>
#include <ShlObj.h>

//////////////////////////////////////////////////
//implementation of infotip interfaces

class ATL_NO_VTABLE IFileInfotipImpl: public IPersistFile, public IQueryInfo
{
public:
	IFileInfotipImpl(){ if (FAILED(SHGetMalloc(&m_pAlloc))) m_pAlloc=NULL; }
	virtual ~IFileInfotipImpl(){ m_pAlloc->Release(); }


    // IUnknown
	//
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) = 0;
	_ATL_DEBUG_ADDREF_RELEASE_IMPL(IFileInfotipImpl)

	// IPersistFile
	//
	STDMETHOD(GetClassID)(LPCLSID){return E_NOTIMPL;}
	STDMETHOD(IsDirty)(VOID){return E_NOTIMPL;}
	STDMETHOD(Save)(LPCOLESTR, BOOL){return E_NOTIMPL;}
	STDMETHOD(SaveCompleted)(LPCOLESTR){return E_NOTIMPL;}
	STDMETHOD(GetCurFile)(LPOLESTR FAR*){return E_NOTIMPL;}
	STDMETHOD(Load)(LPCOLESTR wszFile, DWORD dwMode)
	{
		m_szFile=(WCHAR*)wszFile;//load filename
	return S_OK;	
	}

	// IQueryInfo
	//
	STDMETHOD(GetInfoFlags)(LPDWORD pdwFlags){*pdwFlags = 0;return E_NOTIMPL;}//dwFlags is currently unused

	STDMETHOD(GetInfoTip)(DWORD dwFlags, LPWSTR *ppwszTip)
	{							
		try
		{
			CString tip=GetFileInfotipImpl(m_szFile);
			if (tip.IsEmpty()) return S_FALSE;

			*ppwszTip = (WCHAR*) m_pAlloc->Alloc( (tip.GetLength()+1)*sizeof(WCHAR) );
			if (*ppwszTip) wcscpy_s(*ppwszTip, tip.GetLength()+1, tip);
			else return S_FALSE;
		return S_OK;
		}
		catch (...){ /*ATLTRACE("ERROR!\nException in IFileInfotipImpl");*/ return S_FALSE;}

	return S_FALSE;
	}

	
	virtual CString GetFileInfotipImpl(const CString& szFile);//must be implemented in inherited class

private:
	LPMALLOC m_pAlloc;
	CString m_szFile;
};



#endif//_IINFOTIPIMPL_317E3CC2_C9EC_4312_8995_8866CE136CB0_
