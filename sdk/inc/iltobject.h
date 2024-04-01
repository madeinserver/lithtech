#ifndef __ILTOBJECT_H__
#define __ILTOBJECT_H__

#include "ltbasedefs.h"
#include "iltclientfilemgr.h"

class ILTObject
{
public:
	virtual const LTVector& GetPos() const = 0;
	virtual void SetPos(const LTVector& pos) = 0;

	virtual void SetDims(const LTVector& dims) = 0;
	virtual const LTVector& GetDism() const = 0;

	virtual float GetRadius() const = 0;
	virtual void SetRadius(float f) = 0;

	virtual float GetRadiusSquared() const = 0;
	virtual void SetRadiusSquared(float f) = 0;

	virtual const LTVector& GetGlobalForceOverride() const = 0;

	virtual void SetupTransform(LTMatrix& mat) = 0;
	virtual bool IsMoveable() const = 0;
	virtual bool IsMainWorldModel() const = 0;

	virtual bool HasWorldModel() const = 0;
	virtual bool IsModel() const = 0;
	virtual bool IsScaled() const = 0;
	virtual bool IsTranslucent() const = 0;
	virtual bool IsPaused() const = 0;

	virtual uint32 GetFlags() const = 0;
	virtual void SetFlags(uint32 flags) = 0;

	virtual uint32 GetFlags2() const = 0;
	virtual void SetFlags2(uint32 flags) = 0;

	virtual uint32 GetUserFlags() const = 0;
	virtual void SetUserFlags(uint32 flags) = 0;

	virtual FileIdentifier* GetFile() = 0;
	virtual void SetFile(FileIdentifier* pFile) = 0;

	virtual uint8 GetColorR() const = 0;
	virtual uint8 GetColorG() const = 0;
	virtual uint8 GetColorB() const = 0;
	virtual uint8 GetColorA() const = 0;

	virtual void SetColorR(uint8 color) = 0;
	virtual void SetColorG(uint8 color) = 0;
	virtual void SetColorB(uint8 color) = 0;
	virtual void SetColorA(uint8 color) = 0;

	virtual LTRotation& GetRotation() = 0;
	virtual void SetRotation(const LTRotation& rot) = 0;

	virtual LTVector& GetScale() = 0;
	virtual void SetScale(const LTVector& rot) = 0;

	virtual uint8 GetObjectType() = 0;

};

#endif
