#include <iostream>
#include <allegro.h>
#include <png.h> //le header spécifiques au plug-in png
#include <loadpng.h> //2nd header spécifiques au plug_in png
#define nbi 1

using namespace std;

int main()
{
    BITMAP *page; //pointeur sur struct BITMAP specifiques a allegro (permet le gestion des images, pages représente ici un buffer)
    BITMAP *image[nbi];
    char nfi[nbi][50]= {"doge.png"};
    FONT* font_perso;

    set_alpha_blender(); // permet de prendre en compte les paramétres alpha d'un png comme une transparence
    allegro_init(); //lancement d'allegro
    install_timer(); //lancement de la clock spécifiques a allegro
    install_keyboard(); //lancement du pilote clavier d'allegro
    register_png_file_type(); //permet d'assimiler le codec png comme un codec bitmap et de l'utilisé dans allegro (plug-in d'allegro 4)
    set_color_depth(desktop_color_depth()); //créer une instance graphique spécifiques a l'harware de l'user

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,640,480,0,0)!=0)//detection d'erreur du lancement d'allegro
    {
        allegro_message("prb gfx mode"); //message d'erreur
        allegro_exit(); //fermeture d'allegro
        exit(EXIT_FAILURE); //fermeture du programme
    }

    page=create_bitmap(SCREEN_W,SCREEN_H);

    for (int i=0; i<nbi; i++)
        {

            image[i]=load_bitmap(nfi[i],NULL);
            cout << "chargez" ;

            if (!image[i])
            {
                allegro_message("pas pu trouver/charger %s", nfi[i]);
                allegro_exit();
                exit(EXIT_FAILURE);
            }
        }

    font_perso=load_font("petyka_72.pcx",NULL,NULL);
    if(font_perso==NULL)
    {
        allegro_message("pas pu trouver/charger font");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    blit(image[0],screen,0,0,0,0,SCREEN_W,SCREEN_H);
    int col=makecol(127,127,127);
    textout_centre_ex(screen,font_perso,"hello world",SCREEN_W/2,SCREEN_H/2,col,makecol(255,255,255));

    while(!key[KEY_ESC]);

    return 0;
}
END_OF_MAIN();
