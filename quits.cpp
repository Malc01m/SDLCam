//Quit before a window or context is present
void quit(int code) {
    SDL_Quit();
    exit(code);
}

//Quit while a window is present, but before a context is present
void quit(int code, SDL_Window *window) {
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(code);
}

//Quit while a window and context are present
void quit(int code, SDL_Window *window, SDL_GLContext ctx) {
    SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(code);
}