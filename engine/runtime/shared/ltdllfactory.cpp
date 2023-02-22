#include "bdefs.h"
#include "ltdllfactory.h"

void LTFactoryMod::Clear()
{
	if (m_hInstance)
		FreeLibrary(m_hInstance);

	m_hInstance = NULL;
}

bool LTFactoryMod::Load(const char* dllName)
{
	if (m_hInstance)
		return true;

	WIN32_FIND_DATA tFileFindData;
	memset(&tFileFindData, 0, sizeof(tFileFindData));

	// start a search for sound DLL files

	char cCurrentDir[_MAX_PATH];
	char cProcessDir[_MAX_PATH];

	char cDrive[_MAX_PATH];
	char cDir[_MAX_PATH];
	char cFName[_MAX_PATH];
	char cExt[_MAX_PATH];

	GetCurrentDirectory(_MAX_PATH, cCurrentDir);
	GetModuleFileName(NULL, cProcessDir, _MAX_PATH);

	_splitpath(cProcessDir, cDrive, cDir, cFName, cExt);

	SetCurrentDirectory(cDir);

	HANDLE hFileFindHandle = ::FindFirstFile(dllName, &tFileFindData);
	if (hFileFindHandle == INVALID_HANDLE_VALUE)
	{
		SetCurrentDirectory(cCurrentDir);

		// Try looking in the current directory
		hFileFindHandle = ::FindFirstFile(dllName, &tFileFindData);
		if (hFileFindHandle == INVALID_HANDLE_VALUE)
			return false;
	}

	// stop the search for files
	FindClose(hFileFindHandle);

	// try to load the sound library DLL

	HINSTANCE hLibInstance = ::LoadLibrary(tFileFindData.cFileName);
	if (hLibInstance == NULL)
	{
		SetCurrentDirectory(cCurrentDir);
		return false;
	}

	m_hInstance = hLibInstance;
	SetCurrentDirectory(cCurrentDir);
	return true;
}

void* LTFactoryMod::GetProc(const char* data)
{
	if (!m_hInstance)
		return NULL;

	return ::GetProcAddress(m_hInstance, data);
}
