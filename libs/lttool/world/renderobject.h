// ----------------------------------------------------------
// renderobject.h
// lithtech (c) 2000 
//
// A CRenderObject is a device dependant object that exists in the
// renderer.
// RenderObject is a virtual base class - All RenderObjects should derive from this class.
// ----------------------------------------------------------
#ifndef __RENDEROBJECT_H__
#define __RENDEROBJECT_H__

class CRenderObject
{
protected :
    RENDER_OBJECT_TYPES m_Type;
    
public:
	// RenderObjects can be destroyed (on some platforms, anyway). This method should
	//	be used to re-load/create all the lost parts (this is basically for ALT-TAB)...
	virtual void ReCreateObject()									{ }
	virtual void FreeDeviceObjects()								{ }

	virtual void Render()											{ } // Virtual function for drawing...

	RENDER_OBJECT_TYPES GetType()									{ return m_Type; }

    // a little kludge here to exclude this stuff which isn't needed.
#ifdef __PS2
    CRenderObject()													{ }
	virtual ~CRenderObject()										{ }
#else
    CRenderObject()													{ m_pNext = NULL; }
	virtual ~CRenderObject()										{ }
    
	CRenderObject*	GetNext()										{ return m_pNext; }
	void			SetNext(CRenderObject* pNext)					{ m_pNext = pNext; }

private:
	// This puffs - but this is so that these things can be contained in a list (since we aren't using STL at this point)...
	CRenderObject*	m_pNext;
#endif
};

#endif 










