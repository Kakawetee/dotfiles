// GNUko extensioak aktibatzen ditu
#define _GNU_SOURCE
#include <stdio.h>         // fprintf, perror, fdopen, getline, fputs, fflush
#include <stdlib.h>        // getenv, free
#include <string.h>        // strncpy, strlen
#include <sys/socket.h>    // socket, connect
#include <sys/un.h>        // struct sockaddr_un (sockets Unix)
#include <unistd.h>        // write

int main (void) {

    // NIRI_SOCKET ingurune aldagaia exportatu, Unix socket-aren helbidea eskuratuz
    const char *path = getenv("NIRI_SOCKET");
    if (!path) { fprintf(stderr, "NIRI_SOCKET on definido\n"); return 1;}
    
    // AF_UNIX: Unix domeinuko socket-a
    // SOCK_STREAM: Byte fluxua, konexiora zuzendua (TCP bezala)
    // 0: defektuzko protokoloa
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);

    // perror(): [ "socket" + ": " + errno + \n ]
    if (fd < 0) { perror("socket"); return 1; }

    // sa_family_t sun family    : Helbide mota, beti AF_UNIX
    // char        sun_path[108] : Socket-aren fitxategiari helbidea
    struct sockaddr_un addr = { .sun_family = AF_UNIX }; 
    strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);
    
    // &addr eskuratzeko casting-a egin behar da, horrekin batera, socket-a eta byte kopurua pasatzen zaio
    if (connect(fd, (struct sockaddr *)&addr, sizeof addr) < 0) {
        // perror(): [ "connect" + ": " + errno + \n ]
        perror("connect"); return 1;
    }
   

    // \" C lengoaian " karakterea adierazteko erabiltzen da 
    const char *req = "\"EventStream\"\n";
    // Socketean "EventStream" idatzi, Nirik- ulertzen duen eskaeretako bat da
    // Honi, {"Ok":"Handled"} 
    if (write(fd, req, strlen(req)) < 0 ) { perror("write"); return 1; }

    // read() funtzioa erabili nahi badugu, byte blokeak jasoko ditugu
    // Erosoa ez denez, fitxategi batean ezarri eta getline() bezalako funtzioak erabili
    FILE *f = fdopen(fd, "r");

    char *line = NULL;
    size_t cap = 0;
    // Hasieraketa balio horiekin getline()-ek buferra bere kabuz erreserbatzen ditu
    while (getline(&line, &cap, f) != -1) {
        // Lehen \n arte lortutako byteak inprimatu
        fputs(line, stdout);
        // Berehala idaztea behartzen du, buffera husteko 
        fflush(stdout);
    }

    free(line);
    return 0;
}
