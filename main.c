#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <SDL/SDL.h>


#include "field_works.h"
#include "observer.h"

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
    #include <stdbool.h>
#endif



int main ( int argc, char** argv )
{
    /*****************Init the field**************************/
    /***************** GLOBAL VARIABLES **********************/
        uint32_t iterations = 0;
        field_of_arrows field;

    /***************** PROGRAMM CODE *************************/
    /***************** INIT PHASE ****************************/
        printf("Field(s) starting screen!\n");
        printf("Press enter to continue.\n");
        getchar();


        init_field(&field);

    /***************** PROGRAM PHASE**************************/
    clear_screen();

    /*********************************************************/

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // load an image
    SDL_Surface* bmp_right = SDL_LoadBMP("arrow_right.bmp");
    if (!bmp_right)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }


    // program main loop
    bool done = false;
    while (!done)
    {
    {   /************field work*****************************/
        clear_screen();
        iterations++;
        printf("Iterationcounter: %d\n", iterations);
        update_field(&field);
    }

        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing
        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 255, 255));
        // DRAWING STARTS HERE

        munch_the_field(screen, &field);

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_UpdateRect(screen, 0, 0, 0, 0);
        //SDL_Flip(screen);


        SDL_Delay(100);
    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(bmp_right);

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
