#pragma once
#include "Types.h"
#include "Constants.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Renderer
{
private:
	Renderer();
	static Renderer* renderer;

	SDL_Renderer* m_renderer = nullptr;
	SDL_Window* m_window = nullptr;
	std::unordered_map<std::string, SDL_Texture*> m_textureData;
	std::unordered_map<std::string, TTF_Font*> m_fontData;
	std::unordered_map<std::string, SDL_Rect*> m_rects;

public:
	~Renderer();
	static Renderer* GetInstance() 
	{ 
		if (renderer == nullptr) 
		{ 
			renderer = new Renderer;
		} 
		return renderer; 
	}

	void DestroyTextures();
	void Clear();
	void Render();
	void LoadFont(const Font& font);
	void LoadTexture(const std::string& id, const std::string& path);
	void LoadRect(const std::string& idRect, const RECT& rect);
	RECT GetRect(const std::string& idRect);
	void SetRect(const std::string& idRect, const RECT& rect);
	VEC2 LoadTextureText(const std::string& fontId, Text text);
	VEC2 GetTextureSize(const std::string& id);
	void PushImage(const std::string& id, const std::string& idRect);
	void PushImage(const std::string& id, const RECT* rectImage);
	void PushSprite(const std::string& id, const std::string& idRectSprite, const std::string& idRectPos);
	void PushSprite(const std::string& id, const RECT* rectSprite, const RECT* rectPos);
	void PushRotatedSprite(const std::string& id, const std::string& idRectSprite, const std::string& idRectPos, float angle);
	void SetRenderDrawColor(int r, int g, int b);
	void SetRenderDrawColor(const Color& c);
	const SDL_Rect MyRect2SDL(const RECT* r) { return { r->x, r->y, r->w, r->h }; }
	const RECT RectSDL2My(const SDL_Rect* r) { return RECT(r->x, r->y, r->w, r->h); }
};