#include "common.h"

#include <map>
using namespace std;

class CHttpProtocol
{
public:
	char * ErrorMsg;					     //�ж��Ƿ��ʼ�������г�������Ϣ
	SOCKET m_listenSocket;				   //���������׽���
	map<char *, char *> m_typeMap;	// ����content-type���ļ���׺�Ķ�Ӧ��ϵmap
	HANDLE m_hExit;

	char * m_strRootDir;				  // web�ĸ�Ŀ¼
	UINT	m_nPort;				       	  // http server�Ķ˿ں�

	BIO *bio_err;
	static char * pass;
	SSL_CTX *ctx;
	char * initialize_ctx();												//��ʼ��CTX
	char * load_dh_params(SSL_CTX *ctx, char *file);						//����CTX����
	static int password_cb(char *buf, int num, int rwflag, void *userdata);

public:
	CHttpProtocol(void);
	int TcpListen(); 
	void err_exit(char * str);
	
	void StopHttpSrv();													//ֹͣHTTP����
	bool StartHttpSrv();												//��ʼHTTP����

	static void * ListenThread(LPVOID param);								//�����߳�
	static void * ClientThread(LPVOID param);								//�ͻ��߳�

	bool RecvRequest(PREQUEST pReq, LPBYTE pBuf, DWORD dwBufSize);		//����HTTP����
	int Analyze(PREQUEST pReq, LPBYTE pBuf);							//����HTTP����
	void Disconnect(PREQUEST pReq);										//�Ͽ�����
	void CreateTypeMap();												//��������ӳ��
	void SendHeader(PREQUEST pReq);										//����HTTPͷ
	int FileExist(PREQUEST pReq);										//�ж��ļ��Ƿ����
	
	void GetCurrentTime(LPSTR lpszString);								//�õ�ϵͳ��ǰʱ��
	bool GetLastModified(HANDLE hFile, LPSTR lpszString);				//�õ��ļ��ϴ��޸ĵ�ʱ��
	bool GetContentType(PREQUEST pReq, LPSTR type);						//ȡ���ļ�����
	void SendFile(PREQUEST pReq);										//�����ļ�
	bool SendBuffer(PREQUEST pReq, LPBYTE pBuf, DWORD dwBufSize);		//���ͻ���������
public:
	bool SSLRecvRequest(SSL *ssl,BIO *io, LPBYTE pBuf, DWORD dwBufSize);//����HTTPS����
	bool SSLSendHeader(PREQUEST pReq, BIO *io);							//����HTTPSͷ
	bool SSLSendFile(PREQUEST pReq, BIO *io);							//��SSLͨ�������ļ�
	bool SSLSendBuffer(PREQUEST pReq, LPBYTE pBuf, DWORD dwBufSize);
public:
	~CHttpProtocol(void);
	void Test(PREQUEST pReq);
};
