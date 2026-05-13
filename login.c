#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char *expected_password = "boogeyman";

int main()
{
    char *password = calloc(100, sizeof(char));
    
    printf("Enter password:\n");
    scanf("%s", password);
    if ( strcmp(password, expected_password) == 0 )
    {
        printf("Success!\n");
    }
    else
    {
        printf("Failure.\n");
    }
}
