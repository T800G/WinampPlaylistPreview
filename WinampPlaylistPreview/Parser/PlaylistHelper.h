#ifndef _PLAYLISTHELPER_982F306B_6C41_4522_9B8F_F038C7C8563E_
#define _PLAYLISTHELPER_982F306B_6C41_4522_9B8F_F038C7C8563E_
#pragma once
#ifndef _UNICODE
	#error C_SplitPath is UNICODE-only class
#endif
#include <atlmisc.h>
#include <math.h>

class C_SplitPath
{
public:
    C_SplitPath(LPCTSTR lpszPath = NULL){ SplitPathInitialize();if (lpszPath) Split(lpszPath);}

    BOOL Split(LPCTSTR lpszPath )
		{
			SplitPathInitialize();
			if (lpszPath == NULL) return FALSE;
			SplPstatus=_wsplitpath_s(lpszPath, drive0, _MAX_DRIVE, dir0, _MAX_DIR, fname0, _MAX_FNAME, ext0, _MAX_EXT);
			fullpath=lpszPath;
			drive=drive0;
			dir=dir0;
			filename=fname0;
			ext_nodot=ext=ext0;
			ext_nodot.Delete(0,1);

			filetitle+=filename;
			filetitle+=ext;
		return ((SplPstatus!=EINVAL) && (SplPstatus!=ERANGE));
		}

	CString filetitle,fullpath, drive, dir, filename, ext, ext_nodot;

	errno_t SplPstatus;

private:
	void SplitPathInitialize()
		{
			wmemset(drive0, 0, _MAX_DRIVE);//init
			wmemset(dir0, 0, _MAX_DIR);
			wmemset(fname0, 0, _MAX_FNAME);
			wmemset(ext0, 0, _MAX_EXT);
			SplPstatus=NULL;
			fullpath.Empty();
			drive.Empty();
			dir.Empty();
			filename.Empty();
			ext.Empty();
			ext_nodot.Empty();
			filetitle.Empty();
		}

    TCHAR drive0[_MAX_DRIVE];
    TCHAR dir0[_MAX_DIR];
    TCHAR fname0[_MAX_FNAME];
    TCHAR ext0[_MAX_EXT];
};


#endif//_PLAYLISTHELPER_982F306B_6C41_4522_9B8F_F038C7C8563E_
