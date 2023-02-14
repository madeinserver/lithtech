#ifndef __SOCKET_H__
#define __SOCKET_H__

#ifndef  _WINSOCKAPI_
#include <winsock.h>
#endif //_WINSOCKAPI_

#ifndef EWOULDBLOCK
const int EWOULDBLOCK = WSAEWOULDBLOCK;
#endif

#ifndef ECONNRESET
const int ECONNRESET = WSAECONNRESET;
#endif

typedef int socklen_t;

#endif __SOCKET_H__