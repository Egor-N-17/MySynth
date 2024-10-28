#pragma once
#include "PlayParams.h"
#include "Common.h"
#include <mmeapi.h>

class CFileManager : public CSubject, public CSingleton<CFileManager>
{
	friend class CSingleton<CFileManager>;
public:
	void LoadParams();
	
	void SaveParams(sPlayParams params);

protected:
	CFileManager() {};
};
