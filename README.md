# Building-all-or-multiple-C-Programs-Linux
This program will build all, or only one or multiple C programs in the current directory.

Here is the all the details of this program.

But before this, let's make this program as a linux command.

Copy paste this in terminal after going into this program directory:
```
sudo cp build "//bin"
```


Usage: build [Option]... [Filename of c program]...[Filename to build program]...


Example: 
```
build test.c testing hello.c hola hi.c
```


Options:
--help  -h      PrintUsage


Using command only build will build all the c programs files stored in that current directory
Example: 
```
build
```
Can build multiple c programs at once and if the filename in which the build should be saved is not given then it will be saved as the same name as the c program without extension
Example: 
```
build test.c testing hello.c hi.c hola
```
This command will build test.c to testing, hello.c to hello because no filename is given for this and hi.c to hola
