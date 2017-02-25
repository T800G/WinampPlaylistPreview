#include "stdafx.h"
#include <Shlwapi.h>
#pragma comment( lib, "shlwapi.lib")
#include "ConfigFile.h"//.pls are cfg-structured files
#include "m3uParser.h"
#include "PlaylistParser.h"


//
void _m3uEntry::addExtinfLine(CString cline)
{
	m3ready=false;//reset m3u entry
	//extract time and title from extinf line
	cline.Delete(0,1+cline.Find(_T(":")));//remove '#extinf:' from the beginning of line

	tempcs.Empty();
	tempcs=cline.Left(cline.Find(_T(",")));
	if (tempcs.IsEmpty()) plsEntry.init_tracklength();
	else plsEntry.tracklength=StrToInt(tempcs);//get entry playtime

	cline.Delete(0,1+cline.Find(_T(",")));//1+ ???	//get entry title
	plsEntry.title=cline;
}
//
void _m3uEntry::addFilepathLine(CString cline)
{
	m3ready=true;
	if (findNoCase(cline, _T("http://")))
	 {plsEntry.init_tracklength();plsEntry.title=plsEntry.file=cline;return;}

	plsEntry.file=cline;
	if (plsEntry.title.IsEmpty()) plsEntry.title=plsEntry.file;
}
//
//
void C_PlaylistParser::parseM3U()
{
	plsStatus=NOCODE;
	songList.clear();
	plsEntry.init();
	maxseconds=totalPlaytime_sec=0;
	std::string sline; sline.clear();
	CString cline; cline.Empty();
	i=1;

	_m3uEntry m3uEntry;

	//open file for parsing
	std::ifstream ifs((LPCTSTR)playlistFile.fullpath);
	if (!ifs.is_open()) {plsStatus=PSTC_EXC_ERROR; return;}

	//parse as extinf/file line pairs
while (!ifs.eof())
	{
	if (!getline(ifs, sline)) break;
	if (ifs.fail()) {ifs.close();return;}

	if (!decodeUtf(sline,cline)) continue;
	if (findNoCase(cline,_T("#EXTM3U"))) continue;

//check for empty line?
	if (findNoCase(cline,_T("#EXTINF:")))
	{
	//playlistType=M3UEXT;

	m3uEntry.addExtinfLine(cline);
	}
	else m3uEntry.addFilepathLine(cline);


	if (m3uEntry.isReady())	
	{
		totalPlaytime_signed+=m3uEntry.plsEntry.tracklength;
		totalPlaytime_sec+=((m3uEntry.plsEntry.tracklength<0) ? 0 : m3uEntry.plsEntry.tracklength);//skip streams (-1)
		if (-1>m3uEntry.plsEntry.tracklength) allvalidlength=false;
		if (maxseconds<m3uEntry.plsEntry.tracklength) maxseconds=m3uEntry.plsEntry.tracklength;

		m3uEntry.setIndex(i);
		songList.push_back(m3uEntry.plsEntry);
		m3uEntry.Reset();
		i++;
	}

}//while loop
ifs.close();
}
//
