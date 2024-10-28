#include "stdafx.h"
#include "FileManager.h"
#include <fstream> 
#include <regex>
#include <sstream> 

using namespace std;

//----------------------------------------------------------------------------

void CFileManager::LoadParams()
{
	wifstream wifs;
	wifs.open("DefaultParams.txt", ifstream::in);

	shared_ptr<CPlayParams> playParams = CPlayParams::Instance();

	try
	{
		if (wifs.is_open())
		{
			sPlayParams paramsResult;
			paramsResult.clearData();
			wstring wstrText;
			while (getline(wifs, wstrText, L'\n'))
			{
				wsmatch m;
				wregex reg(L"((\\w+ \\w+)|(\\w+#?))\\s+((\\d+)|(.+))");
				wstring wstrAtribute;
				wstring wstrVal;
				regex_search(wstrText, m, reg);
				wstrAtribute = wstrText.substr(0, m[1].length());
				wstrVal.append(m[4].first, m[4].second);
				if (wstrAtribute == NUMBER_OF_BLOCKS)
				{
					paramsResult.iBlocks = _wtoi(wstrVal.c_str());
				}
				else if (wstrAtribute == BLOCK_SAMPLE)
				{
					paramsResult.iBlockSample = _wtoi(wstrVal.c_str());
				}
				else if (wstrAtribute == CHANNELS)
				{
					paramsResult.iChannel = _wtoi(wstrVal.c_str());
				}
				else if (wstrAtribute == SAMPLE_RATE)
				{
					paramsResult.iSampleRate = _wtoi(wstrVal.c_str());
				}
				else if (wstrAtribute == DEVICE_NUMBER)
				{
					paramsResult.iDeviceNumber = _wtoi(wstrVal.c_str());
				}
				else if (wstrAtribute == C_KEY)
				{
					paramsResult.iC = _wtoi(wstrVal.c_str());
				}
				else if (wstrAtribute == CSHARP_KEY)
				{
					paramsResult.iCSharp = _wtoi(wstrVal.c_str());
				}
				else if (wstrAtribute == D_KEY)
				{
					paramsResult.iD = _wtoi(wstrVal.c_str());
				}
				else if (wstrAtribute == DSHARP_KEY)
				{
					paramsResult.iDSharp = _wtoi(wstrVal.c_str());
				}
				else if (wstrAtribute == E_KEY)
				{
					paramsResult.iE = _wtoi(wstrVal.c_str());
				}
				else if (wstrAtribute == F_KEY)
				{
					paramsResult.iF = _wtoi(wstrVal.c_str());
				}
				else if (wstrAtribute == FSHARP_KEY)
				{
					paramsResult.iFSharp = _wtoi(wstrVal.c_str());
				}
				else if (wstrAtribute == G_KEY)
				{
					paramsResult.iG = _wtoi(wstrVal.c_str());
				}
				else if (wstrAtribute == GSHARP_KEY)
				{
					paramsResult.iGSharp = _wtoi(wstrVal.c_str());
				}
				else if (wstrAtribute == A_KEY)
				{
					paramsResult.iA = _wtoi(wstrVal.c_str());
				}
				else if (wstrAtribute == ASHARP_KEY)
				{
					paramsResult.iASharp = _wtoi(wstrVal.c_str());
				}
				else if (wstrAtribute == H_KEY)
				{
					paramsResult.iH = _wtoi(wstrVal.c_str());
				}
				else
				{
					throw false;
				}
			}
			playParams->SetPlayParams(paramsResult);
		}
	}
	catch (bool)
	{
		AfxMessageBox(L"Something wrong with parametrs file. Delete parametrs file and reload app.", MB_OK | MB_ICONWARNING);
	}

	wifs.close();
}

//----------------------------------------------------------------------------

void CFileManager::SaveParams(sPlayParams params)
{
	wofstream wofs("DefaultParams.txt", iostream::trunc);
	wofs << NUMBER_OF_BLOCKS << L"\t\t\t" << params.iBlocks << endl;
	wofs << BLOCK_SAMPLE << L"\t\t" << params.iBlockSample << endl;
	wofs << CHANNELS << L"\t\t" << params.iChannel << endl;
	wofs << SAMPLE_RATE << L"\t\t" << params.iSampleRate << endl;
	wofs << DEVICE_NUMBER << L"\t\t" << params.iDeviceNumber << endl;
	wofs << C_KEY << L"\t\t" << params.iC << endl;
	wofs << CSHARP_KEY << L"\t\t" << params.iCSharp << endl;
	wofs << D_KEY << L"\t\t" << params.iD << endl;
	wofs << DSHARP_KEY << L"\t\t" << params.iDSharp << endl;
	wofs << E_KEY << L"\t\t" << params.iE << endl;
	wofs << F_KEY << L"\t\t" << params.iF << endl;
	wofs << FSHARP_KEY << L"\t\t" << params.iFSharp << endl;
	wofs << G_KEY << L"\t\t" << params.iG << endl;
	wofs << GSHARP_KEY << L"\t\t" << params.iGSharp << endl;
	wofs << A_KEY << L"\t\t" << params.iA << endl;
	wofs << ASHARP_KEY << L"\t\t" << params.iASharp << endl;
	wofs << H_KEY << L"\t\t" << params.iH << endl;
	wofs.close();
}