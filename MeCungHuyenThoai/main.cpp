#include "SetUp.h"

int main(int argc, char* argv[]) {

	start();
	close();

	return 0;
}

//#include <SDL.h>
//
//int main(int argc, char* argv[]) {
//    // Initialize SDL video subsystem
//    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
//        return -1;
//    }
//
//    // Create a window that can be resized
//    SDL_Window* window = SDL_CreateWindow("Resizable Window",
//        S00, 600, SDL_WINDOW_RESIZABLE);
//
//    if (!wiDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
//        8ndow) {
//        SDL_Log("Could not create window: %s", SDL_GetError());
//        SDL_Quit();
//        return -1;
//    }
//
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    if (!renderer) {
//        SDL_Log("Could not create renderer: %s", SDL_GetError());
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//        return -1;
//    }
//
//    SDL_Event event;
//    int running = 1;
//
//    while (running) {
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT) {
//                running = 0;
//            }
//
//            // Handle window events (maximize, minimize, etc.)
//            if (event.type == SDL_WINDOWEVENT) {
//                switch (event.window.event) {
//                case SDL_WINDOWEVENT_MAXIMIZED:
//                    SDL_Log("Window Maximized");
//                    break;
//                case SDL_WINDOWEVENT_RESTORED:
//                    SDL_Log("Window Restored");
//                    break;
//                case SDL_WINDOWEVENT_MINIMIZED:
//                    SDL_Log("Window Minimized");
//                    break;
//                }
//            }
//        }
//
//        // Clear the renderer with blue background
//        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);  // Blue background
//        SDL_RenderClear(renderer);
//
//        // Set color to yellow for the square (R, G, B, A)
//        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);  // Yellow color
//
//        // Define the rectangle for the square
//        SDL_Rect square = { 20, 20, 50, 50 };  // x = 20, y = 20, width = 50, height = 50
//
//        // Render the square
//        SDL_RenderFillRect(renderer, &square);
//
//        // Present the updated renderer
//        SDL_RenderPresent(renderer);
//    }
//
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
//}
