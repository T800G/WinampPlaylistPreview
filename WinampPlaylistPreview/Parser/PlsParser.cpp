#include "stdafx.h"
#include <Shlwapi.h>
#pragma comment( lib, "shlwapi.lib")
#include "ConfigFile.h"//.pls are cfg-structured files
#include "PlaylistParser.h"

//
void C_PlaylistParser::parsePLS()
{
	plsStatus=NOCODE;
	USES_CONVERSION;
	ConfigFile winampPls(W2A(playlistFile.fullpath));

	std::string nentr;
	nentr="NumberOfEntries";

	if (winampPls.keyExists(nentr)) 
		{ songcount = winampPls.read<int>(nentr);
		if (!(songcount>0))	{plsStatus=PSTC_NOSONGS;return;}}
	else {plsStatus=PSTC_NOSONGS;return;}

	//build vector
	std::string TitleN;
	char strbuf[16];
	allvalidlength=true;

	for (i=1; i<=songcount; i++)//1-based		//limit no# of entries (Vista infotip window limit)
	{
		plsEntry.init();
		plsEntry.index=i;
		memset(strbuf,0,sizeof(strbuf));
		_itoa_s(i,strbuf,sizeof(strbuf),10);

		TitleN.clear();
		TitleN="File";
		TitleN+=strbuf;
		if (!winampPls.keyExists(TitleN))
		{
			allvalidlength=allvalidentrys=false;
			plsEntry.title=_T("---");
		}
		else
		{
			//get file path
			TitleN.clear();
			TitleN="File";
			TitleN+=strbuf;
			plsEntry.sfile=winampPls.read<std::string>(TitleN);

			//get title
			TitleN.clear();
			TitleN="Title";
			TitleN+=strbuf;
			if (!winampPls.keyExists(TitleN))
			{
				plsEntry.stitle=plsEntry.sfile;//if no title, set filepath as title
				allvalidentrys=false;
			}
			else { plsEntry.stitle=winampPls.read<std::string>(TitleN); }

			plsEntry.std2CStr();//make CStrings

			if (findNoCase(plsEntry.file, _T("http://")))
			{
				allvalidlength=false;
				plsEntry.init_tracklength();
				plsEntry.title=plsEntry.file;
			}
			else
			{
				//get track playtime
				TitleN.clear();
				TitleN="Length";
				TitleN+=strbuf;
				if (!winampPls.keyExists(TitleN)) allvalidlength=false;
				else
				{
				plsEntry.tracklength=winampPls.read<int>(TitleN);
				totalPlaytime_signed+=plsEntry.tracklength;
				totalPlaytime_sec+=((plsEntry.tracklength<0) ? 0 : plsEntry.tracklength);//skip streams (-1)
				}


				if (maxseconds<plsEntry.tracklength) maxseconds=plsEntry.tracklength;
			}

		}
		songList.push_back(plsEntry);
	}//for loop

}
//
