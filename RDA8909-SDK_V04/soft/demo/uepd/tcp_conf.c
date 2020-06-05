#include "tcp_conf.h"
#include "string.h"

uint16_t tmplen = 0;
uint8_t sockfd = -1;    //sockfd

static VOID test_tcp_rsp(void *paramer)
{
    COS_EVENT *pEvent = (COS_EVENT *)paramer;
    COS_PRINTFI("test_tcp_rsp Got 0x%x,0x%x,0x%x,0x%x",
          pEvent->nEventId, pEvent->nParam1, pEvent->nParam2, pEvent->nParam3);

    int uSocket = (int)pEvent->nParam1;
    UINT16 uDataSize = pEvent->nParam2;
    // UINT8 *pData;
    char *pData;
    CFW_TCPIP_SOCKET_ADDR from_addr;
    UINT32 iResult;
    INT32 fromLen = sizeof(CFW_TCPIP_SOCKET_ADDR);
 
    switch (pEvent->nEventId)
    {
    case EV_CFW_TCPIP_REV_DATA_IND:
        COS_PRINTFI("test_tcp_rsp socket:%d, len:%d", uSocket, uDataSize);
        pData = COS_MALLOC(pEvent->nParam2 + 1);
        memset(pData, 0, pEvent->nParam2 + 1); 
        if (pData == NULL)
            return;
        iResult = CFW_TcpipSocketRecvfrom(uSocket, pData, uDataSize, 0, &from_addr, &fromLen);
        if (SOCKET_ERROR == iResult)
        {
        }
        else
        {
            for(uint8_t i=0;i<uDataSize;i++)
                COS_PRINTFI("Recv[%d]:%x",i,pData[i]);
            ((char *)pData)[uDataSize] = '\0';
            COS_PRINTFI("test_tcp_rsp: tcp_recv_data = %s", (char *)pData);
            COS_PRINTFI("test_tcp_rsp: %d,%s,%hu,%d,", uSocket, inet_ntoa(from_addr.sin_addr), ntohs(from_addr.sin_port), iResult);     
            COS_PRINTFI("string info %d",uDataSize);
            for(uint16_t i=0;i<uDataSize;i++){
                COS_PRINTFI("%d: %x",i, pData[i]);
            }       
        }
        COS_FREE(pData);
        break;
    default:
        COS_PRINTFI("UDP unexpect asynchrous event/response %d", pEvent->nEventId);
        break;
    }
    COS_FREE(pEvent);
}

bool tcp_init(const char *addr, uint16_t port){
     /* Create TCP Connect */
    UINT8 type = CFW_TCPIP_SOCK_STREAM, protocol = CFW_TCPIP_IPPROTO_TCP;
    // uint8_t sockfd = -1;
    INT32 result = 0;

    result = CFW_TcpipSocketEX(CFW_TCPIP_AF_INET, type, protocol, test_tcp_rsp, 0);
    if (SOCKET_ERROR == result) {
        COS_PRINTFI("CFW_TcpipSocket() failed!");
		// epd_showinfo("error","CFW_TcpipSocket() failed!");
        return false;
    }
    sockfd = result;
    CFW_TCPIP_SOCKET_ADDR server_addr = {0};
    server_addr.sin_family = CFW_TCPIP_AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_len = sizeof(CFW_TCPIP_SOCKET_ADDR);
    result = CFW_TcpipInetAddr(addr);
    if (SOCKET_ERROR == result) {
        COS_PRINTFI("CFW_TcpipInetAddr() failed!");
		// epd_showinfo("error","CFW_TcpipInetAddr() failed!");
        return false;
    }
    server_addr.sin_addr.s_addr = result;
    result = CFW_TcpipSocketConnect(sockfd, &server_addr, sizeof(server_addr));
    if (SOCKET_ERROR == result) {
        COS_PRINTFI("CFW_TcpipSocketConnect() failed!");
		// epd_showinfo("error","CFW_TcpipSocketConnect() failed!");
        return false;
    }
    COS_Sleep(1000);
    
    /* Send data to server */
    static char *send_data="test1234567890";
    result = CFW_TcpipSocketSend(sockfd, (UINT8 *)send_data, strlen(send_data), 0);
    if (SOCKET_ERROR == result) {
        COS_PRINTFI("CFW_TcpipSocketSend() failed!");
		// epd_showinfo("error","CFW_TcpipSocketSend() failed!");
        return false;
    }
    return true;
}

bool tcp_send(uint8_t *data, uint16_t len){
    uint8_t res = CFW_TcpipSocketSend(sockfd, (UINT8 *)data, len, 0);
    if (SOCKET_ERROR == res) {
        COS_PRINTFI("CFW_TcpipSocketSend() failed!");
		// epd_showinfo("error","CFW_TcpipSocketSend() failed!");
        return false;
    }
    return true;
}