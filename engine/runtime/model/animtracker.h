
#ifndef __ANIMTRACKER_H__
#define __ANIMTRACKER_H__

#ifndef __MODEL_H__
#include "model.h"
#endif

#ifndef __LTANIMTRACKER_H__
#include "ltanimtracker.h" // main structure defs in here.
#endif


#define NOT_INTERPOLATING   0xFFFF

#define AT_PLAYING      (1<<0)  // Currently playing.
#define AT_LOOPING      (1<<1)
#define AT_DOCALLBACKS  (1<<2)  // Should this tracker do callbacks?
#define AT_ALLOWINVALID (1<<3)  // If this is set, the tracker will be allowed to be set to invalid
                                // animations and frames (IsValid will return FALSE).  This can be
                                // used to keep track of times for a model that is being loaded
                                // in the background.
#define AT_REMOVE		(1<<4)	// Flag used by the client side networking to remove unused trackers, very short term and
								// should never be left set outside of scope of unpacking trackers from the
								// network

// ------------------------------------------------------------ //
// Functions.
// ------------------------------------------------------------ //

void trk_Init(LTAnimTracker *pTracker, Model *pModel, uint32 iAnim);

void trk_Update(LTAnimTracker *pTracker, uint32 msDelta);

bool trk_IsStopped(LTAnimTracker *pTracker);
void trk_SetCurTime(LTAnimTracker *pTracker, uint32 msTime, bool bTransition);

bool trk_SetCurAnim(LTAnimTracker *pTracker, uint32 iAnim, bool bTransition);

// Resets the current animation to its start position.
void trk_Reset(LTAnimTracker *pTracker);

// set the animation to the key closest to msTime in Miliseconds..
void trk_SetAtKeyFrame(LTAnimTracker *pTracker, uint32 msTime);


// ------------------------------------------------------------ //
// Inlines.
// ------------------------------------------------------------ //
inline
bool LTAnimTracker::IsValid()
{
    return m_TimeRef.IsValid();
}
inline
ModelAnim* LTAnimTracker::GetCurAnim()
{
    ASSERT(IsValid());
    return GetModel()->GetAnim(m_TimeRef.m_Cur.m_iAnim);
}
inline
ModelAnim* LTAnimTracker::GetPrevAnim()
{
    ASSERT(IsValid());
    return GetModel()->GetAnim(m_TimeRef.m_Prev.m_iAnim);
}
inline
AnimInfo* LTAnimTracker::GetCurAnimInfo()
{
    ASSERT(IsValid());
    return GetModel()->GetAnimInfo(m_TimeRef.m_Cur.m_iAnim);
}
inline
AnimInfo* LTAnimTracker::GetPrevAnimInfo()
{
    ASSERT(IsValid());
    return GetModel()->GetAnimInfo(m_TimeRef.m_Prev.m_iAnim);
}
inline
AnimKeyFrame* LTAnimTracker::GetCurFrame()
{
    ASSERT(IsValid());
    return &GetCurAnim()->m_KeyFrames[m_TimeRef.m_Cur.m_iFrame];
}
inline
AnimKeyFrame* LTAnimTracker::GetPrevFrame()
{
    ASSERT(IsValid());
    return &GetPrevAnim()->m_KeyFrames[m_TimeRef.m_Prev.m_iFrame];
}
inline
bool LTAnimTracker::AllowInvalid()
{
    return !!(m_Flags & AT_ALLOWINVALID);
}

inline
uint32 trk_GetCurAnimIndex(LTAnimTracker *pTracker)
{
    return pTracker->m_TimeRef.m_Cur.m_iAnim;
}

inline
void trk_Loop(LTAnimTracker *pTracker, bool bLoop)
{
    if (bLoop)
        pTracker->m_Flags |= AT_LOOPING;
    else
        pTracker->m_Flags &= ~AT_LOOPING;
}

inline
void trk_Play(LTAnimTracker *pTracker, bool bPlaying)
{
    if (bPlaying)
        pTracker->m_Flags |= AT_PLAYING;
    else
        pTracker->m_Flags &= ~AT_PLAYING;
}

#endif  // __ANIMTRACKER_H__











