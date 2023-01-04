EXECUTE :: windres my.rc -O coff -o my.res

COMPILE :: g++ main.cpp  my.res
OR
COMPILE :: g++ main.cpp  my.res -o WORDLE