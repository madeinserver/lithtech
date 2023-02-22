#ifndef __LTSYSNODE_H__
#define __LTSYSNODE_H__

#include <string>

template <typename T>
struct LTSysNode
{
	LTSysNode(const char* pcSysName, T* pSys, LTSysNode* pNext)
	{
		m_pNext = pNext;
		m_pSys = pSys;
		m_pcSysName = pcSysName;
	}

	~LTSysNode()
	{
		if (m_pNext != NULL)
			delete m_pNext;
	}

	T* Find(const char* pcSysName)
	{
		if (pcSysName == NULL)
			return NULL;

		if (m_pcSysName == pcSysName)
			return m_pSys;

		if (m_pNext != NULL)
			return m_pNext->Find(pcSysName);

		return NULL;
	}

private:
	std::string m_pcSysName;
	T* m_pSys;
	LTSysNode* m_pNext;
};

#endif
