#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>

char* GetExtension(char*); // to get the extension of the filename
char* GetFilename(char*);   //to get the filename without the extension of the file

void BuildAllProgram(); //to build all the c programs in a directory
void BuildOneProgram(); //to build only one file with only one arguement in command with C file name

void BuildFile(char*, char*); //to build the file one by one by calling this function

void Help();

int main(int argc, char **argv) {

    if(argc > 1) {

        if(argv[1][0] == '-') {
            if(strcmp(argv[1], "--help") == 0 || strcmp(argv[1],"-h") == 0) 
                Help();
            else
                printf("Invalid Option\n");

            return 0;
        }

        for(int i = 1; i < argc; i++) {
            if(argv[i+1] != NULL){    
                if(strcmp(GetExtension(argv[i+1]), ".c") != 0) {
                    BuildFile(argv[i-1], argv[++i]);
                    continue;
                }
            }
            BuildOneProgram(argv[i]);
        }
    }
    else 
        BuildAllProgram();

    return 0;
}

void BuildAllProgram() {

    DIR *d;
    struct dirent *dir;

    char ext[50], filename[50];

    d = opendir(".");

    if(d) {

        //Getting all the files in this current directory

        while ((dir = readdir(d)) != NULL) {

            strcpy(ext, GetExtension(dir->d_name));
            
            //checking if the file is c program or not

            if((strcmp(ext, ".c")) == 0) {

                /*
                    there are some files like . .. if u can check by command ls -a on linux.
                    so neglecting those files.
                */

                if(dir->d_name[0] == '.')  continue;

                /*
                    neglecting this c program to be build again.
                    because rebuilding the program that is running currently
                    will make some error.
                */
                if(strcmp(dir->d_name, "build.c") == 0) continue;

                strcpy(filename, GetFilename(dir->d_name));
                BuildFile(dir->d_name, filename);
            }
        }
        closedir(d);
    }
    
}

void BuildOneProgram(char* programname) {
    char ext[50], filename[50];

    strcpy(ext, GetExtension(programname));

    if(strcmp(ext, ".c") != 0) {
        printf("Not a C program file\n");
        return;
    }

    strcpy(filename, GetFilename(programname));
    BuildFile(programname, filename);
    
}

void BuildFile(char* programname, char* filename) {

    char command[50];


    /*
        Printing the details of building in termainal
        to make sure everything is working perfectly
    */
    printf("Building %s to %s\n", programname, filename);

    /*
        storing in string variable command the command 
        which is used to build c program by buffering the values.
    */
    snprintf(command, sizeof(command), "gcc %s -o %s", programname, filename);

    /*
        using the command stored above just to run the command in 
        opened terminal. For now, using bash terminal.
    */
    system(command);
}

void Help() {
    printf("Usage: build [Option]... [Filename of c program]...[Filename to build program]...\n");
    printf("Example: build test.c testing hello.c hola hi.c\n");
    printf("Options:\n--help\t-h\tPrintUsage\n");
    printf("Using command only build will build all the c programs files stored in that current directory\n");
    printf("Example: build\n");
    printf("Can build multiple c programs at once and if the filename in which the build should be saved is not given then it will be saved as the same name as the c program without extension\n");
    printf("Example: build test.c testing hello.c hi.c hola\n");
    printf("This command will build test.c to testing, hello.c to hello because no filename is given for this and hi.c to hola\n");
}

char* GetExtension(char* name) {
    static char extension[50];

    for(int i = 0; i < 50; i++)
        extension[i] = '\0';

    for(int i = 0, c = 0; i < strlen(name); i++) {
        if(name[i] == '.' || c != 0) {
            extension[c] = name[i];
            c++;
        }
    }

    return extension;
}

char* GetFilename(char* name) {
    static char filename[50];

    for(int i = 0; i < 50; i++)
        filename[i] = '\0';

    for(int i = 0, c = 0; i < strlen(name); i++) {
        if(name[i] == '.' || c != 0)    break;
        
        filename[i] = name[i];
    }

    return filename;
}