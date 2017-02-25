#ifndef _PLAYLIST_PARSER_5B7E52DE_7ADA_4d88_AFAC_296EFC8DDD43_
#define _PLAYLIST_PARSER_5B7E52DE_7ADA_4d88_AFAC_296EFC8DDD43_
#pragma once

#include <vector>
#include <atlmisc.h>

#include "PlaylistGlobals.h"
#include "PlaylistHelper.h"


class C_PlaylistParser
{
public:
	CString infotip;
	BOOL process(LPCTSTR fpls);


	C_PlaylistParser();
	~C_PlaylistParser();
private:
	C_SplitPath playlistFile;
	UINT totalPlaytime_sec;
	int totalPlaytime_signed, songcount, maxseconds;
	bool allvalidentrys, allvalidlength;

	PLAYLIST_TYPE playlistType;
	PLAYLIST_STATUSCODE plsStatus;
	ENCODING_TYPE textencoding, textencodingEx;


	_plsEntry plsEntry;

	std::vector<_plsEntry> songList;
	std::vector<_plsEntry>::iterator songListiter;


	inline PLAYLIST_TYPE getType(CString fpl);
	void parsePLS();
	void parseM3U();
	bool decodeUtf(std::string sstrin, CString &cstrout);
	void buildPlaylist();
	int getDigitCount(LONG dn);
	CString seconds2str(int sec, int sec2=0);
	CString getPlaylistSize();
	
//helpers
	int i,j,k,mbwcr;
	CString ctmpstr;
};
#endif//_PLAYLIST_PARSER_5B7E52DE_7ADA_4d88_AFAC_296EFC8DDD43_