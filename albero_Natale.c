/*Scrivere un programma che, attraverso una lista, permette di gestire le luci dell’albero di natale.
	La lista contiente:
		- Il numero del led;
		- Il colore
		- la posizione X
		- la posizione Y
		- Acceso o spento.

	Il programma permette di:
		- Collegare un nuovo led in ordine crescente
		- Scollegare un led dalla coda
		- Switchare led accesi con led spenti
		- Creare una lista contenente solo i led rossi;
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int nLed;
    char colore;
    int x;
    int y;
    char stato[4];
    struct nodo *next;
} nodo;

typedef nodo *ptrNodo;

ptrNodo collegaLed(ptrNodo lista, int nLed);
ptrNodo scollegaLed(ptrNodo lista);
ptrNodo creaLista(ptrNodo lista);
ptrNodo addLedToList(ptrNodo lista, int nLed, char colore, int x, int y, char stato[]);
void  switchOnOff(ptrNodo albero);
void stampaLed(ptrNodo lista);

int main(int argc, const char * argv[]) {
    ptrNodo albero = NULL;
    ptrNodo ledRossi = NULL;
    int c, nLed;
    
    do{
        printf("\nMenu\n");
        printf("1) Collega led\n");
        printf("2) Scollega led in fondo\n");
        printf("3) Switch ON/OFF\n");
        printf("4) Crea lista led rossi\n");
        printf("5) Stampa\n\n");
        printf(">> ");
        scanf("%d",&c);
        switch(c){
            case 1:
                printf("Inserisci il numero del led: ");
                scanf("%d",&nLed);
                albero = collegaLed(albero, nLed);
                break;
            case 2:
                albero = scollegaLed(albero);
                break;
            case 3:
                switchOnOff(albero);
                break;
            case 4:
                ledRossi = creaLista(albero);
                break;
            case 5:
                stampaLed(albero);
                printf("\n\nLED ROSSI:\n");
                stampaLed(ledRossi);
                break;
        }
    }while(c!=0);
    return 0;
}

ptrNodo collegaLed(ptrNodo lista, int nLed){
    ptrNodo led;
    if (lista != NULL && lista->nLed < nLed){
        lista->next = collegaLed(lista->next, nLed);
        return lista;
    }
    else{
        led = (ptrNodo)malloc(sizeof(nodo));
        led->nLed = nLed;
        printf("Inserisci colore: ");
        fpurge(stdin);
        scanf("%c",&led->colore);
        printf("Inserisci x: ");
        scanf("%d",&led->x);
        printf("Inserisci y: ");
        scanf("%d",&led->y);
        printf("Inserisci stato: ");
        fpurge(stdin);
        scanf("%s",led->stato);
        if (lista==NULL)
            led->next = NULL;
        else
            led->next = lista;
        return led;
    }
}

ptrNodo scollegaLed(ptrNodo lista){
    ptrNodo temp;
    if (lista == NULL)
        return NULL;
    if (lista->next==NULL)
    {
        free(lista);
        return NULL;
    }
    if (lista->next->next==NULL)
    {
        temp = lista->next;
        lista->next = NULL;
        free(temp);
        return lista;
    }
    else
    {
         lista->next = scollegaLed(lista->next);
        return lista;
    }
    
}

ptrNodo creaLista(ptrNodo lista){
    ptrNodo newLista = NULL;
    if (lista==NULL)
        return NULL;
    else{
        if ((lista->colore=='R') || (lista->colore=='r')){
            newLista = addLedToList(newLista, lista->nLed, lista->colore, lista->x, lista->y, lista->stato);
            newLista->next = creaLista(lista->next);
        }
        else
            newLista = creaLista(lista->next);
        return newLista;
    }
    
}

void  switchOnOff(ptrNodo albero)
{
    if (albero==NULL)
        return;
    else{
        if (strcmp(albero->stato,"ON")==0)
            strcpy(albero->stato,"OFF");
        else if (strcmp(albero->stato,"OFF")==0)
            strcpy(albero->stato,"ON");
        switchOnOff(albero->next);
        return;
    }
}

void stampaLed(ptrNodo lista){
    if (lista==NULL)
        return;
    else
    {
        printf("LED: %d\nCOLORE: %c\nX: %d Y: %d\nSTATO: %s\n",lista->nLed,lista->colore,lista->x,lista->y,lista->stato);
        stampaLed(lista->next);
    }
    
}

ptrNodo addLedToList(ptrNodo lista, int nLed, char colore, int x, int y, char stato[]){
    ptrNodo led;
    if (lista != NULL && lista->nLed < nLed){
        lista->next = addLedToList(lista->next, nLed, colore, x, y, stato);
        return lista;
    }
    else{
        led = (ptrNodo)malloc(sizeof(nodo));
        led->nLed = nLed;
        led->colore = colore;
        led->x = x;
        led->y = y;
        strcpy(led->stato,stato);
        if (lista==NULL)
            led->next = NULL;
        else
            led->next = lista;
        return led;
    }
}

