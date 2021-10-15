#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

// Cała lista sprowadza się głównie do alokacji pamięci, oraz odpowiedniego ustawiania wskaźników
// w miarę modyfikacji listy

struct doubly_linked_list_t {   // cała lista
    struct node_t *head;    // wskaźnik na początkowy element listy
    struct node_t *tail;    // wskaźnik na ostatni element list
};

struct node_t {     // pojedynczy element listy
    int data;   // wartość
    struct node_t *next;    // wskaźnik na kolejny element względem danego węzła
    struct node_t *prev;    // wskaźnik na poprzedni element
};

struct doubly_linked_list_t *dll_create();  // alokacja pamięci

int dll_push_back(struct doubly_linked_list_t *dll, int value); // Dodanie elementu na końcu listy

int dll_push_front(struct doubly_linked_list_t *dll, int value); // Dodanie elementu na początku listy

int dll_pop_front(struct doubly_linked_list_t *dll, int *err_code); // Pobranie elementu z początku listy (wraz z usunięciem)

int dll_pop_back(struct doubly_linked_list_t *dll, int *err_code); // Pobranie elementu z końca listy (wraz z usunięciem)

int dll_back(const struct doubly_linked_list_t *dll, int *err_code);    // Zwrócenie ostatniego elementu

int dll_front(const struct doubly_linked_list_t *dll, int *err_code); // Zwrócenie pierwszego elementu

int dll_size(const struct doubly_linked_list_t *dll);   // Rozmiar listy

int dll_is_empty(const struct doubly_linked_list_t *dll);   // Sprawdzenie czy jest pusta

int dll_at(const struct doubly_linked_list_t *dll, unsigned int index, int *err_code); // Zwrócenie elementu o wskazanym indeksie

int dll_insert(struct doubly_linked_list_t *dll, unsigned int index, int value); // Dodanie elementu na dany indeks

int dll_remove(struct doubly_linked_list_t *dll, unsigned int index, int *err_code);    // Usunięcie z danego indeksu

void dll_clear(struct doubly_linked_list_t *dll);   // Wyczyszczenie listy

void dll_display(const struct doubly_linked_list_t *dll);   // Wyświetlenie wszystkich elementów

void dll_display_reverse(const struct doubly_linked_list_t *dll);   // Jak wyżej, ale od końca

#endif //DOUBLY_LINKED_LIST_H
