#ifndef _677BFDA4_81A3_4560_A781_4509E1865146_
#define _677BFDA4_81A3_4560_A781_4509E1865146_
#pragma once
#include "PlaylistGlobals.h"


class _m3uEntry
{
public:
	_plsEntry plsEntry;


	_m3uEntry(){m3ready=false;}
	//~_m3uEntry();
	void addExtinfLine(CString cline);
	void addFilepathLine(CString cline);
	bool isReady(){return m3ready;}
	void setIndex(int i){plsEntry.index=i;}
	void Reset(){m3ready=false;plsEntry.init();}

private:
	bool m3ready;
	CString tempcs;

};
#endif//_677BFDA4_81A3_4560_A781_4509E1865146_
