/* Si definisca una struttura dati per rappresentare punti in un piano cartesiano, ed una per rappresentare linee spezzate 
	Si definiscano le seguenti funzioni: 	– Data una linea A,verificare che sia non degenere (formata da almeno 2 punti e tutti i punti sono diversi tra loro) 
	–  Date due linee A e B, verificare se B è una scorciatoia di A (iniziano e terminano nello stesso punto, ma length(B) < length(A))  

	–  Date due linee A e B, concatenazione di A e B  
	–  Data una linea A, verificarne la tortuosità (rapporto tra la lunghezza di A e la distanza tra gli estremi)  

*/

struct point {
    float x;
    float y;
    struct point *next;
};

typedef struct point point;

typedef point * line;

// Inserisce l'elemento alla fine (coda) della lista e ritorna la "nuova" lista
line tailInsert(line l, float x, float y);

// Ritorna il numero di elementi nella lista
int size(line l);

// Rimuove tutti gli elementi dalla lista
void clearList(line l);

// Stampa la lista
void printList(line l);

int non_degenere(line l);
int punti_uguali(point *p1, point *p2);
point *ultimo(line l);
float lunghezza(line l);
float distanza(point *p1, point *p2);
int scorciatoia(line a, line b);

int main(int argc, const char * argv[]) {
    
    return 0;
}

int punti_uguali(point *p1, point *p2) {
    return p1->x == p2->x && p1->y == p2->y;
}

int non_degenere(line l) {
    line it1, it2;
    
    if (size(l) < 2) {
        return 0;
    }
    it1 = l;
    while (it1 != NULL) {
        it2 = l;
        while (it2 != NULL) {
            if (it1 != it2 && punti_uguali(it1, it2)) {
                return 0;
            }
            it2 = it2->next;
        }
        it1 = it1->next;
    }
    
    return 1;
}

point *ultimo(line l) {
    line it = l;
    
    if (l == NULL) {
        return NULL;
    }
    else if (l->next == NULL) {
        return l;
    }
    else {
        while (it->next != NULL) {
            it = it->next;
        }
        return it;
    }
}

float distanza(point *p1, point *p2) {
    return sqrt((p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) * (p1->y - p2->y));
}

float lunghezza(line l) {
    line it = l;
    float ris = 0;
    
    while (it != NULL && it->next != NULL) {
        ris += distanza(it, it->next);
        it = it->next;
    }
    
    return ris;
}

int scorciatoia(line a, line b) {
    if (a == NULL || b == NULL) {
        return 0;
    }
    if (punti_uguali(a, b) &&
        punti_uguali(ultimo(a), ultimo(b)) &&
        lunghezza(b) < lunghezza(a)) {
        return 1;
    }
    else {
        return 0;
    }
}

line tailInsert(line l, float x, float y) {
    line currentTail = l;
    point *p = (point *) malloc(sizeof(point));
    p->next = NULL;
    p->x = x;
    p->y = y;
    
    // Caso di lista inizialmente vuota
    if (l == NULL) {
        return p;
    }
    
    // Caso di lista non vuota
    while (currentTail->next != NULL) {
        currentTail = currentTail->next;
    }
    currentTail->next = p;
    return l;
}

int size(line l) {
    int count = 0;
    while (l != NULL) {
        count++;
        l = l->next;
    }
    return count;
}

void clearList(line l) {
    line temp;
    while (l != NULL) {
        temp = l;
        l = l->next;
        free(temp);
    }
}

void printList(line l) {
    while (l != NULL) {
        printf("(%.2f, %.2f)\t", l->x, l->y);
        l = l->next;
    }
    printf("\n");
}
