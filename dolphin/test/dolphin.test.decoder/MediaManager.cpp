#include "stdafx.h"
#include "MediaManager.h"
#include "MediaDisplay.h"
#include "MediaDecoder.h"
#include "MediaReciever.h"
#include "MediaDemuxer.h"

MediaManager* MediaManager::m_instance = nullptr;
MediaManager::MediaManager()
	: m_mediaDecoder(nullptr)
	, m_mediaReciever(nullptr)
	, m_mediaDisplay(nullptr)
	, m_mediaDemuxer(nullptr)
{
}


MediaManager::~MediaManager()
{
}

void MediaManager::Init()
{
	if (m_instance == nullptr)
	{
		m_instance = new MediaManager;
	}
}

void MediaManager::UnInit()
{
	if (nullptr != m_instance)
	{
		delete m_instance;
	}
}

MediaManager* MediaManager::Get()
{
	return m_instance;
}

void MediaManager::Start()
{
	if (nullptr == m_mediaDemuxer)
	{
		m_mediaDemuxer = std::make_shared<MediaDemuxer>();
		m_mediaDemuxer->Start();
	}
	if (nullptr == m_mediaReciever)
	{
		m_mediaReciever = std::make_shared<MediaReciever>();
		m_mediaReciever->Start();
	}
	if (nullptr == m_mediaDecoder)
	{
		m_mediaDecoder = std::make_shared<MediaDecoder>();
		m_mediaDecoder->Start();
	}
	if (nullptr == m_mediaDisplay)
	{
		m_mediaDisplay = std::make_shared<MediaDisplay>(1920, 1080);
	}
	m_mediaDemuxer->Attach(m_mediaDecoder);
	m_mediaReciever->Attach(m_mediaDecoder);
	m_mediaDecoder->Attach(m_mediaDisplay);
}

void MediaManager::Stop()
{
	if (nullptr != m_mediaDecoder)
	{
		m_mediaDecoder->Stop();
	}
	if (nullptr != m_mediaReciever)
	{
		m_mediaReciever->Stop();
	}
	if (nullptr != m_mediaDemuxer)
	{
		m_mediaDemuxer->Stop();
	}

}

void MediaManager::Run()
{
	m_mediaDisplay->Display();
}