#ifndef __LTDLLFACTORY_H__
#define __LTDLLFACTORY_H__

#include "ltsysnode.h"
#include <string>

class LTFactoryMod
{
public:
	LTFactoryMod()
#ifdef _WIN32
		: m_hInstance(NULL)
#endif
	{}

	virtual ~LTFactoryMod() { Clear(); }

	virtual bool Load(const char* dllName);
	virtual void Clear();
	virtual void* GetProc(const char* data);

private:
#ifdef _WIN32
	HINSTANCE m_hInstance;
#endif
};

#define TERM_MSG	"Execution may terminate..."



#define RENDER_DRIVER_NAME			"RenderDrv.dll"
#define RENDER_DRIVER_DESC_NAME		"RenderSysDesc"
#define RENDER_DRIVER_MAKE_NAME		"RenderSysMakes"

struct ILTInfo
{
	const char* driverName;
	const char* descName;
	const char* makeName;
	const char* modType;

	virtual void Init() = 0;
};

template <typename T, typename I>
class LTFactory : public LTFactoryMod
{
public:
	typedef char* (*SysDescFn)();
	typedef T* (*SysMakeFn)();

	LTFactory()
	{
		m_cInfo.Init();
	}

	virtual ~LTFactory() {}

	typedef bool (*FnEnumSysCallback)(const char* pcSysName, const char* pcSysDesc, void* pUserData);

	void DisplaySysError(const char* pcErrorString)
	{
#ifdef _WIN32
		MessageBox(NULL, pcErrorString, "Driver error", MB_OK | MB_ICONERROR);
#endif
	}

	static bool EnumSysCallback(const char* pcSysName, const char* pcSysDesc, void* pUserData)
	{
		char* pcEarliestSysName = (char*)pUserData;

		if (pcEarliestSysName[0] == 0 ||
			strcmp(pcSysName, pcEarliestSysName) < 0)
			strcpy(pcEarliestSysName, pcSysName);

		return true;
	}

	virtual bool EnumSystems(FnEnumSysCallback fnEnumCallback, void* pUserData = NULL)
	{
		char acSysNames[1024] = { 0, 0 };

		if (!fnEnumCallback)
			return false;

		bool bSuccess = FillSystems(&acSysNames[0], 1023);
		if (!bSuccess)
			return false;

		char* pcSysNames = &acSysNames[0];
		while (pcSysNames[0] != 0)
		{
			char* pcSysName = pcSysNames;
			size_t nSysNameLen = strlen(pcSysName);

			char* pcSysDesc = pcSysName + nSysNameLen + 1;
			size_t nSysDescLen = strlen(pcSysDesc);

			bool bContinue = fnEnumCallback(pcSysName, pcSysDesc, pUserData);
			if (!bContinue)
				return true;

			pcSysNames = pcSysDesc + nSysDescLen + 1;
		}

		return true;
	}

	virtual bool FillSystems(char* pcSysNames, uint uiMaxStringLen)
	{
		if (!Load(m_cInfo.driverName))
			return false;
	
		SysDescFn fnSysDesc = (SysDescFn)GetProc(m_cInfo.descName);
		if (fnSysDesc == NULL)
			return false;

		strcpy(pcSysNames, m_cInfo.driverName);
		pcSysNames += strlen(pcSysNames) + 1;
		strcpy(pcSysNames, fnSysDesc());
		pcSysNames += strlen(pcSysNames) + 1;
		pcSysNames[0] = 0;
		return true;
	}

	virtual T* MakeSystem(const char* pcSystemName) {
		static char pcDefaultSysName[1024] = { 0 };

		// if no name provided, enumerate and choose the first

		if (pcSystemName == NULL) {
			EnumSystems(EnumSysCallback, &pcDefaultSysName[0]);
			if (pcDefaultSysName[0] == 0) {
				char acErrorString[1024];
				sprintf(acErrorString, "Could not find a suitable %s driver.\n%s", m_cInfo.modType, TERM_MSG);
				DisplaySysError(acErrorString);
				return NULL;
			}
			pcSystemName = &pcDefaultSysName[0];
		}

		// see if we already have an interface made for that name of sound system

		if (m_pSysNodes != NULL)
		{
			T* pSys = m_pSysNodes->Find(pcSystemName);
			if (pSys != NULL)
				return pSys;
		}

		if (!Load(m_cInfo.driverName))
			return false;

		SysMakeFn fnSysMake = (SysMakeFn)GetProc(m_cInfo.makeName);
		if (fnSysMake == NULL)
		{
			char acErrorString[1024];
			sprintf(acErrorString, "Failed to find func \'%s\' for %s driver \'%s\'.\n%s",
				m_cInfo.makeName, m_cInfo.modType, pcSystemName, TERM_MSG);
			DisplaySysError(acErrorString);
			return NULL;
		}

		T* pSys = fnSysMake();

		if (!pSys->Init())
		{
			char acErrorString[1024];
			sprintf(acErrorString, "Failed to initialize %s driver \'%s\'.\n%s", m_cInfo.modType, pcSystemName, TERM_MSG);
			DisplaySysError(acErrorString);
			return NULL;
		}

		LT_MEM_TRACK_ALLOC(m_pSysNodes = new LTSysNode<T>(pcSystemName, pSys, m_pSysNodes), LT_MEM_TYPE_SOUND);
		return pSys;
	}

private:
	LTSysNode<T>* m_pSysNodes;
	I m_cInfo;
};

#endif
