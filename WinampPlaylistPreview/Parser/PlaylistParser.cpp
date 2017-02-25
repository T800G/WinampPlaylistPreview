#include "stdafx.h"
#include <Shlwapi.h>
#pragma comment( lib, "shlwapi.lib")
#include "ConfigFile.h"
#include "PlaylistGlobals.h"
#include "PlaylistParser.h"

bool findNoCase(CString fns, LPCTSTR fnc)
{
	CString ctmpstr=fnc;
	ctmpstr.MakeUpper();
	fns.MakeUpper();
	if (-1==fns.Find(ctmpstr)) return false;
return true;
};
//
C_PlaylistParser::~C_PlaylistParser(){ songList.empty();}//free vector mem
//
C_PlaylistParser::C_PlaylistParser()
{
	songList.empty();
	infotip.Empty();

	totalPlaytime_sec=0;
	totalPlaytime_signed=songcount=maxseconds=0;
	playlistType=NOTPLS;
	plsStatus=NOCODE;
	textencoding=PLS_ANSI;
	textencodingEx=PLS_ANSI;
	allvalidentrys=allvalidlength=true;
}
//
BOOL C_PlaylistParser::process(LPCTSTR fpls)
{
	playlistFile.Split(fpls);	
	playlistFile.ext_nodot.MakeLower();
try
	{
		playlistType=getType(playlistFile.ext_nodot);
		switch (playlistType)
			{
			case M3U:
				parseM3U();
				break;
			case PLS:
				parsePLS();
				break;
			//case PLC:
			//	parsePLC();
			//	break;
			//case WPL:
			//	parseWPL();
			//	break;
			//case ASX:
			//	parseASX();
			//	break;
			//case CUE:
			//	parseCUE();
			//	break;
			default:
				break;
			}
	buildPlaylist();
	}
	catch (...) {return FALSE;}
return TRUE;
}
//
inline PLAYLIST_TYPE C_PlaylistParser::getType(CString fpl)
{
	fpl.MakeLower();
	if (fpl.IsEmpty()) return NOTPLS;
	if (fpl==_T("m3u")) return M3U;
	if (fpl==_T("m3u8")) return M3U;
	if (fpl==_T("pls")) return PLS;
	if (fpl==_T("plc")) return PLC;
	if (fpl==_T("wpl")) return WPL;
	if (fpl==_T("asx")) return ASX;
	if (fpl==_T("cue")) return CUE;
return NOTPLS;
}
//

//
void C_PlaylistParser::buildPlaylist()
{
	if (plsStatus!=NOCODE) return;

	int tipwidth=0;
	CString plsLine, infoSeparator;
	CString filesize=getPlaylistSize();
	infoSeparator.Empty();

	CString totalPlaytime=_T("Total playing time: ")+seconds2str(totalPlaytime_sec,totalPlaytime_signed)+_T("\n")+filesize;
	
	//build songs list line by line
	for (songListiter=songList.begin(); songListiter<songList.end(); songListiter++)
	{
		plsLine.Empty();

		if ((infotip.GetLength()>(VISTA_INFOTIP_LIMIT-totalPlaytime.GetLength()-69)))
		 {infotip+=_T("...\n");break;}

		if (songListiter->index<10) plsLine+=_T(" ");
		plsLine.Append(songListiter->index);
		plsLine+=_T(". ")+songListiter->title;//L2
		plsLine+=_T("   (")+seconds2str(songListiter->tracklength)+_T(")\n");

		j=plsLine.GetLength();
		if (tipwidth<j) tipwidth=j;

		infotip+=plsLine;//add line to infotip
	}

	//build separator line
	j=((tipwidth>65) ? 65 : tipwidth);
	for (i=1; i<j; i++) { infoSeparator+=_T("-");}
	infoSeparator+=_T("\n");

	infotip+=infoSeparator+totalPlaytime;
}
//
bool C_PlaylistParser::decodeUtf(std::string sstrin, CString &cstrout)
{
	if (!sstrin.length()) return false;//skip empty lines
	cstrout.Empty();

   int len = MultiByteToWideChar(CP_UTF8, 0, sstrin.c_str(), -1, NULL, 0);
   if (len>1)
   { 
      TCHAR *ptr = cstrout.GetBuffer(len-1);
      if (ptr!=NULL) mbwcr = MultiByteToWideChar(CP_UTF8, 0, sstrin.c_str(), -1, ptr, len);
      cstrout.ReleaseBuffer();

	  if ((mbwcr==0) || (mbwcr==ERROR_NO_UNICODE_TRANSLATION)) return false;
   }

return true;
}
//
int C_PlaylistParser::getDigitCount(LONG dn)
{
	CString dnm;
	dnm.Append(dn);
	if (dn<10) return (1+dnm.GetLength());
	return dnm.GetLength();
}
//
CString C_PlaylistParser::seconds2str(int sec, int sec2)
{
	if ((sec<0) || ((sec==0) && (sec2<0))) return _T("--:--");

	CString cstr;
	cstr.Empty();
	int h,m,s;
	h=sec/3600; sec=sec%3600;
	m=sec/60; s=sec%60;

	if (h) {cstr.Append(h); cstr+=_T(":");}

	if (!m)	cstr+=_T("00:");
	else {if ((m<10)&&(h!=0)) cstr+=_T("0"); cstr.Append(m); cstr+=_T(":");}
	
	if (!s) cstr+=_T("00");
	else {if (s<10) cstr+=_T("0"); cstr.Append(s);}

return cstr;
}
//
CString C_PlaylistParser::getPlaylistSize()
{
	CString psize;
	psize.Empty();

	HANDLE hFile = CreateFile(playlistFile.fullpath, GENERIC_READ, FILE_SHARE_DELETE, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == NULL) return psize;

	// get file size
	DWORD fsize = GetFileSize(hFile, NULL);//old fc, but playlists are not usually huge
	CloseHandle(hFile);
	if (fsize ==INVALID_FILE_SIZE) return psize;

	//separate sizes:bytes,kB,MB, GB? unlikely
	if (fsize<1024) psize.Format(_T("Size: %d bytes"),fsize);
	if ((fsize>1024) && (fsize<1048576)) psize.Format(_T("Size: %d,%d KB"),(fsize/1024),((fsize % 1024)/100)); 
	if (fsize>1048576) psize.Format(_T("Size: %d,%d MB"),(fsize/1048576),((fsize % 1048576)/10000));
	if (fsize>1073741824) psize.Format(_T("Size: %d,%d GB"),(fsize/1073741824),((fsize % 1073741824)/1000000));

return psize;	
}
