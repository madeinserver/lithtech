#ifndef __ILTDYNAMICLIGHT_H__
#define __ILTDYNAMICLIGHT_H__

#include "iltobject.h"

class ILTDynamicLight : public ILTObject
{
public:
    virtual float GetRadius() const = 0;
    virtual void SetRadius(float radius) = 0;
};

#endif
