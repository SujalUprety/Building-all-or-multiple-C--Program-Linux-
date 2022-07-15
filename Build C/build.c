#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>

char* GetExtension(char*); // to get the extension of the filename
char* GetFilename(char*);   //to get the filename without the extension of the file

int main() {

    DIR *d;
    struct dirent *dir;

    char ext[50], filename[50];
    char command[50];

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

                /*
                    Printing the details of building in termainal
                    to make sure everything is working perfectly
                */
                printf("Building %s to %s\n", dir->d_name, filename);
                
                /*
                    storing in string variable command the command 
                    which is used to build c program by buffering the values.
                */
                snprintf(command, sizeof(command), "gcc %s -o %s", dir->d_name, filename);

                /*
                    using the command stored above just to run the command in 
                    opened terminal. For now, using bash terminal.
                */
                system(command);
            }
        }
        closedir(d);
    }

    return 0;
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