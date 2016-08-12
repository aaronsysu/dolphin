#include "stdafx.h"
#include "MediaReciever.h"

#define DEFAULT_BUFFER_LENGTH (200*1024)
MediaReciever::MediaReciever()
	: m_udpSocket(nullptr)
	, m_ioPool(nullptr)
	, m_recvBuffer(nullptr)
	, m_recvBufferSize(0)
{
}


MediaReciever::~MediaReciever()
{
}

void MediaReciever::Start()
{
	if (nullptr == m_recvBuffer)
	{
		m_recvBuffer = std::make_shared<SimpleBuffer>();
		m_recvBuffer->pBuf = new char[DEFAULT_BUFFER_LENGTH];
		m_recvBufferSize = DEFAULT_BUFFER_LENGTH;
	}
	if (nullptr == m_ioPool)
	{
		m_ioPool = std::make_unique<CIoPool>();
		m_ioPool->Run(1);
	}
	if (nullptr == m_udpSocket)
	{
		m_udpSocket = std::make_shared<CUdpSocket>(m_ioPool->GetIo());
		m_udpSocket->Bind("0.0.0.0", 9901);
	}
	m_udpSocket->AsynRecv(m_recvBuffer, m_recvBufferSize, std::bind(&MediaReciever::HandleRecv, this));
}

void MediaReciever::Stop()
{
	m_udpSocket->Close();
	m_ioPool->Stop();
}

void MediaReciever::HandleRecv()
{
	auto buffer = std::make_shared<MediaSample>();
	buffer->buffer = reinterpret_cast<unsigned char*>(m_recvBuffer->Get());
	buffer->bufferSize = m_recvBufferSize;
	PushToConsumer(buffer);
	m_udpSocket->AsynRecv(m_recvBuffer, m_recvBufferSize, std::bind(&MediaReciever::HandleRecv, this));
}