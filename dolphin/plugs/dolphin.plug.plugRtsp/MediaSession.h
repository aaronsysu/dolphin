#pragma once
#include "../Plug.h"
#include <string>
#include <thread>

#include "liveMedia.hh"
#include "BasicUsageEnvironment.hh"

class StreamClientState {
public:
	StreamClientState();
	virtual ~StreamClientState();

public:
	MediaSubsessionIterator* iter;
	MediaSession* session;
	MediaSubsession* subsession;
	TaskToken streamTimerTask;
	double duration;
};

class ourRTSPClient : public RTSPClient {
public:
	static ourRTSPClient* createNew(UsageEnvironment& env, char const* rtspURL,
		int verbosityLevel = 0,
		char const* applicationName = NULL,
		portNumBits tunnelOverHTTPPortNum = 0);

	virtual int Start();
	virtual int Stop();
	void SetMediaCallback(funcRealCallBack lpCallback, void* pObject){
		_pMediaCallback = lpCallback;
		_pMediaObject = pObject;
	}
protected:
	ourRTSPClient(UsageEnvironment& env, char const* rtspURL,
		int verbosityLevel, char const* applicationName, portNumBits tunnelOverHTTPPortNum);
	// called only by createNew();
	virtual ~ourRTSPClient();

	// RTSP 'response handlers':
	static void continueAfterDESCRIBE(RTSPClient* rtspClient, int resultCode, char* resultString);
	static void continueAfterSETUP(RTSPClient* rtspClient, int resultCode, char* resultString);
	static void continueAfterPLAY(RTSPClient* rtspClient, int resultCode, char* resultString);

	// Other event handler functions:
	static void subsessionAfterPlaying(void* clientData); // called when a stream's subsession (e.g., audio or video substream) ends
	static void subsessionByeHandler(void* clientData); // called when a RTCP "BYE" is received for a subsession
	static void streamTimerHandler(void* clientData);
	// called at the end of a stream's expected duration (if the stream has not already signaled its end using a RTCP "BYE")


	// Used to iterate through each stream's 'subsessions', setting up each one:
	static void setupNextSubsession(RTSPClient* rtspClient);

	// Used to shut down and close a stream (including its "RTSPClient" object):
	static void shutdownStream(RTSPClient* rtspClient, int exitCode = 1);

public:
	static unsigned rtspClientCount; // Counts how many streams (i.e., "RTSPClient"s) are currently in use.
	TaskScheduler* _scheduler;
	UsageEnvironment* _env;

	StreamClientState scs;
	funcRealCallBack _pMediaCallback;
	void* _pMediaObject;
	std::thread _mediaWorker;
	char _stopFlag;
};

class PlugMediaSession : public MediaSink
{
public:
	void SetMediaCallback(funcRealCallBack lpCallback, void* pObject){
		_pMediaCallback = lpCallback;
		_pMediaObject = pObject;
	}
public:
	static PlugMediaSession* createNew(UsageEnvironment& env,
		MediaSubsession& subsession, // identifies the kind of data that's being received
		char const* streamId = NULL); // identifies the stream itself (optional)

private:
	PlugMediaSession(UsageEnvironment& env, MediaSubsession& subsession, char const* streamId);
	// called only by "createNew()"
	virtual ~PlugMediaSession();
	static void afterGettingFrame(void* clientData, unsigned frameSize,
		unsigned numTruncatedBytes,
	struct timeval presentationTime,
		unsigned durationInMicroseconds);
	void afterGettingFrame(unsigned frameSize, unsigned numTruncatedBytes,
	struct timeval presentationTime, unsigned durationInMicroseconds);
private:
	// redefined virtual functions:
	virtual Boolean continuePlaying();

private:
	u_int8_t* _receiveBuffer;
	u_int8_t* _frameBuffer;
	MediaSubsession& _subsession;
	char* _streamId;

private:
	std::string _param;
	funcRealCallBack _pMediaCallback;
	void* _pMediaObject;
};

