#pragma once
#include "Consumer.h"
#include "InternalDefines.h"
#include <string>
#include <memory>
extern "C"{
#include "../../thirdparty/SDL2/include/SDL.h"
}

class MediaDisplay
	: public Consumer<MediaSample::Ptr>
{
public:
	MediaDisplay(int width, int height);
	~MediaDisplay();
	void Display();
private:
	virtual void Push(MediaSample::Ptr &buffer) override;
private:
	std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> m_displayWindow;
	std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> m_renderer;
	std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> m_texture;
};

