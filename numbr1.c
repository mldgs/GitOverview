#include <stdio.h>

int show_menu1();


int main(){
    int option;


    while (option != 7)
    {
        option = show_menu1();
        printf("%d", option);


    }


    return 0;
}

int show_menu1(){
    int way;
    way = -1;
    while (way<0 || way>7){
        puts("Press:");
        puts("0 - information about program");
        puts("1 - add card");
        puts("2 - edit card");
        puts("3 - delete card");
        puts("4 - output all cards");
        puts("5 - find cards by parameter");
        puts("6 - sort cards by parameter");
        puts("7 - exit");

        scanf("%d", &way);
        if (way<0 || way>7)
            {
                puts("r u dumb?");
            }
    }
    return way;
}
