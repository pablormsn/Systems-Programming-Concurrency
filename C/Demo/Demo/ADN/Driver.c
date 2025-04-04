#include "ADN.h"
#include <stdio.h>
int main(void){
     setvbuf(stdout, NULL, _IONBF, 0);
    Chain chain1;

    emptyChain(&chain1);
    
    char f1[] = "AAAA";
    char f2[] = "ACGT";
    if (addFragment(&chain1, f1, 4)){
        printf("Fragment added\n");
    }else{
        printf("Unable to add fragment\n");
    }
    if (addFragment(&chain1, f1, 8)){
        printf("Fragment added\n");
    }else{
        printf("Unable to add fragment\n");
    }
    if(addFragment(&chain1, f1, 12)){
        printf("Fragment added\n");
    }else{
        printf("Unable to add fragment\n");
    }

    showChain(chain1);
    if (addFragment(&chain1, f2, -1)){
        printf("Fragment added\n");
    }else{
        printf("Unable to add fragment\n");
    }
    if (addFragment(&chain1, f2, 1)){
        printf("Fragment added\n");
    }else{
        printf("Unable to add fragment\n");
    }
    if(addFragment(&chain1, f2, 5)){
        printf("Fragment added\n");
    }else{
        printf("Unable to add fragment\n");
    }

    showChain(chain1);

    //saveToFile("adnTest.bin", chain1);

    destroyChain(&chain1);
    printf("Chain destroyed\n");
    showChain(chain1);

    loadFromFile("adnTest.bin", &chain1);
    printf("Chain loaded from file:\n");
    showChain(chain1);

    int count = cut(&chain1,"AAAA");
    printf("Cut AAAA - removed fragments: %d\n", count);
    showChain(chain1);
    destroyChain(&chain1);

    loadFromFile("adnTest.bin", &chain1);
    printf("Chain loaded from file:\n");
    showChain(chain1);
    /*count  = extract(&chain1, 5);
    printf("Extract fragment 5 - extracted fragments: %d\n", count);
    showChain(chain1);
    count  = extract(&chain1, 1);
    printf("Extract fragment 1 - extracted fragments: %d\n", count);
    showChain(chain1);
    destroyChain(&chain1);*/

}