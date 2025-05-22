#include "Renderer.h"
#include <string>
#include <iostream>

using namespace std;

Renderer::Renderer() : window(nullptr), renderer(nullptr), font(nullptr) {
    // Initialize button text
    PlayAgain.text = "Play Again";
    Exit.text = "Exit";
}

Renderer::~Renderer() {
    if (font != nullptr) TTF_CloseFont(font);
    if (renderer != nullptr) SDL_DestroyRenderer(renderer);
    if (window != nullptr) SDL_DestroyWindow(window);
}

bool Renderer::initialize() {
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) return false;

    font = TTF_OpenFont("assets/font/ClearSans-Medium.ttf", 36);
    if (font == nullptr) return false;

    // Initialize button positions
    PlayAgain.rect = { SCREEN_WIDTH / 4 - 75, SCREEN_HEIGHT / 2 + 50, 150, 50 };
    Exit.rect = { 3 * SCREEN_WIDTH / 4 - 75, SCREEN_HEIGHT / 2 + 50, 150, 50 };

    SDL_SetRenderDrawColor(renderer, 250, 248, 239, 255);
    return true;
}

void Renderer::render(const Board& board, int score, int highScore) {
    SDL_RenderClear(renderer);

    // Draw board background
    SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);
    SDL_Rect boardRect = { BOARD_PADDING, BOARD_PADDING + 60, SCREEN_WIDTH - 2 * BOARD_PADDING, SCREEN_HEIGHT - 2 * BOARD_PADDING - 60 };
    SDL_RenderFillRect(renderer, &boardRect);

    // Draw tiles
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            renderTile(col * (TILE_SIZE + TILE_MARGIN) + BOARD_PADDING,
                row * (TILE_SIZE + TILE_MARGIN) + BOARD_PADDING + 60,
                board.getTile(row, col));
        }
    }

    // Draw score and high score
    SDL_Color textColor = { 119, 110, 101, 255 };
    SDL_Color boxColor = { 187, 173, 160, 255 };

    // Score box
    SDL_SetRenderDrawColor(renderer, boxColor.r, boxColor.g, boxColor.b, boxColor.a);
    SDL_Rect scoreBox = { BOARD_PADDING, 10, 150, 40 };
    SDL_RenderFillRect(renderer, &scoreBox);

    string scoreStr = "Score: " + to_string(score);
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreStr.c_str(), textColor);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_Rect scoreTextRect = {
        BOARD_PADDING + 10,
        10 + (40 - scoreSurface->h) / 2,
        scoreSurface->w,
        scoreSurface->h
    };
    SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreTextRect);
    SDL_FreeSurface(scoreSurface);
    SDL_DestroyTexture(scoreTexture);

    // High score box
    SDL_SetRenderDrawColor(renderer, boxColor.r, boxColor.g, boxColor.b, boxColor.a);
    SDL_Rect highScoreBox = { SCREEN_WIDTH - BOARD_PADDING - 150, 10, 150, 40 };
    SDL_RenderFillRect(renderer, &highScoreBox);

    string highScoreStr = "High: " + to_string(highScore);
    SDL_Surface* highScoreSurface = TTF_RenderText_Solid(font, highScoreStr.c_str(), textColor);
    SDL_Texture* highScoreTexture = SDL_CreateTextureFromSurface(renderer, highScoreSurface);
    SDL_Rect highScoreTextRect = {
        SCREEN_WIDTH - BOARD_PADDING - 140,
        10 + (40 - highScoreSurface->h) / 2,
        highScoreSurface->w,
        highScoreSurface->h
    };
    SDL_RenderCopy(renderer, highScoreTexture, nullptr, &highScoreTextRect);
    SDL_FreeSurface(highScoreSurface);
    SDL_DestroyTexture(highScoreTexture);

    SDL_RenderPresent(renderer);
}

void Renderer::renderTile(int x, int y, const Tile& tile) {
    SDL_Color color = tile.getColor();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_Rect tileRect = { x, y, TILE_SIZE, TILE_SIZE };
    SDL_RenderFillRect(renderer, &tileRect);

    if (!tile.isEmpty()) {
        SDL_Color textColor = tile.getTextColor();
        string valueStr = to_string(tile.getValue());

        SDL_Surface* surface = TTF_RenderText_Solid(font, valueStr.c_str(), textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_Rect textRect = {
            x + (TILE_SIZE - surface->w) / 2,
            y + (TILE_SIZE - surface->h) / 2,
            surface->w,
            surface->h
        };

        SDL_RenderCopy(renderer, texture, nullptr, &textRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}

void Renderer::renderLose() {
    SDL_Color bgColor = { 255, 0, 0, 200 };
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Color buttonColor = { 187, 173, 160, 255 };
    SDL_Color buttonTextColor = { 119, 110, 101, 255 };

    // draw bg
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_Rect background = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderFillRect(renderer, &background);

    // draw game over
    SDL_Surface* surface = TTF_RenderText_Solid(font, "GAME OVER!", textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect textRect = {
        (SCREEN_WIDTH - surface->w) / 2,
        SCREEN_HEIGHT / 2 - 50,
        surface->w,
        surface->h
    };
    SDL_RenderCopy(renderer, texture, nullptr, &textRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    // draw play again
    SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
    SDL_RenderFillRect(renderer, &PlayAgain.rect);
    surface = TTF_RenderText_Solid(font, PlayAgain.text.c_str(), buttonTextColor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect playAgainTextRect = {
        PlayAgain.rect.x + (PlayAgain.rect.w - surface->w) / 2,
        PlayAgain.rect.y + (PlayAgain.rect.h - surface->h) / 2,
        surface->w,
        surface->h
    };
    SDL_RenderCopy(renderer, texture, nullptr, &playAgainTextRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    // draw exit
    SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
    SDL_RenderFillRect(renderer, &Exit.rect);
    surface = TTF_RenderText_Solid(font, Exit.text.c_str(), buttonTextColor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect exitTextRect = {
        Exit.rect.x + (Exit.rect.w - surface->w) / 2,
        Exit.rect.y + (Exit.rect.h - surface->h) / 2,
        surface->w,
        surface->h
    };
    SDL_RenderCopy(renderer, texture, nullptr, &exitTextRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
}

void Renderer::renderWin() {
    SDL_Color color = { 144, 238, 144, 180 };
    SDL_Color textColor = { 0, 100, 0, 255 };

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect background = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderFillRect(renderer, &background);

    SDL_Surface* surface = TTF_RenderText_Solid(font, "YOU WIN!", textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect textRect = {
        (SCREEN_WIDTH - surface->w) / 2,
        (SCREEN_HEIGHT - surface->h) / 2,
        surface->w,
        surface->h
    };
    SDL_RenderCopy(renderer, texture, nullptr, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(renderer);
}

bool Renderer::isPointInButton(int x, int y, const Button& button) {
    return (x >= button.rect.x && x < button.rect.x + button.rect.w &&
        y >= button.rect.y && y < button.rect.y + button.rect.h);
}