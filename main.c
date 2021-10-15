#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

int main() {
    struct doubly_linked_list_t *dll = dll_create();
    if (dll == NULL) {
        printf("Niepowodzenie alokacji pamieci");
        return 8;
    }

    int op = -1;
    printf("0 - zakoncz\n1 - dodaj na koniec\n2 - pobierz z konca\n3 - dodaj na poczatek\n4 - pobierz z poczatku\n"
           "5 - dodaj liczbe na wybrany indeks\n6 - usun liczbe z wybranego indeksu\n7 - wyswietl ostatni element\n"
           "8 - wyswietl pierwszy element\n9 - czy lista jest pusta\n10 - rozmiar listy\n11 - wyczyszczenie listy\n"
           "12 - wyswietl liczbe z wybranego indeksu\n13 - wyswietl liste\n14 - wyswietl liste od tylu\n");
    while (op != 0) {
        printf("Co chcesz zrobic? ");
        if (scanf("%d", &op) != 1) {
            printf("Niewlasciwe dane");
            dll_clear(dll); // Zwolnienie pamięci z elementów
            free(dll);  // Zwolnienie pamięci z listy
            return 1;
        }
        switch (op) {
            case 0: {
                break;  // każdy case kończy się breakiem, żeby przerwać dalsze sprawdzanie
            }
            case 1: {
                int a;
                printf("Podaj liczbe ");
                if (scanf("%d", &a) != 1) { // Sprawdzenie czy uzytkownik podal prawidlowe znaki na wejściu
                    printf("Niewlasciwe dane");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                if (dll_push_back(dll, a) == 2) {
                    printf("Niepowodzenie alokacji pamieci");   // jeśli malloc się nie powiódł
                    dll_clear(dll);
                    free(dll);
                    return 8;
                }
                break;
            }
            case 2: {
                int err;
                int a = dll_pop_back(dll, &err);
                if (err == 0) printf("%d\n", a);
                else printf("Lista jest pusta\n");
                break;
            }
            case 3: {
                int a;
                printf("Podaj liczbe ");
                if (scanf("%d", &a) != 1) {
                    printf("Niewlasciwe dane");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                if (dll_push_front(dll, a) == 2) {
                    printf("Niepowodzenie alokacji pamieci");
                    dll_clear(dll);
                    free(dll);
                    return 8;
                }
                break;
            }
            case 4: {
                int err;
                int a = dll_pop_front(dll, &err);
                if (err == 0) printf("%d\n", a);
                else printf("Lista jest pusta\n");
                break;
            }
            case 5: {
                int a, index, err;
                printf("Podaj liczbe ");
                if (scanf("%d", &a) != 1) {
                    printf("Niewlasciwe dane");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                printf("Podaj index ");
                if (scanf("%d", &index) != 1) {
                    printf("Niewlasciwe dane");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                err = dll_insert(dll, index, a);
                if (err == 2) {
                    printf("Niepowodzenie alokacji pamieci");
                    dll_clear(dll);
                    free(dll);
                    return 8;
                } else if (err == 1) {
                    printf("Indeks poza zakresem\n");
                }
                break;
            }
            case 6: {
                int a, index, err;
                if(dll_is_empty(dll)) {
                    printf("Lista jest pusta\n");
                    break;
                }
                printf("Podaj index ");
                if (scanf("%d", &index) != 1) {
                    printf("Niewlasciwe dane");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                a = dll_remove(dll, index, &err);
                if (err == 1) {
                    printf("Indeks poza zakresem\n");
                } else {
                    printf("%d\n", a);
                }
                break;
            }
            case 7: {
                if(dll_is_empty(dll)) {
                    printf("Lista jest pusta\n");
                }
                else {
                    printf("%d\n", dll_back(dll, NULL));
                }
                break;
            }
            case 8: {
                if(dll_is_empty(dll)) {
                    printf("Lista jest pusta\n");
                } else {
                    printf("%d\n", dll_front(dll, NULL));
                }
                break;
            }
            case 9: {
                printf("%d\n", dll_is_empty(dll));
                break;
            }
            case 10: {
                printf("%d\n", dll_size(dll));
                break;
            }
            case 11: {
                dll_clear(dll);
                break;
            }
            case 12: {
                if(dll_is_empty(dll)) {
                    printf("Lista jest pusta\n");
                } else {
                    int index;
                    printf("Podaj index ");
                    if (scanf("%d", &index) != 1) {
                        printf("Niewlasciwe dane");
                        dll_clear(dll);
                        free(dll);
                        return 1;
                    }
                    int err, a;
                    a = dll_at(dll, index, &err);
                    if(err != 0) {
                        printf("Indeks poza zakresem\n");
                    } else {
                        printf("%d\n", a);
                    }
                }
                break;
            }
            case 13: {
                if(dll_is_empty(dll)) {
                    printf("Lista jest pusta\n");
                } else {
                    dll_display(dll);
                    printf("\n");
                }
                break;
            }
            case 14: {
                if(dll_is_empty(dll)) {
                    printf("Lista jest pustsa\n");
                } else {
                    dll_display_reverse(dll);
                    printf("\n");
                }
                break;
            }
            default: {  // Nieprawidłowy wybór operacji
                printf("Niewlasciwe dane\n");
            }
        }
    }

    dll_clear(dll);
    free(dll);
    return 0;
}
