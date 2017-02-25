#ifndef _PLAYLISTSHELL_F7543B07_2570_4BBA_8E2D_936E4298AAF6_
#define _PLAYLISTSHELL_F7543B07_2570_4BBA_8E2D_936E4298AAF6_
#pragma once

#include "resource.h"
#include "FileInfotipImpl.h"
#include "Parser/PlaylistParser.h"


class ATL_NO_VTABLE CPlaylistShell : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPlaylistShell,&CLSID_PlaylistShell>,
	public IDispatchImpl<IPlaylistShell, &IID_IPlaylistShell, &LIBID_PLSINFOTIPLib>,
	public IFileInfotipImpl
{
public:
	CPlaylistShell(){}
	~CPlaylistShell(){}

	BEGIN_COM_MAP(CPlaylistShell)
		COM_INTERFACE_ENTRY(IPlaylistShell)
			COM_INTERFACE_ENTRY(IQueryInfo)
			COM_INTERFACE_ENTRY(IPersistFile)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_REGISTRY_RESOURCEID(IDR_PlaylistShell)
	DECLARE_PROTECT_FINAL_CONSTRUCT()



	CString GetFileInfotipImpl(const CString& szFile)
	{	
		C_PlaylistParser pls;
		pls.process(szFile);
	return pls.infotip;
	}


};



#endif//_PLAYLISTSHELL_F7543B07_2570_4BBA_8E2D_936E4298AAF6_
