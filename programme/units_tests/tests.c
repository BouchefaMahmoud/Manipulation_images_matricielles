
#include "../src/views/screen/screen.h"
#include "../src/views/pixels/pixels.h"
#include <check.h>

/*
START_TEST(isdigitSTRING)
{
    char *s = "12356";
    int n = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (isdigit(ch[i]) == 0)
            n++;
    }
    ck_assert_int_eq(n,0);
}END_TEST;
*/

START_TEST(op_pars){

    char * c1 ="select 100 100 100 100";
    options op ;

    parser(&op, c1);
    ck_assert_int_eq(op.select.h, 100);
    ck_assert_int_eq(op.select.w, 100);
    ck_assert_int_eq(op.select.x, 100);
    ck_assert_int_eq(op.select.y, 100);

    char * c2 = "replaceColor 255 255 255 100 100 100 10";
    parser(&op, c1);
    ck_assert_int_eq(op.couleur.r, 255);
    ck_assert_int_eq(op.couleur.g, 255);
    ck_assert_int_eq(op.couleur.b, 255);
    ck_assert_int_eq(op.couleur2.r, 100);
    ck_assert_int_eq(op.couleur2.g, 100);
    ck_assert_int_eq(op.couleur2.b, 100);

 
}END_TEST;



START_TEST(size)
{

    char *commande = "screen 700 700";

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_ExitWithError("Erreur d'initialisation de la SDL");
    }

    options op;
    op.flag = -1;

    parser(&op, commande);
    init_screen(op.taille_fenetre, "test1");

    screen *s = _get_screens();

    ck_assert_int_eq(s->surface_principale->h, 700);
    ck_assert_int_eq(s->surface_principale->w, 700);

    fermer_fenetre();
    SDL_Quit();
}
END_TEST;




// START_TEST(ctrl_z_test)
// {

//     if (SDL_Init(SDL_INIT_VIDEO) != 0)
//     {
//         SDL_ExitWithError("Erreur d'initialisation de la SDL");
//     }
//     char *commande = "screen 700 700";

//     options op;
//     op.flag = -1;
//     parser(&op, commande);
//     screen *s = _get_screens();
//     init_screen(op.taille_fenetre, "test1");
//     SDL_Surface * debut = SDL_GetWindowSurface(s->window);
//     sym_h();
//     ctrl_z();
//     sym_h();
//     ctrl_z();
//     SDL_Surface * fin = SDL_GetWindowSurface(s->window);

//     Uint32 *pixels = (Uint32 *)debut;
//     Uint32 *pixels2 = (Uint32 *)fin;

//     for(int y = 0 ; y < 700; y++ ){
//         for(int x = 0 ; x < 700; x++ ){
//             ck_assert_int_eq( pixels[y * 700 + x], pixels2[y * 700 + x]);
//         }
//     }

//     fermer_fenetre();
//     SDL_Quit();
// }
// END_TEST;

int main()
{

    TCase *init, *cntz, *sel, * parsing;
    Suite *s;
    SRunner *sr;
    init = tcase_create("init_screen");
    sel = tcase_create("select");
    parsing = tcase_create("parse");

    tcase_add_test(init, size);
    tcase_add_test(parsing, op_pars);
    
    // tcase_add_test(sel,select_z );
    // cntz = tcase_create("cntz");
    // tcase_add_test(cntz, ctrl_z_test);

    s = suite_create("screens");

    suite_add_tcase(s, init);
    suite_add_tcase(s, sel);
    suite_add_tcase(s, parsing);
    
    
    // suite_add_tcase(s, cntz);

    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);

    printf("%d\n", srunner_ntests_failed(sr) == 0 ? 0 : 1);

    return 0;
}