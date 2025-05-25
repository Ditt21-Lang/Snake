#include<stdio.h>
#include <string.h>

int main(){
    char ptr[20];
    printf("silahkan masukan karakter=");
    fgets(ptr,20,stdin);
    printf("%s",ptr);
}