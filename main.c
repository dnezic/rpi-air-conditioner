#include "mitsu.h"


int main(int argc, char *argv[]) {
    
    if(argc != 4) {
        printf("Usage: #>sudo mitsu <temp> <on> <operation>\n");
        printf("\t<temp> = 16, ... 31\n");
        printf("\t<on> = 1=ON | 0=OFF\n");
        printf("\t<operation> = 0=HEATING | 1=DEHUMIDIFY | 2=COOLING\n");
        printf("\nExample for heating 22C:\n\t#>sudo mitsu 22 1 0\n");
    }
    
    send(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    
    printf("Command sent.\n");
    
    return 0;
}
