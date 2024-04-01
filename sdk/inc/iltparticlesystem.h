#ifndef __ILTPARTICLESYSTEM_H__
#define __ILTPARTICLESYSTEM_H__

#include "iltobject.h"

// A single particle.
struct PSParticle
{
    LTVector    m_Pos;				// Current position of the particle
    LTVector    m_Velocity;			// Current velocity of the particle
    float       m_Size;				// Particle size

    LTVector    m_Color;			// 0-255
    float       m_Alpha;			// 0-1

    float		m_fAngle;			// Angle in radians of this particle
    float		m_fAngularVelocity;	// Velocity of the angular change in radians per second

    float       m_Lifetime;         // Current lifetime left
    float       m_TotalLifetime;    // Total lifetime (i.e. initial value)

    uint32		m_nUserData;		// 32 bits of user data...

    PSParticle* m_pNext;			// Linked list information
    PSParticle* m_pPrev;
};

class ILTParticleSystem : public ILTObject
{
public:
    virtual uint32 GetPSFlags() const = 0;
    virtual int GetParticles() const = 0;
    virtual int GetChangedParticles() const = 0;
    virtual const PSParticle& GetParticleHead() const = 0;
    virtual HTEXTURE GetCurTexture() = 0;
    virtual const LTVector& GetSystemCenter() const = 0;
    virtual float GetSystemRadius() const = 0;
    virtual uint32 GetEffectShaderID() const = 0;
    virtual HTEXTURE GetCurrentTexture() = 0;
};

#endif
