#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char **argv) {
    char input[256];

    while(1) {

        printf("LUSC> ");

        if (!fgets(input, sizeof(input), stdin)){
            printf("\n");
            return 0;
        }

        printf("result: %s", input) ;
        while (strcspn(input, "\n") == strlen(input)) {
            if (!fgets(input, sizeof(input), stdin))
                printf("\n");
                return 0 ;
            printf("%s", input);
        }
        printf("\n");        
    }

    return 0;
}