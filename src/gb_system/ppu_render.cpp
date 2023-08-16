#include "ppu_render.hpp"
#include "system.hpp"
#include <array>

namespace gb_system {

static const uint8_t LCDC_BG_WINDOW_DISPLAY = 1;
static const uint8_t LCDC_OBJ_DISPLAY = 2;
static const uint8_t LCDC_OBJ_SIZE = 4;
static const uint8_t LCDC_BG_TILE_MAP_DISPLAY_SELECT = 8;
static const uint8_t LCDC_BG_WINDOW_TILE_DATA_SELECT = 16;
static const uint8_t LCDC_WINDOW_DISPLAY = 32;
static const uint8_t LCDC_WINDOW_TILE_MAP_DISPLAY_SELECT = 64;
static const uint8_t LCDC_ENABLED = 128;

int ppu_get_bg_tile_data_address(ppu &pPpu, uint8_t pId, uint8_t pBank) {
  bool bgTileSigned = pPpu.mLcdc & LCDC_BG_WINDOW_TILE_DATA_SELECT;
  int base = pBank * 0x2000;
  if (!bgTileSigned) {
    if (pId >= 128) {
      return base + 0x800 + (pId - 128) * 16;
    } else {
      return base + 0x1000 + pId * 16;
    }
  }
  return base + pId * 16;
}

int ppu_get_bg_palette_color(ppu &pPpu, uint8_t pPaletteId, uint8_t pColorId) {
  int addr = pPaletteId * 8 + pColorId * 2;
  return pPpu.mBgPalette[addr] | (pPpu.mBgPalette[addr + 1] << 8);
}

int ppu_get_obj_palette_color(ppu &pPpu, uint8_t pPaletteId, uint8_t pColorId) {
  int addr = pPaletteId * 8 + pColorId * 2;
  return pPpu.mObjPalette[addr] | (pPpu.mObjPalette[addr + 1] << 8);
}

void ppu_render_line_bg(ppu &pPpu, std::array<uint8_t, LCD_WIDTH> &pLine,
                        int pSrcX, int pSrcY, int pDstX, int pDstY,
                        int pMapAddr) {
  // int drawY = pPpu.mLy + pPpu.mScy;
  int tileY = (pSrcY / 8) & 0x1f;
  int py = pSrcY % 8;
  int fbAddr = pDstY * LCD_WIDTH;
  int bgMapIdBase = pMapAddr;
  int bgMapAttrBase = pMapAddr + 0x2000;
  bool isCGB = pPpu.mSystem.mSystemType == system_type::CGB;

  int currentX = pDstX;
  do {
    // int drawX = currentX + pPpu.mScx;
    int drawX = currentX + pSrcX;
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
    while (px >= 0) {
      uint8_t vx = tileHFlip ? 7 - px : px;
      uint8_t colorId =
          ((tileLine1 >> vx) & 1) | (((tileLine2 >> vx) & 1) << 1);
      if (isCGB) {
        auto color = ppu_get_bg_palette_color(pPpu, tilePalette, colorId);
        pPpu.mFramebuffer[fbAddr + currentX] = color;
        pLine[currentX] = (tilePriority << 1) | (colorId > 0);
      } else {
        auto color = (pPpu.mBgp >> (colorId << 1)) & 0x03;
        pPpu.mFramebuffer[fbAddr + currentX] = color | 0x8000;
        pLine[currentX] = colorId > 0;
      }
      px -= 1;
      currentX += 1;
    }
  } while (currentX < LCD_WIDTH);
}

void ppu_render_line_sprite(ppu &pPpu, std::array<uint8_t, LCD_WIDTH> &pLine) {
  bool lcdcPriority = pPpu.mLcdc & LCDC_BG_WINDOW_DISPLAY;
  bool isCGB = pPpu.mSystem.mSystemType == system_type::CGB;
  int spriteHeight = (pPpu.mLcdc & LCDC_OBJ_SIZE) ? 16 : 8;
  int dstY = pPpu.mLy;
  int fbAddr = dstY * LCD_WIDTH;
  // Read OAM
  // Scan for candidates
  std::array<uint8_t, 10> drawIds;
  int drawIdsPos = 0;
  for (int i = 0; i < 160; i += 4) {
    int spriteY = pPpu.mOam[i] - 16;
    int py = dstY - spriteY;
    if (py < 0 || py >= spriteHeight)
      continue;
    int spriteX = pPpu.mOam[i + 1] - 8;
    if (spriteX <= -8 || spriteX > LCD_WIDTH)
      continue;
    drawIds[drawIdsPos % 10] = i;
    drawIdsPos += 1;
  }
  // Draw OAM
  int drawCount = 0;
  for (int i = drawIdsPos - 1; i >= 0; i -= 1) {
    if (drawCount >= 10)
      break;
    drawCount += 1;
    int addr = drawIds[i % 10];
    int spriteY = pPpu.mOam[addr] - 16;
    int py = dstY - spriteY;
    if (py < 0 || py >= spriteHeight)
      continue;
    uint8_t spriteX = pPpu.mOam[addr + 1] - 8;
    uint8_t tileId = pPpu.mOam[addr + 2];
    uint8_t attributes = pPpu.mOam[addr + 3];

    int obp = (attributes & 16) ? pPpu.mObp1 : pPpu.mObp0;
    bool flipX = attributes & 32;
    bool flipY = attributes & 64;
    bool objPriority = attributes & 128;
    int palette = attributes & 7;
    int tileBank = (attributes >> 3) & 1;

    if (flipY)
      py = spriteHeight - 1 - py;
    if (spriteHeight == 16)
      tileId = tileId & 0xfe;

    int tileAddr = tileBank * 0x2000 + tileId * 16 + py * 2;
    uint8_t tileLine1 = pPpu.mVram[tileAddr];
    uint8_t tileLine2 = pPpu.mVram[tileAddr + 1];

    for (int x = 0; x < 8; x += 1) {
      int px = flipX ? x : (7 - x);
      int currentX = spriteX + x;
      if (currentX < 0 || currentX >= LCD_WIDTH)
        continue;
      int colorId = ((tileLine1 >> px) & 1) | (((tileLine2 >> px) & 1) << 1);
      if (colorId == 0)
        continue;
      uint8_t prevData = pLine[currentX];
      bool bgColor = prevData & 1;
      bool bgPriority = prevData & 2;
      if (isCGB) {
        if (bgColor && lcdcPriority && (objPriority || bgPriority))
          continue;
        int color = ppu_get_obj_palette_color(pPpu, palette, colorId);
        pPpu.mFramebuffer[fbAddr + currentX] = color;
      } else {
        if (bgColor && objPriority)
          continue;
        int color = (obp >> (colorId << 1)) & 0x03;
        pPpu.mFramebuffer[fbAddr + currentX] = color | 0x8000;
      }
    }
  }
}

void ppu_render_line(ppu &pPpu) {
  std::array<uint8_t, LCD_WIDTH> line;
  if (pPpu.mSystem.mSystemType == system_type::CGB ||
      (pPpu.mLcdc & LCDC_BG_WINDOW_DISPLAY)) {
    // GB: If BG_WINDOW_DISPLAY is 0, don't render BG and window
    ppu_render_line_bg(pPpu, line, pPpu.mScx, pPpu.mLy + pPpu.mScy, 0, pPpu.mLy,
                       pPpu.mLcdc & LCDC_BG_TILE_MAP_DISPLAY_SELECT ? 0x1c00
                                                                    : 0x1800);
    int windowY = pPpu.mLy - pPpu.mWy;
    if (pPpu.mLcdc & LCDC_WINDOW_DISPLAY && windowY >= 0) {
      ppu_render_line_bg(
          pPpu, line, -pPpu.mWx + 7, windowY, max(0, pPpu.mWx - 7), pPpu.mLy,
          pPpu.mLcdc & LCDC_WINDOW_TILE_MAP_DISPLAY_SELECT ? 0x1c00 : 0x1800);
    }
  }
  if (pPpu.mLcdc & LCDC_OBJ_DISPLAY) {
    ppu_render_line_sprite(pPpu, line);
  }
}
}; // namespace gb_system
