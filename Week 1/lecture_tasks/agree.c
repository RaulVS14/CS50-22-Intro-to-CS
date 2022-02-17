#include <cs50.h>
#include <stdio.h>

int main(void){
    char confirm = get_char("Do you agree? ");
    if(confirm == 'y' || confirm == 'Y'){
        printf("You agree. Wise choice.\n");
    } else if(confirm == 'n' || confirm == 'N') {
        printf("You disagree. You chose poorly.\n");
    }
}