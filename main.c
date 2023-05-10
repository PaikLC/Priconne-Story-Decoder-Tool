#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

const char *help =
    "\n"
    "This program is to deserialize the story text of Princess Connect Re:Dive\n"
    "and should work to all the data servers?\n\n"
    "%s -p \"path/to/the/storydata.bytes\" [-o \"path/to/output/the/result\"] options\n\n" // %s is to the name of the program (argv[0])...
    "Arguments:\n"
        "\t-p           The path to the file to deserialize\n"
        "\t-o           The path to the directory to save de result\n\n"
        "\t--all-text   Put in a txt file all the details of the file\n"
;


int main(int argc, char *argv[])
{
    char *pathOpen = NULL, *pathSave = NULL;
    bool tmp = false;

    if (argc == 1)
    {
        printf(help, argv[0]);
        return EXIT_FAILURE;
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
                if (strcmp(argv[i], "--all-text") == 0)
                {
                    tmp = true;
                }
            }
            break;

        default:
            break;
        }
    }
    

    return EXIT_SUCCESS;
}