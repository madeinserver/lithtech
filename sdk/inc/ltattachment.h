#ifndef __LTATTACHMENT_H__
#define __LTATTACHMENT_H__

#include "ltbasedefs.h"

class LTAttachment
{
public:
    LTransform          m_Offset;       // transform offset.
    uint16				m_nChildID;		// the child object of this attachment.
    uint16				m_nParentID;	// the parent object of this attachment.
    uint32              m_iSocket;      // Model node index (if the parent is not a model, this is -1).
    LTAttachment* m_pNext;
};

#endif
