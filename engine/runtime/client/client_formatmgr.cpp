#include "ltmodule.h"
#include "ltpixelformat.h"
#include "iltclientformatmgr.h"

//implementation of IClientFormatMgr interface
class CClientFormatMgr : public IClientFormatMgr {
public:
    declare_interface(CClientFormatMgr);

    //our format mgr object.
    FormatMgr formatmgr;

    FormatMgr *Mgr() {
        return &formatmgr;   
    }
};

//register our implementation.
define_interface(CClientFormatMgr, IClientFormatMgr);

