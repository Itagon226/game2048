#include "Tile.h"
#include <map>

Tile::Tile(int val) { 
    value = val; 
}

void Tile::setValue(int val) { value = val; }

int Tile::getValue() const { return value; }

bool Tile::isEmpty() const { return value == 0; }

// color
SDL_Color Tile::getColor() const {
    static const std::map<int, SDL_Color> colorMap = {
        {0,    {204, 192, 179, 255}},
        {2,    {238, 228, 218, 255}},
        {4,    {237, 224, 200, 255}},
        {8,    {242, 177, 121, 255}},
        {16,   {245, 149, 99, 255}},
        {32,   {246, 124, 95, 255}},
        {64,   {246, 94, 59, 255}},
        {128,  {237, 207, 114, 255}},
        {256,  {237, 204, 97, 255}},
        {512,  {237, 200, 80, 255}},
        {1024, {237, 197, 63, 255}},
        {2048, {237, 194, 46, 255}},
        // 4096
    };

    auto it = colorMap.find(value);
    if (it != colorMap.end()) return it->second;
    
    return SDL_Color{ 187, 173, 160 , 255 };
}

SDL_Color Tile::getTextColor() const {
    if (value <= 4) return SDL_Color{ 119, 110, 101, 255 };
    return SDL_Color{ 249, 246, 242, 255 };
}

