#include "doubly_linked_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct doubly_linked_list_t *dll_create() { // Utworzenie listy wraz z alokacją, w przypadku niepowodzenia zwracany jest NULL
    struct doubly_linked_list_t *dll = malloc(sizeof *dll);
    if (dll != NULL) {  // Jeśli udało się zaalokować to początkowe wartości wskaźników są ustawione na nulle
        dll->head = NULL;
        dll->tail = NULL;
    }
    return dll;
}

int dll_push_back(struct doubly_linked_list_t *dll, int value) {
    if (dll == NULL) {  // Jeśli wskaźnik na listę jest nullem to zwracany jest kod błędu 1
        return 1;
    }
    struct node_t *node = malloc(sizeof *node);
    if (node == NULL) { // Jeśli nie udało się zaalokować pamięci na nowy element, to zwracany jest kod błędu 2
        return 2;
    }
    if (dll->tail != NULL) {    // Jeśli lista ma ostatni element, to nowo utworzony jest po nim, więc ustawiony jest jego wskaźnik
        dll->tail->next = node;
    }
    node->prev = dll->tail; // Poprzednim elementem nowego elementu jest ostatni element listy (nawet jeśli jest nullem)
    node->next = NULL;  // Nowy element nie ma następnego elementu, bo jest na końcu
    node->data = value; // Ustawienie wartości
    dll->tail = node;   // Nowy element staje się ostatnim
    if (dll->head == NULL) {    // Jeśli lista nie ma pierwszego elementu, to ten nim się staje (lista  jednym elementem jest jednocześnie główą i ogonem listy)
        dll->head = node;
    }
    return 0;   // 0 oznacza brak błędu
}

int dll_push_front(struct doubly_linked_list_t *dll, int value) {   // Wszystko analogicznie jak funkcja wyżej, tylko dodawnie na początek listy
    if (dll == NULL) {
        return 1;
    }
    struct node_t *node = malloc(sizeof *node);
    if (node == NULL) {
        return 2;
    }
    node->data = value;
    node->next = dll->head;
    node->prev = NULL;
    if (dll->head != NULL) {
        dll->head->prev = node;
    }
    dll->head = node;
    if (dll->tail == NULL) {
        dll->tail = node;
    }
    return 0;
}

int dll_pop_front(struct doubly_linked_list_t *dll, int *err_code) { // Funkcja pobiera wskaźnik na błąd, ponieważ sama zwraca wartość elementu
    if (dll == NULL || dll->head == NULL) { // jeśli lista jest nullem, bądź nie ma przodu (jest pusta)
        if (err_code != NULL) *err_code = 1;
        return 0;
    }
    struct node_t *tmp = dll->head; // Zapis wskaźnika, ponieważ później wskaźniki na przód listy jest nullowany, a będzie jeszcze potrzebny
    int tmp_value = dll->head->data;    // Przechowanie wartości, ponieważ pamięć na element zostanie zwolniona, a trzeba ją zwrócić
    if (dll->head == dll->tail) {   // Jeśli lista zawiera jeden element, to głowa jest też ogonem, więc oba wskaźniki należy ustawić na null
        dll->tail = NULL;
        dll->head = NULL;
    } else {
        dll->head->next->prev = NULL; // po usunięciu pierwszego elementu, drugi nie będzie miał poprzednika, więć ustawiany jest null
        dll->head = dll->head->next; // drugi element staje się głową listy
    }
    free(tmp);  // zwolnienie pamięci
    if (err_code != NULL) {
        *err_code = 0;  // brak błędu
    }
    return tmp_value;   // zwrócenie wartości
}

int dll_pop_back(struct doubly_linked_list_t *dll, int *err_code) { // analogicznie do powyższego
    if (dll == NULL || dll->tail == NULL) {
        if (err_code != NULL) *err_code = 1;
        return 0;
    }
    struct node_t *tmp = dll->tail;
    int tmp_value = dll->tail->data;
    if (dll->head == dll->tail) {
        dll->head = NULL;
        dll->tail = NULL;
    } else {
        dll->tail->prev->next = NULL;
        dll->tail = dll->tail->prev;
    }
    free(tmp);
    if (err_code != NULL) {
        *err_code = 0;
    }
    return tmp_value;
}

int dll_back(const struct doubly_linked_list_t *dll, int *err_code) {   // bez usuwania, więc tak jak w powyższych funkcjach, tylko okrojone
    if (dll == NULL || dll->tail == NULL) {
        if (err_code != NULL) *err_code = 1;
        return 0;
    }
    if (err_code != NULL) {
        *err_code = 0;
    }
    return dll->tail->data;
}

int dll_front(const struct doubly_linked_list_t *dll, int *err_code) { // bez usuwania, więc tak jak w powyższych funkcjach, tylko okrojone
    if (dll == NULL || dll->head == NULL) {
        if (err_code != NULL) *err_code = 1;
        return 0;
    }
    if (err_code != NULL) {
        *err_code = 0;
    }
    return dll->head->data;
}

struct node_t *dll_begin(struct doubly_linked_list_t *dll) {  // bez usuwania, więc tak jak w powyższych funkcjach, tylko okrojone
    if (dll == NULL) {
        return NULL;
    }
    return dll->head;
}

struct node_t *dll_end(struct doubly_linked_list_t *dll) {  // bez usuwania, więc tak jak w powyższych funkcjach, tylko okrojone
    if (dll == NULL) {
        return NULL;
    }
    return dll->tail;
}

int dll_size(const struct doubly_linked_list_t *dll) {
    if (dll == NULL) {
        return -1;  // jeśli lista jest nullem to zwracana jest wartość -1
    }
    int size = 0;
    struct node_t *nxt = dll->head; // wskaźnik po którym będziemy iterować
    while (nxt != NULL) { // dopóki nie trafimy na null to przechodzimy po kolejnych elementach listy i dodajemy
        size++;
        nxt = nxt->next;
    }
    return size;
}

int dll_is_empty(const struct doubly_linked_list_t *dll) {
    int size = dll_size(dll);
    if (size > 0) return 0;
    if (size == 0) return 1;
    return -1;
}

int dll_at(const struct doubly_linked_list_t *dll, unsigned int index, int *err_code) {
    if (dll == NULL) {
        if (err_code != NULL) *err_code = 1;
        return 0;
    }
    struct node_t *nxt = dll->head;
    for (unsigned int i = 0; i < index; i++) {  // Iterowanie po kolejnych elementach aż dotrzemy do żądanego indeksu
        if (nxt == NULL) {  // jeśli jednak trafimy po drodze na null to zwracamy błąd
            if (err_code != NULL) *err_code = 1;
            return 0;
        }
        nxt = nxt->next;
    }
    if (nxt == NULL) {  // po dotarciu do elementu sprawdzamy jeszcze czy on sam nie jest nullem
        if (err_code != NULL) *err_code = 1;
        return 0;
    }
    if (err_code != NULL) {
        *err_code = 0;
    }
    return nxt->data;
}

int dll_insert(struct doubly_linked_list_t *dll, unsigned int index, int value) {   // Analogicznie jak przy dodawaniu na początku i końcu listy
    if (dll == NULL) {
        return 1;
    }
    struct node_t *nxt = dll->head;
    for (unsigned int i = 0; i < index; i++) {  // Docieramy do odpowiedniego miejsca w liście
        if (nxt == NULL) {
            return 1;
        }
        nxt = nxt->next;
    }
    if (nxt != NULL) {  // Jeśli nie jest nullem to podmieniamy element w danym indeksie
        if (nxt->prev != NULL) {
            struct node_t *node = malloc(sizeof *node);
            if (node == NULL) {
                return 2;
            }
            // ustawienie wartości i wskaźników na nowe
            node->data = value;
            node->prev = nxt->prev;
            node->next = nxt;
            nxt->prev->next = node;
            nxt->prev = node;
        } else { // jeśli ten element nie ma poprzednika to wystarczy dodać nowy element na początek
            if (dll_push_front(dll, value) == 2) {
                return 2;
            }
        }
    } else {    // Jeśli dany element jest nullem, to znaczy, że jest ostatni, więc wystarczy dodać na koniec
        if (dll_push_back(dll, value) == 2) {
            return 2;
        }
    }
    return 0;
}

int dll_remove(struct doubly_linked_list_t *dll, unsigned int index, int *err_code) {   // jak wyżej tylko usuwanie
    if (dll == NULL) {
        if (err_code != NULL) *err_code = 1;
        return 0;
    }
    struct node_t *nxt = dll->head;
    for (unsigned int i = 0; i < index; i++) {
        if (nxt == NULL) {
            if (err_code != NULL) *err_code = 1;
            return 0;
        }
        nxt = nxt->next;
    }
    if (nxt == NULL) {
        if (err_code != NULL) *err_code = 1;
        return 0;
    }

    if (nxt->prev != NULL) {
        nxt->prev->next = nxt->next;
    } else {
        dll->head = nxt->next;
    }
    if (nxt->next != NULL) {
        nxt->next->prev = nxt->prev;
    } else {
        dll->tail = nxt->prev;
    }
    int tmp = nxt->data;
    free(nxt);
    if (err_code != NULL) {
        *err_code = 0;
    }
    return tmp;
}

void dll_clear(struct doubly_linked_list_t *dll) {
    if (dll == NULL) {
        return;
    }
    struct node_t *nxt = dll->head;
    struct node_t *tmp;
    while (nxt != NULL) {   // po kolei przechodzimy po indeksach i zwalniamy pamięć
        tmp = nxt;
        nxt = nxt->next;
        free(tmp);
    }
    dll->head = NULL;   // nie ma teraz początku i końca listy, a sama lista nie jest dealokowana
    dll->tail = NULL;
}

void dll_display(const struct doubly_linked_list_t *dll) {  // iterowanie i wyświetlanie kolejnych elementóœ
    if (dll == NULL) {
        return;
    }
    struct node_t *nxt = dll->head;
    while (nxt != NULL) {
        printf("%d ", nxt->data);
        nxt = nxt->next;
    }
}

void dll_display_reverse(const struct doubly_linked_list_t *dll) {  // to samo, tylko od końca
    if (dll == NULL) {
        return;
    }
    struct node_t *nxt = dll->tail;
    while (nxt != NULL) {
        printf("%d ", nxt->data);
        nxt = nxt->prev;
    }
}


