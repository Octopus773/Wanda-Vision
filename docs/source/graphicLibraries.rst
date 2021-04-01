Graphic Libraries
=================

Introduction
----------------

This page will explain the purpose of graphic interface step by step

.. warning::
    This page is under construction

Comments
--------

Comments begin with ``;`` or ``*`` and end along with the line. ``;`` can be
used anywhere, but ``*`` can be placed only at the beginning of a new line.

WLA supports also ANSI C style commenting. This means you can start a
multiline comment with ``/*`` and end it with ``*/``.

What also is supported are C++ style comments. This means you can start a
comment with ``//``.

You can also use ``.ASM`` and ``.ENDASM`` directives to skip characters. These
function much like ANSI C comments, but unlike the ANSI C comments these can be
nested.


Line splitting
--------------

 .. code-block:: c
   :linenos:
   :emphasize-lines: 8,10,16

    int main(int argc, char *argv[])
    {

        // variable declarations
        SDL_Window *win = NULL;
        SDL_Renderer *renderer = NULL;
        SDL_Surface *texte;
        SDL_Texture *img = NULL;
        SDL_Texture *texteText;
        TTF_Font *police = NULL;
        SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255};
        int w, h;									  // texture width & height
        char temps[] = "salut"; /* Tableau de char suffisamment grand */
        const Uint8 *keystate = SDL_GetKeyboardState(NULL);

        // Initialize SDL.
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
            return 1;
        TTF_Init();

        // create the window and renderer
        // note that the renderer is accelerated
        win = SDL_CreateWindow("Image Loading", 100, 100, WIDTH, HEIGHT, 0);
        renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

        /* Chargement de la police */
        police = TTF_OpenFont("angelina.ttf", 250);

        /* Initialisation du temps et du texte */
        texte = TTF_RenderText_Solid(police, temps, couleurBlanche);
        texteText = SDL_CreateTextureFromSurface(renderer, texte);

        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(texteText, NULL, NULL, &texW, &texH);
        SDL_Rect dstrect = {0, 0, texW, texH};

        // load our image
        img = IMG_LoadTexture(renderer, IMG_PATH);
        SDL_QueryTexture(img, NULL, NULL, &w, &h); // get the width and height of the texture
        // put the location where we want the texture to be drawn into a rectangle
        // I'm also scaling the texture 2x simply by setting the width and height
        SDL_Rect texr;
        texr.x = 0;
        texr.y = 0;
        texr.w = w;
        texr.h = h;
        bool first = true;
        // main loop
        while (1)
        {

            // event handling
            SDL_Event e;
            if (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                    break;
                else if (e.type == SDL_KEYUP)
                {
                    printf("UP event %d\n", e.key.keysym.sym);
                }
                else if (e.type == SDL_KEYDOWN)
                {
                    printf("Down event %d\n", e.key.keysym.sym);
                }
                else if (e.type == SDL_MOUSEBUTTONUP)
                    //printf("mouse event at x: %d %d %d y: %d %d %d\n", e.button.x, WIDTH, (e.button.x * 100) / WIDTH, e.button.y, HEIGHT,  (e.button.y * 100) / HEIGHT);
                    printf("got key %d\n", e.button.button);
            }
            SDLK_a;
            SDL_SCANCODE_A;

            /*if (keystate[SDL_SCANCODE_A]) {
                printf("hold\n");
            }*/

            dstrect.w += (rand() % 11) - 5;
            dstrect.h += (rand() % 11) - 5;
            // clear the screen
            // copy the texture to the rendering context
            //SDL_RenderCopy(renderer, img, NULL, &texr);
            SDL_RenderCopyEx(renderer, img, NULL, &texr, 45, NULL, SDL_FLIP_NONE);
            SDL_RenderCopyEx(renderer, texteText, NULL, &dstrect, 0, NULL, SDL_FLIP_NONE);

            filledCircleRGBA(renderer, 500, 100, 70, 0x00, 0x00, 0xFF, 0xFF);
            setRendererColor(renderer, 0xFF0000FF);
            SDL_RenderFillRect(renderer, &texr);
            setRendererColor(renderer, 0);
            // flip the backbuffer
            // this means that everything that we prepared behind the screens is actually shown

            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);
        }

        SDL_DestroyTexture(img);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);

        return 0;
    }
