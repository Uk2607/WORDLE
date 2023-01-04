# WORDLE
#### _by **Utkarsh Kumawat**_
This is a personal version of WORDLE by NYT created in **C++** and built for learning and fun purpose.

## Features
- Get a random word each time you finish one
- Don't have to wait for a day to solve another wordle
- Says you whether the word contains duplicate letters
- Saves history in a file

## Tech
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)

## Installation
- Must have a compile, like [GCC], to translate the C++ code
- A editor like [VS Code]

## Setup project
> In my.rc you can change the path of icon if you want to change it
> After doing that execute the following command :

```sh
windres my.rc -O coff -o my.res
```

> Compiling here is bit different
> Use the following command to compile the project
```sh
g++ main.cpp  my.res
```
#### OR
> If you want to give name to executable file then:
```sh
g++ main.cpp  my.res -o WORDLE
```

## License

MIT

**Free Software, Hell Yeah!**

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)

   [C++]: <https://cplusplus.com/>
   [GCC]: <https://www.geeksforgeeks.org/complete-guide-to-install-c17-in-windows/>
   [VS Code]: <https://code.visualstudio.com/download>
