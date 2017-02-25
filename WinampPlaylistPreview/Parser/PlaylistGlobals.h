#ifndef _8AFCE047_75EC_4dab_B939_39F51112B59F_
#define _8AFCE047_75EC_4dab_B939_39F51112B59F_
#pragma once
#include <atlmisc.h>

#define VISTA_INFOTIP_LIMIT 900 //about 65 chars per row, 15 lines + 5 chars in 16th line

enum PLAYLIST_TYPE {NOTPLS, M3U, M3UEXT, PLS, WPL, ASX, CUE, PLC};
enum PLAYLIST_STATUSCODE {NOCODE, NOVALID_VER, PSTC_EXC_ERROR, PSTC_NOSONGS, PSTC_NOPLAYTIME};
enum ENCODING_TYPE {PLS_ANSI, PLS_UNICODE, PLS_UTF8, PLS_UNICODE_LE, PLS_UNICODE_BE};


bool findNoCase(CString fns, LPCTSTR fnc);//helper/global

class _plsEntry 
{public:
	CString title, file;
	int index;//1-based
	int tracklength;

	std::string stitle;//helpers
	std::string sfile;
	_plsEntry(){init();}
	void init(){tracklength=index=-2; title.Empty(); file.Empty(); stitle.clear(); sfile.clear();}
	void std2CStr(){title+=stitle.c_str();file+=sfile.c_str();}
	void init_tracklength(){ tracklength=-2;}
};

#endif//_8AFCE047_75EC_4dab_B939_39F51112B59F_
