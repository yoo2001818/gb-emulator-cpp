#include <SDL2/SDL_blendmode.h>
#include "font_renderer.hpp"
#include "application.hpp"

app::font_renderer::font_renderer(app::application &pApp) : mApp(pApp)
{
  this->mTexture = IMG_LoadTexture(this->mApp.mRenderer, "res/font.png");
  if (this->mTexture == nullptr)
  {
    throw std::runtime_error(SDL_GetError());
  }
}

app::font_renderer::~font_renderer()
{
  if (this->mTexture != nullptr)
  {
    SDL_DestroyTexture(this->mTexture);
    this->mTexture = nullptr;
  }
}

void app::font_renderer::reset()
{
  this->reset(0, 0);
}

void app::font_renderer::reset(int pPosX, int pPosY)
{
  this->mStartX = pPosX;
  this->mCurrentX = pPosX;
  this->mCurrentY = pPosY;
}

void app::font_renderer::write(char pChar)
{
  if (pChar == '\n')
  {
    this->mCurrentX = this->mStartX;
    this->mCurrentY += 24;
    return;
  }
  int tileX = pChar % 16;
  int tileY = pChar / 16;
  SDL_Rect srcRect{tileX * 24 + 6, tileY * 24, 12, 24};
  SDL_Rect dstRect{this->mCurrentX, this->mCurrentY, 12, 24};
  SDL_SetRenderDrawColor(this->mApp.mRenderer, 0, 0, 0, 255);
  SDL_SetTextureColorMod(this->mTexture, 255, 255, 255);
  SDL_RenderFillRect(this->mApp.mRenderer, &dstRect);
  SDL_RenderCopy(this->mApp.mRenderer, this->mTexture, &srcRect, &dstRect);
  this->mCurrentX += 12;
}

void app::font_renderer::write(const std::string &pStr)
{
  for (const char &c : pStr)
  {
    this->write(c);
  }
}
