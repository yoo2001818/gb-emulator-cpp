#include "ppu_render.hpp"
#include "system.hpp"
#include <array>

namespace gb_system
{

  static const uint8_t LCDC_BG_WINDOW_DISPLAY = 1;
  static const uint8_t LCDC_OBJ_DISPLAY = 2;
  static const uint8_t LCDC_OBJ_SIZE = 4;
  static const uint8_t LCDC_BG_TILE_MAP_DISPLAY_SELECT = 8;
  static const uint8_t LCDC_BG_WINDOW_TILE_DATA_SELECT = 16;
  static const uint8_t LCDC_WINDOW_DISPLAY = 32;
  static const uint8_t LCDC_TILE_MAP_DISPLAY_SELECT = 64;
  static const uint8_t LCDC_ENABLED = 128;

  int ppu_get_bg_tile_data_address(ppu &pPpu, uint8_t pId, uint8_t pBank)
  {
    bool bgTileSigned = pPpu.mLcdc & LCDC_BG_WINDOW_TILE_DATA_SELECT;
    int base = pBank * 0x2000;
    if (bgTileSigned)
    {
      if (pId >= 128)
      {
        return base + 0x800 + (pId - 128) * 16;
      }
      else
      {
        return base + 0x1000 + pId * 16;
      }
    }
    return base + pId * 16;
  }

  int ppu_get_bg_palette_color(ppu &pPpu, uint8_t pPaletteId, uint8_t pColorId)
  {
    int addr = pPaletteId * 8 + pColorId * 2;
    return pPpu.mBgPalette[addr] | (pPpu.mBgPalette[addr + 1] << 8);
  }

  int ppu_get_obj_palette_color(ppu &pPpu, uint8_t pPaletteId, uint8_t pColorId)
  {
    int addr = pPaletteId * 8 + pColorId * 2;
    return pPpu.mObjPalette[addr] | (pPpu.mObjPalette[addr + 1] << 8);
  }

  void ppu_render_line_bg(ppu &pPpu, std::array<uint8_t, LCD_WIDTH> &pLine)
  {
    if (
        pPpu.mSystem.mSystemType != system_type::CGB &&
        !(pPpu.mLcdc & LCDC_BG_WINDOW_DISPLAY))
    {
      // GB: If BG_WINDOW_DISPLAY is 0, don't render BG and window
      return;
    }
    int drawY = pPpu.mLy + pPpu.mScy;
    int tileY = (drawY / 8) & 0x1f;
    int py = drawY % 8;
    int fbAddr = pPpu.mLy * LCD_WIDTH;
    int bgMapIdBase = (pPpu.mLcdc & LCDC_BG_TILE_MAP_DISPLAY_SELECT) ? 0x1c00 : 0x1800;
    int bgMapAttrBase = (pPpu.mLcdc & LCDC_BG_TILE_MAP_DISPLAY_SELECT) ? 0x3c00 : 0x3800;

    int currentX = 0;
    do
    {
      int drawX = currentX + pPpu.mScx;
      int tileX = (drawX / 8) & 0x1f;
      int px = 7 - (drawX % 8);

      // Read tile data of the current position
      uint8_t tileId = pPpu.mVram[bgMapIdBase + (32 * tileY) + tileX];
      uint8_t tileAttributes = pPpu.mVram[bgMapAttrBase + (32 * tileY) + tileX];
      int tilePalette = tileAttributes & 0x7;
      uint8_t tileBank = (tileAttributes >> 3) & 1;
      bool tileHFlip = tileAttributes & 0x20;
      bool tileVFlip = tileAttributes & 0x40;
      bool tilePriority = tileAttributes & 0x80;

      uint8_t vy = tileVFlip ? 7 - py : py;

      int tileAddr = ppu_get_bg_tile_data_address(pPpu, tileId, tileBank);
      uint8_t tileLine1 = pPpu.mVram[tileAddr + vy * 2];
      uint8_t tileLine2 = pPpu.mVram[tileAddr + vy * 2 + 1];

      // Paint the pixel..
      while (px >= 0)
      {
        uint8_t vx = tileHFlip ? 7 - px : px;
        uint8_t colorId = ((tileLine1 >> vx) & 1) | (((tileLine2 >> vx) & 1) << 1);
        if (pPpu.mSystem.mSystemType != system_type::CGB)
        {
          auto color = ppu_get_bg_palette_color(pPpu, tilePalette, colorId);
          pPpu.mFramebuffer[fbAddr + currentX] = color;
          pLine[currentX] = (tilePriority << 1) | (colorId > 0);
        }
        else
        {
          auto color = (pPpu.mBgp >> (colorId << 1)) & 0x03;
          pPpu.mFramebuffer[fbAddr + currentX] = color | 0x8000;
          pLine[currentX] = colorId > 0;
        }
        px -= 1;
        currentX += 1;
      }
    } while (currentX < LCD_WIDTH);
  }

  void ppu_render_line_window(ppu &pPpu, std::array<uint8_t, LCD_WIDTH> &pLine)
  {
  }

  void ppu_render_line_sprite(ppu &pPpu, std::array<uint8_t, LCD_WIDTH> &pLine)
  {
  }

  void ppu_render_line(ppu &pPpu)
  {
    std::array<uint8_t, LCD_WIDTH> line;
    ppu_render_line_bg(pPpu, line);
  }
};
