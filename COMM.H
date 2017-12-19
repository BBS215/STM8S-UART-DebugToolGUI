///// comm.h
/////     purpose : prototypes for for TCommPort, serial communictaions API encapsulation
/////    copyright: Harold Howe, bcbdev.com 1996-1999.
/////    notice   : This file provides an object that encapsulates the win32 serial port routines.
/////               This file may be distributed and used freely for program development,
/////               but it may not be resold as part of a software development library.
/////               In other words, don't take the source and attempt to sell it to other developers.
#ifndef COMM_H
#define COMM_H

#include <windows.h>
#include <string>
#include <list>
#include <tchar.h>

namespace std
{
#ifdef _UNICODE 
	typedef wstring tstring;
#else
	typedef string tstring;
#endif
};

bool isAblePort(const std::tstring & port);

// When the comm port class encounters an error, it throws an ECommError exception.
// The Error member of the exception object describes what went wrong. Some of the
// items should never happen. Others are fairly common place. You should pay special
// attention to the OPEN_ERROR type. This is the error that occurs when opening the port
// fails because another app already has the port open.
class ECommError
{
public:
    enum ErrorType
    {
        BAD_SERIAL_PORT    ,
        BAD_BAUD_RATE      ,
        BAD_PORT_NUMBER    ,
        BAD_STOP_BITS      ,
        BAD_PARITY         ,
        BAD_BYTESIZE       ,
        PORT_ALREADY_OPEN  ,
        PORT_NOT_OPEN      ,
        OPEN_ERROR         ,
        WRITE_ERROR        ,
        READ_ERROR         ,
        CLOSE_ERROR        ,
        PURGECOMM          ,
        FLUSHFILEBUFFERS   ,
        GETCOMMSTATE       ,
        SETCOMMSTATE       ,
        SETUPCOMM          ,
        SETCOMMTIMEOUTS    ,
        CLEARCOMMERROR     ,
        GET_COMM_MODEM_STATUS_ERROR
    };

    ECommError( ErrorType error);

    ErrorType Error;
    DWORD     Errno;   // Errno == return value from GetLastError. Can be used with FormatMessage
};

class TCommPort
{
  public:
    TCommPort();
    ~TCommPort();
    
//    bool isAblePort(const std::string & port);
    
    int OpenCommPort(void);
    int CloseCommPort(void);

    int SetCommPort(const std::tstring & port);
    std::tstring GetCommPort(void);
    int SetBaudRate(DWORD newBaud);//CBR_110 (300,600,1200,2400,4800,9600,14400,19200,
    DWORD GetBaudRate(void);        //  38400,56000,57600,115200,128000,256000)
    int SetParity(BYTE newParity);//NOPARITY ODDPARITY EVENPARITY MARKPARITY SPACEPARITY
    BYTE GetParity(void);
    int SetByteSize(BYTE newByteSize); // 4-8
    BYTE GetByteSize(void);
    int SetStopBits(BYTE newStopBits);//ONESTOPBIT ONE5STOPBITS TWOSTOPBITS       
    BYTE GetStopBits(void);

    DWORD GetCommModemStatus(); // MS_CTS_ON The CTS is on.
               // MS_DSR_ON The DSR is on.
               // MS_RING_ON The ring indicator signal is on.
               // MS_RLSD_ON The RLSD (receive-line-signal-detect) signal is on.
    void SetDTR(){ if (VerifyOpen()) return; EscapeCommFunction(m_hCom, SETDTR); }
    void ClrDTR(){ if (VerifyOpen()) return; EscapeCommFunction(m_hCom, CLRDTR); }
    void SetRTS(){ if (VerifyOpen()) return; EscapeCommFunction(m_hCom, SETRTS); }
    void ClrRTS(){ if (VerifyOpen()) return; EscapeCommFunction(m_hCom, CLRRTS); }
    
    
    void SetCommDCBProperties(DCB &properties);  // avoid using DCB interface
    void GetCommDCBProperties(DCB &properties);  // Use SetBaudRate et al instead

    void GetCommProperties(COMMPROP &properties);

    void WriteString(const char *outString);
    int WriteBuffer(BYTE  *buffer, unsigned int ByteCount);
    int WriteBufferSlowly(BYTE *buffer, unsigned int ByteCount);
    int ReadString(char *string, unsigned int MaxBytes);
    int ReadBytes(BYTE *bytes, unsigned int byteCount);
    void DiscardBytes(unsigned int MaxBytes);
	void Flush_RX(void);
	void PurgeCommPort(void);
    void FlushCommPort(void);

    void  PutByte(BYTE value);
    int   GetByte(); // -1 при отсуствии
    int   GetByte(int Time); // ждать байта не менее Time ms 
    int	  BytesAvailable(void);

    bool GetConnected()
    {
        return m_CommOpen;
    }

    HANDLE GetHandle() // allow access to the handle in case the user needs to
    {                  // do something hardcore. Avoid this if possible
        return m_hCom;
    }

  private:
    // Note: the destructor of the commport class automatically closes the
    //       port. This makes copy construction and assignment impossible.
    //       That is why I privatize them, and don't define them. In order
    //       to make copy construction and assignment feasible, we would need
    //       to employ a reference counting scheme.
    TCommPort(const TCommPort &);            // privatize copy construction
    TCommPort & operator=(const TCommPort&);  // and assignment.

    int VerifyOpen(void)
    {
		if (!m_CommOpen)
			//throw ECommError(ECommError::PORT_NOT_OPEN) ;
			return -1;
		return 0;
    }

    int VerifyClosed(void)
    {
        if(m_CommOpen)
            //throw ECommError(ECommError::PORT_ALREADY_OPEN) ;
			return -1;
		return 0;
    }

  // this stuff is private because we want to hide these details from clients
    bool          m_CommOpen;
    COMMTIMEOUTS  m_TimeOuts;
    std::tstring   m_CommPort;
    DCB           m_dcb;        // a DCB is a windows structure used for configuring the port
    DCB           old_m_dcb;    
    HANDLE        m_hCom;       // handle to the comm port.
};

int Get_port_list(std::list<_TCHAR*> &port_list);
void Free_port_list(std::list<_TCHAR*> &port_list);

#endif