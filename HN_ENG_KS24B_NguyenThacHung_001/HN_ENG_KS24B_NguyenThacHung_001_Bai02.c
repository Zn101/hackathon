#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Undo {
    char x;
    struct Undo* next;
} Undo;

typedef struct Redo {
    char x;
    struct Redo* next;
} Redo;

Undo* createUndo (char x) {
    Undo* u = (Undo*)malloc(sizeof(Undo));
    u->x = x;
    u->next = NULL;
    return u;
}

Redo* createRedo (char x) {
    Redo* r = (Redo*)malloc(sizeof(Redo));
    r->x = x;
    r->next = NULL;
    return r;
}

int main() {
    int choice = 0;
    char *sample = "ABCD";
    do {
        printf("---TASK MANAGER---");
        printf("\n1. Insert x");
        printf("\n2. Undo");
        printf("\n3. Redo");
        printf("\n4. Hien thi");
        printf("\n5. Thoat chuong trinh");
        printf("\nNhap vao lua chon: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                char x[1];
                printf("Nhap vao x: ");
                scanf("%s", x);
                size_t len = strlen(sample);
                char *str2 = malloc(len + 1 + 1);
                strcpy(str2, sample);
                str2[len] = x;
                str2[len + 1] = '\0';
                printf("%s\n", str2);
                free(str2);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                printf("Thoat khoi chuong trinh thanh cong");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 8);
    return 0;
}