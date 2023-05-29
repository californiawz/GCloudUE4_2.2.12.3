
#ifndef __ASOCKET_H__
#define __ASOCKET_H__
#include "ABasePal.h"


#if defined (_WIN32) || defined (_WIN64)	// for windows

//_GCLOUDCORE_UE defined in GCloudCore.Build.cs
#if defined(_GCLOUDCORE_UE) && (_GCLOUDCORE_UE > 0)
#include "Windows/AllowWindowsPlatformAtomics.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include <winsock2.h>
#include "Windows/HideWindowsPlatformAtomics.h"
#include "Windows/HideWindowsPlatformTypes.h"
#else
#include <winsock2.h>
#endif

typedef int 						socklen_t;

#define QWSAGetLastError()			WSAGetLastError()
#define QCloseSocket(s)				closesocket(s)
#define QIOCtlSocket(s,c,a)  		ioctlsocket(s,c,a)

#define QINVALID_SOCKET				INVALID_SOCKET
#define QSOCKET_ERROR				SOCKET_ERROR

#else			// for linux

#include <sys/time.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#ifndef __ORBIS__
#include <sys/wait.h>
#endif
#include <sys/socket.h>

#if (defined ANDROID)
#include <linux/if.h>
#endif
#if (defined __APPLE__)
#include <net/if.h>
#endif


#include <netinet/in.h>
#include <unistd.h>
#ifndef __ORBIS__
#include <sys/ioctl.h>
#include <netdb.h>
#endif
#include <sys/errno.h>
#include <arpa/inet.h>
//#include <Common/Debug.h>

typedef sockaddr_in					SOCKADDR_IN;
typedef sockaddr					SOCKADDR;

#define QWSAGetLastError()			errno
#define QCloseSocket(s)				close(s)
#define QIOCtlSocket(s,c,a)  		ioctl(s,c,a)

#define QINVALID_SOCKET	    		(-1)
#define QSOCKET_ERROR        		(-1)

#define SOCKET						int
#define WSAEBADF					EBADF
#define WSAEWOULDBLOCK				EWOULDBLOCK
#define	WSAEINVAL					EINVAL
#define WSAEINPROGRESS				EINPROGRESS
#define WSAEAGAIN					EAGAIN
#endif


namespace ABase
{
    const int32_t PROTOCOL_UDP = 1;
    const int32_t PROTOCOL_TCP = 2;
    
    
    enum EProtocol
    {
        HTTP = 0,
        UDP,
        TCP,
    };
    
    enum SocketStatus
    {
        SS_NOT_CONNECTED,
        SS_CONNECTING = 0x01,
        SS_CONNECTED = 0x02,
        SS_DISCONNECTING = 0x04,
        SS_SEND = 0x08,
        SS_RECV = 0x10,
    };
    
    enum SocketError
    {
        ES_NO_ERROR = 0,
        ES_SOCKET_ERROR = -1,
        ES_INVALID_PARAM = -2,
        ES_SOCKET_CREATE_ERROR = -3,
        ES_CONNECT_ERROR = -4,
        ES_NOT_CONNECTED = -5,
        ES_RECV_ERROR = -6,
        ES_SEND_ERROR = -7,
        ES_RECV_PACKET_EXCEED_SIZE = -100,
        ES_STATUS_ERROR = -1000,
    };
    
    ////////////////////////////////////////////////////////////////////////////////
    //								CSocket
    ////////////////////////////////////////////////////////////////////////////////
    class CSocket
    {
        public:
        CSocket();
        virtual ~CSocket();
        
    private:
        CSocket(const CSocket &);
        CSocket &operator =(const CSocket &);
        
    public:
        bool	Create(a_uint32 dwProtocol, bool ipv6 = false);
        bool	Close();
        void	Attach(SOCKET socket);
        void	Detach();
        
        bool	Bind(const char *ip, int32_t port);
        bool	Listen();
        bool	Accept(CSocket &sockClient);
		
        bool	Connect(const char *IP, int32_t port);
        
        int32_t	Recv(a_byte *buffer, int32_t bufferLen);
        int32_t	Send(const a_byte *buffer, int32_t bufferLen);
        int32_t RecvFrom(a_byte *buffer, int32_t bufferLen, int32_t *outPort =0,char *outIP = 0,int iplen = 0);
        int32_t	SendTo(const a_byte *buffer, int32_t bufferLen, const char *ip, int32_t port);
        
        int32_t	CanRead()		const;
        int32_t	CanWrite()		const;
        int32_t	HasExcept()		const;
        
        bool	SetNonBlocking();
        
        bool	SetSendBufferSize(int32_t bufferLen);
        bool	SetRecvBufferSize(int32_t bufferLen);
        
        SOCKET GetSocket()const;
        int32_t	GetErrorCode() const;
        
        static bool IsIPv6(const char* addr);
        
        
    private:
        
        bool parseProtocol(const char* ip);
        
    private:
        
#if defined (_WIN32) || defined (_WIN64)
        bool	_Startup();
        bool	_Cleanup();
#endif
        
        SOCKET		_socket;
        int32_t _protocol;
        
#if defined (_WIN32) || defined (_WIN64)
        static int32_t	m_nCount;
#endif
    };
    
    
    inline int32_t CSocket::Recv(a_byte *buffer, int32_t bufferLen)
    {
        int32_t nResult = 0;
        if ((nResult = CanRead()) <= 0)
        {
            return nResult;
        }
        
        size_t err =  recv(_socket, (char*)buffer, bufferLen, 0);
        
        return (int32_t)err;
    }
    
    inline int32_t CSocket::Send(const a_byte *buffer, int32_t bufferLen)
    {
        if(QINVALID_SOCKET == _socket)
        {
            return QSOCKET_ERROR;
        }
        
        int32_t nResult = 0;
        if ((nResult = CanWrite()) <= 0)
        {
            return 0;
        }
        int32_t ret = (int32_t)send(_socket, (char*)buffer, bufferLen, 0);
        if(ret < 0)
        {
        }
        
        return ret;
    }
}

#endif
