/*(10pt) Napisz w języku C własną implementacje funkcji printf i scanf (nazwijmy je myprintf i myscanf). 
Funkcje nie mogą wykorzystywać, żadnych funkcji bibliotecznych (atoi, fprintf, fscanf itp.) oraz makr va_start, va_arg i va_end 
(np. możesz skorzystać z wyjaśnienia tutaj oraz patrz X86 calling conventions i dokładniej cdecl) oraz można wykorzystać wywołania systemowe 
read i write z odpowiednim standardowym deskryptorem. Program należy skompilować na maszynę 32-bitową tzn. gcc -m32 np. dla 64-bitowego 
systemu ArchLinux trzeba zainstalować pakiet gcc-multilib z repozytorium multilib. W funkcjach wystarczy zaimplementować 
"%s", "%d", "%x" i "%b", gdzie w naszej implementacji "%s" wyświetla ciąg znaków, "%d" liczbę w systemie dziesiętnym, "%x" liczbę w systemie 
szesnastkowych oraz "%b" liczbę w systemie binarnym.*/
//compile: gcc -o io -m32 -lm -fno-stack-protector

#include<string.h>
#include<stdlib.h>
#include<unistd.h>

char* int2string(int integer) {
    static char out[100];
    char* ptr;

    ptr = &out[99]; 
    *ptr = '\0'; 

    //Wytnij po kolei cyfry
    while(integer) {
        *--ptr = '0' + (integer % 10);
        integer /= 10;
    }

    return ptr;
}

char* bin2string(int bin) {
    static char out[400];
    char* ptr;

    ptr = &out[399];
    *ptr = '\0';

    while(bin){
        *--ptr = '0' + (bin % 2);
        bin /= 2;
    }
    return ptr;
}

char* hex2string(int hex) {
    static char out[80];
    char* ptr;

    ptr = &out[79];
    *ptr = '\0';

    while(hex) {
        int rem = hex % 16;
        if(rem < 10)
            *--ptr = '0' + rem;
        else
            *--ptr = 'A' + rem - 10;
            hex /= 16;    
    } 
    return ptr;
}

void myprintf(char* main, ...) {

    //Pointer wskazujący na parametry
    char *p = (char *) &main + sizeof(main);

    for(int i = 0; i < strlen(main); i++) {
        if(main[i] == '%') {
            switch (main[i+1]) {
            case 's': {
                char* string;
                string = *((char **) p); //Take string
                p += sizeof(char*); //Move pointer to next parameter
                while (string[0] != '\0') {
                    write(1, string, sizeof(char));
                    string++;
                }
                i+=2;
                break;
            }
            case 'd': {
                int integer = *((int*) p);
                p += sizeof(int);
                write(1, int2string(integer), sizeof(char*));
                i+=2;
                break;
            }
            case 'b': {
                int bin = *((int*) p);
                p += sizeof(int);
                write(1, bin2string(bin), sizeof(char*)*100);
                i+=2;
                break;
            }
            case 'x': {
                int hex = *((int*) p);
                p += sizeof(int);
                write(1, hex2string(hex), sizeof(char*));
                i+=2;
                break;
            }
            
            default:{
                write(1, &main[i], 1);
                break;
                }
            }
        }
        write(1, &main[i], 1);
    }
    p = NULL;
}

int str2int(char* string, int base) {
    static char digits[]= "0123456789ABCDEF";
    char* ptr = &string[strlen(string)];
    int integer = 0;
    int mult = 1;

    //printf("POINTER: %d\n",strlen(string));
    for(int i = strlen(string)-1; i >= 0; i--) {
        char tmp = (*--ptr);
        for(int i = 0 ; i < base; i++) {
            if(tmp == digits[i]) {
                integer += i * mult;
            }
        }
        
        mult *= base;
    }
    return integer;
}

void myscanf(char* format, ...) {
    char* p = (char *) &format + sizeof format;

    for(int i = 0; i < strlen(format); i++ ) {
        char* input = calloc(1024,sizeof(char));
        int bytes = read(0,input,1024);
    
        if (input[bytes - 1] == '\n') input[bytes-1] = '\0';
	    input[bytes] = '\0';

        if(format[i] == '%') {
            int* in;
            char** inStr;
            switch(format[i+1]){
                case 'x':
                    in = (int*)(*(int*)p);
                    p += sizeof(int*);
                    *in = str2int(input,16);
                    i+=2;
                    break;
                case 'd':
                    in = (int*)(*(int*)p);
                    p += sizeof(int*);
                    *in = str2int(input,10);
                    i+=2;
                    break;
                case 'b':
                    in = (int*)(*(int*)p);
                    p += sizeof(int*);
                    *in = str2int(input,2);
                    i+=2;
                    break;
                case 's':
                    inStr = (char**)(*(char**)p);
                    *inStr = input;
                    p += sizeof(*inStr);
                    i+=2;
                    break;
            }
        }
    }
}

int main (int argc, char* argv[]) {

    char* sample = "SAMPLE";
    
    myprintf("Print string: %s %s \n", "text1",sample);
    myprintf("Print int: %d\n", 2021);
    myprintf("Print (string, int, bin, hex): (%s, %d, %b, %x)\n",sample,1999, 1999, 64);
    myprintf("Print percentage: %%%\n");

    int d,b,x;
    char* scanned;
    myprintf("Put: string, decimal, binary, hexadecimal\n");
    myscanf("%s %d %b %x",&scanned, &d,&b,&x);
    myprintf("Scanned (int, bin, hex): (%d, %d, %d)\n",d,b,x );
    myprintf("Scanned string: %s ", scanned);
    
    return 0;
}