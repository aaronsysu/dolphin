#pragma once
#include "../../common/net/UdpSocket.h"
#include "../../common/net/IoPool.h"
#include "Consumer.h"
#include "InternalDefines.h"

class MediaReciever
	: public Producer<MediaSample::Ptr>
{
public:
	MediaReciever();
	~MediaReciever();
	void Start();
	void Stop();
private:
	void HandleRecv();
private:
	std::shared_ptr<SimpleBuffer> m_recvBuffer;
	unsigned int m_recvBufferSize;
	std::unique_ptr<CIoPool> m_ioPool;
	std::shared_ptr<CUdpSocket> m_udpSocket;
};

