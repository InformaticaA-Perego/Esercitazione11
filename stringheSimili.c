/*Scrivere una funzione che riceva come input una lista di parole, e stabilisca se è formata da parole simili 
	Due parole sono simili se hanno al più due caratteri diversi 
	Versione iterativa vs versione ricorsiva 
*/
#define MAX_CARATTERI 50

/*
 A B C D E
 A B C C E
 A B A C E
 D D D C E
 */

struct node {
    char content[MAX_CARATTERI];
    struct node *next;
};

typedef struct node node;

typedef node * list;

list tailInsert(list l, char *content);
list inserisci(void);
int simili(char *parola1, char *parola2);
int simili_it(list l);
int simili_ric(list l);
void clearList(list l);

int main(int argc, const char * argv[]) {
    list parole = NULL;
    
    parole = inserisci();
    if (simili_it(parole)) {
        printf("Lista formata da parole simili\n");
    }
    else {
        printf("La lista ha parole NON simili\n");
    }
    clearList(parole);
    
    return 0;
}

list tailInsert(list l, char *content) {
    list currentTail = l;
    node *n = (node *) malloc(sizeof(node));
    n->next = NULL;
    strcpy(n->content, content);
    
    // Caso di lista inizialmente vuota
    if (l == NULL) {
        return n;
    }
    
    // Caso di lista non vuota
    while (currentTail->next != NULL) {
        currentTail = currentTail->next;
    }
    currentTail->next = n;
    return l;
}

list inserisci(void) {
    list head = NULL;
    int i, n;
    char temp[MAX_CARATTERI];
    
    printf("Quante parole? ");
    scanf("%d", &n);
    // controllare il numero di parole...
    for (i = 0; i < n; i++) {
        scanf("%s", temp);
        head = tailInsert(head, temp);
    }
    
    return head;
}

int simili(char *parola1, char *parola2) {
    int l1, l2, cont = 0, lmin, i, diff;
    
    l1 = strlen(parola1);
    l2 = strlen(parola2);
    diff = abs(l1-l2);
    if (diff > 2) {
        return 0;
    }
    if (l1 < l2)
        lmin = l1;
    else
        lmin = l2;
    for (i = 0; i < lmin; i++) {
        if (parola1[i] != parola2[i]) {
            cont++;
        }
    }
    cont += diff;
    
    if (cont > 2)
        return 0;
    else
        return 1;
}

int simili_it(list l) {
    list it = l;
    
    if (it == NULL) return 1;
    while (it->next != NULL) {
        if (!simili(it->content, it->next->content)) {
            return 0;
        }
        it = it->next;
    }
    
    return 1;
}

int simili_ric(list l) {
    if (l == NULL || l->next == NULL) {
        return 1;
    }
    else if (!simili(l->content, l->next->content)) {
        return 0;
    }
    else {
        return simili_ric(l->next);
    }
}

void clearList(list l) {
    list temp;
    while (l != NULL) {
        temp = l;
        l = l->next;
        free(temp);
    }
}
