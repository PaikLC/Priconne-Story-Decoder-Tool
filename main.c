#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include ".\lib\base64\b64.h"
#include ".\lib\deserializer\deserializer.h"
#include "main.h"

const char *help =
    "\n"
    "This program is to deserialize the story text of Princess Connect Re:Dive\n"
    "and should work to all the data servers?\n\n"
    "%s -p \"path/to/the/storydata.bytes\" [-o \"path/to/output/the/result\"] options\n\n" // %s is to the name of the program (argv[0])...
    "Arguments:\n"
        "\t-p                   The path to the file to deserialize\n"
        "\t-o                   The path to the directory to save de result\n"
        "\t\n" //More simple commands??
    "Long arguments\n"
        "\t--all-data           Put in a txt file all the details of the file\n"
        "\t--only-category CAT  Just save the specifided category command\n"
        "\t                     Posible str: NON, SYS, MOT, EFC\n"
        "\t                     NON: for uncategorized category\n"
        "\t                     SYS: for System category\n"
        "\t                     MOT: for Motion category\n"
        "\t                     EFC: for Effect category\n\n"
        "\t--only-cat-number N  Just save the specified category number\n"
        "\t                     They are 112 but the starts form -1 to 110\n"
        "\t                     For more details see the source code or docs\n" // Docs if I have the time... and motivation
;

const char *none = " "; 

void saveResult(char *path, ARGS *story)
{
    FILE *save = fopen(path, "wt");
    ARGS *aux = story;
    extraArgu *extra = story->extra;

    unsigned char *readable = NULL;

    if (save == NULL)
    {
        return;
    }
    

    while (aux != NULL)
    {
        if (aux->argument != NULL && aux->nextArgument != NULL)
        {
            readable = b64_decode(aux->argument, strlen(aux->argument));
            fprintf(save, "[%s][%s] %s\n", catCommand[aux->command.Bytes.category], catNumber[aux->command.Bytes.number + 1], readable);
            free(readable);
        }
        else
        {
            fprintf(save, "[%s][%s] %s\n", catCommand[aux->command.Bytes.category], catNumber[aux->command.Bytes.number + 1], none);
        }
        fflush(save);

        while (extra != NULL && aux->nextArgument != NULL)
        {
            readable = b64_decode(extra->argument, strlen(extra->argument));
            fprintf(save, "\t%s\n", readable);
            fflush(save);

            free(readable);

            extra = extra->nextArgument;
        }
        
        aux = aux->nextArgument;
        if (aux != NULL)
        {
            extra = aux->extra;
        }
        else
        {
            extra = NULL;
        }
    }
    fclose(save);
}

int main(int argc, char *argv[])
{
    char *pathOpen = NULL, *pathSave = NULL;
    bool tmp = false;

    ARGS story = { 0 };

    if (argc == 1)
    {
        printf(help, argv[0]);
        return EXIT_SUCCESS;
    }
    
    for (int i = 1; i < argc; i++)
    {
        switch (argv[i][1])
        {
        case 'p':
            pathOpen = argv[i + 1];
            break;
        
        case 'o':
            pathSave = argv[i + 1];
            break;

        case '-':
            {
                if (strcmp(argv[i], "--all-data") == 0)
                {
                    tmp = true;
                }
            }
            break;

        default:
            break;
        }
    }
    
    if (pathSave == NULL)
    {
        char *pdest = NULL;
        pathSave = (char *)malloc( sizeof(char) * strlen(pathOpen) + 1 );
        if (pathSave == NULL)
        {
            return EXIT_FAILURE;
        }
        
        strncpy(pathSave, pathOpen, strlen(pathOpen));
        pdest = strrchr(pathSave, '.');
        if (pdest == NULL)
        {
            pathSave = (char *)realloc(pathSave, strlen(pathOpen) + 5);
            strcat(pathSave, ".txt");
        }
        else
        {
            strncpy(pdest, ".txt", 5);
        }
        
    }

    if(deserializeFile(pathOpen, &story) == 0)
    {
        printf("Error Something happend...\n");
        system("pause");
        freeArguments(&story);
        return EXIT_FAILURE;
    }
    
    saveResult(pathSave, &story);

    freeArguments(&story);
    free(pathSave);
    return EXIT_SUCCESS;
}