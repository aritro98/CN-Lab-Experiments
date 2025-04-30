#include <stdio.h>
int checkEndianness(){
    unsigned int num=1;
    char *bytePtr=(char*)&num;
    return (*bytePtr ==1);
}
unsigned int swapEndianness(unsigned int num){
    return ((num>>24) & 0xFF) | ((num>>8) & 0xFF00) |
           ((num<<8) & 0xFF0000) | ((num<<24) & 0xFF000000);
}
int main(){
    unsigned int inputNum;
    printf("Enter an integer:");
    scanf("%u",&inputNum);
    if (checkEndianness())
        printf("Host machine is little endian.\n");
    else
        printf("Host machine is big endian.\n");
    char *bytePtr=(char*)&inputNum;
    for (int i=0;i<sizeof(inputNum);++i){
        printf("Byte %d:0x%02X\n",i,bytePtr[i]);
    }
    unsigned int swappedNum=swapEndianness(inputNum);
    printf("Swapped value:%u\n",swappedNum);
    return 0;
}
