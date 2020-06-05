#include "udp_conf.h"
#include "string.h"

CFW_TCPIP_SOCKET_ADDR dest_addr;
uint8_t sockfd1 = -1;    //sockfd

static VOID test_udp_rsp(void *param)
{
    COS_EVENT *pEvent = (COS_EVENT *)param;
    COS_PRINTFI("test_udp_rsp Got 0x%x,0x%x,0x%x,0x%x",
          pEvent->nEventId, pEvent->nParam1, pEvent->nParam2, pEvent->nParam3);

    int uSocket = (int)pEvent->nParam1;
    UINT16 uDataSize = pEvent->nParam2;
    UINT8 *pData;
    CFW_TCPIP_SOCKET_ADDR from_addr;
    UINT32 iResult;
    INT32 fromLen = sizeof(CFW_TCPIP_SOCKET_ADDR);

    switch (pEvent->nEventId)
    {
    case EV_CFW_TCPIP_REV_DATA_IND:
        COS_PRINTFI("test_udp_rsp socket:%d, len:%d", uSocket, uDataSize);
        pData = COS_MALLOC(pEvent->nParam2 + 1);
        memset(pData, 0, pEvent->nParam2 + 1);
        if (pData == NULL)
            return;
        iResult = CFW_TcpipSocketRecvfrom(uSocket, pData, uDataSize, 0, &from_addr, &fromLen);
        if (SOCKET_ERROR == iResult){
        }
        else
        {
            ((char *)pData)[uDataSize] = '\0';
            COS_PRINTFI("test_udp_rsp: udp_recv_data = %s", (char *)pData);
            COS_PRINTFI("test_udp_rsp: %d,%s,%hu,%d,", uSocket, inet_ntoa(from_addr.sin_addr), ntohs(from_addr.sin_port), iResult);
        }
        COS_FREE(pData);
        break;
    default:
        COS_PRINTFI("UDP unexpect asynchrous event/response %d", pEvent->nEventId);
        break;
    }
    COS_FREE(pEvent);
}

bool udp_init(const char *addr, uint16_t port){
      /* Create UDP Connect */
    UINT8 c_type = CFW_TCPIP_SOCK_DGRAM, c_protocol = CFW_TCPIP_IPPROTO_UDP;
    INT32 result = 0;

    result = CFW_TcpipSocketEX(CFW_TCPIP_AF_INET, c_type, c_protocol, test_udp_rsp, 0);
    if (SOCKET_ERROR == result) {
        COS_PRINTFI("CFW_TcpipSocket() failed!");
        return false;
    }
    sockfd1 = result;

    /* Send UDP data */
    const uint8_t *des_ipaddress = addr;
    UINT16 des_port = port;
    const uint8_t *send_data = "Hello This is UDP test Demo!";
    
    
    dest_addr.sin_family = CFW_TCPIP_AF_INET;
    dest_addr.sin_port = htons(des_port);
    dest_addr.sin_len = sizeof(CFW_TCPIP_SOCKET_ADDR);
    result = CFW_TcpipInetAddr(des_ipaddress);
    if (SOCKET_ERROR == result) {
        COS_PRINTFI("CFW_TcpipInetAddr() failed!");
        return false;
    }
    dest_addr.sin_addr.s_addr = result;
    COS_PRINTFI("dest_addr.sin_addr.s_addr send 0x%x", dest_addr.sin_addr.s_addr);
    result = CFW_TcpipSocketSendto(sockfd1, (void *)send_data, strlen(send_data), 0, &dest_addr, dest_addr.sin_len);
    if (SOCKET_ERROR == result) {
        COS_PRINTFI("UDP send socket data error!");
        return false;
    }
    return true;
}

bool udp_send(uint8_t *data, uint16_t len){
    uint8_t res = CFW_TcpipSocketSendto(sockfd1, (void *)data, len, 0, &dest_addr, dest_addr.sin_len);
    if (SOCKET_ERROR == res) {
        COS_PRINTFI("UDP send socket data error!");
        return false;
    }
    return true;
}