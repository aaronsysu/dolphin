#include "stdafx.h"
#include "MediaDisplay.h"
#include <thread>

extern "C"{
#if defined(_WIN32)
#pragma comment(lib, "../../thirdParty/SDL2/lib/Win32/SDL2.lib")
#elif defined(_WIN64)
#pragma comment(lib, "../../thirdParty/SDL2/lib/x64/SDL2.lib")
#endif
}
template <typename T>
inline T checkSDL(T value, const std::string &message) {
	if (!value) {
		throw std::runtime_error{ "SDL " + message };
	}
	else {
		return value;
	}
}

MediaDisplay::MediaDisplay(int width, int height)
	: m_displayWindow{checkSDL(SDL_CreateWindow(
		"display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE), 
		"displayWindow"), SDL_DestroyWindow}
	, m_renderer{ checkSDL(SDL_CreateRenderer(
		m_displayWindow.get(), -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
		"renderer"), SDL_DestroyRenderer}
	, m_texture{ checkSDL(SDL_CreateTexture(
		m_renderer.get(), SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING,
		width, height), 
		"renderer"), SDL_DestroyTexture}
{
	checkSDL(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER), "init");

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(m_renderer.get(), width, height);

	SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, 255);
	SDL_RenderClear(m_renderer.get());
	SDL_RenderPresent(m_renderer.get());
}


MediaDisplay::~MediaDisplay()
{
	SDL_Quit();
}

void MediaDisplay::Display()
{
	for (uint64_t frame_number = 0;;++frame_number)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void MediaDisplay::Push(MediaSample::Ptr &buffer)
{
	if (nullptr == buffer)
		return;

	checkSDL(!SDL_UpdateYUVTexture(
		m_texture.get(), nullptr,
		buffer->planes[0], buffer->pitches[0],
		buffer->planes[1], buffer->pitches[1],
		buffer->planes[2], buffer->pitches[2]), "texture update");
	SDL_RenderClear(m_renderer.get());
	SDL_RenderCopy(m_renderer.get(), m_texture.get(), nullptr, nullptr);
	SDL_RenderPresent(m_renderer.get());
}