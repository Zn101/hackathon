#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Task {
    int Id;
    char Title[50];
    int Priority;
    char deadline[50];
    bool finish;
} Task;

typedef struct TaskQueue {
    Task tasks;
    struct TaskQueue* next;
} TaskQueue;

typedef struct TaskHistory {
    Task tasks;
    struct TaskHistory* next;
    struct TaskHistory* prev;
} TaskHistory;

Task* createTask(int id, char* title, int priority, char* deadline) {
    Task* task = (Task*)malloc(sizeof(Task));
    task->Id = id;
    strcpy(task->Title, title);
    task->Priority = priority;
    strcpy(task->deadline, deadline);
    task->finish = false;
    return task;
}

TaskQueue* createTaskQueue(Task* task) {
    TaskQueue* queue = (TaskQueue*)malloc(sizeof(TaskQueue));
    queue->tasks = *task;
    queue->next = NULL;
    return queue;
}

TaskHistory* createTaskHistory(Task* task) {
    TaskHistory* queue = (TaskHistory*)malloc(sizeof(TaskHistory));
    queue->tasks = *task;
    queue->next = NULL;
    queue->prev = NULL;
    return queue;
}

TaskQueue* enqueueTask(TaskQueue* head, Task* task) {
    TaskQueue* newNode = createTaskQueue(task);
    free(task);
    if (head == NULL) {
        return newNode;
    } else {
        TaskQueue* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        return head;
    }
}

TaskHistory enqueueTaskHistory(TaskHistory* head, Task* task) {
    TaskHistory* newNode = createTaskHistory(task);
    free(task);
    if (head == NULL) {
        return *newNode;
    } else {
        TaskHistory* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
            temp->prev = newNode;
        }
        temp->next = newNode;
        return *head;
    }
}

void printQueue(TaskQueue* head) {
    TaskQueue* temp = head;
    if (temp == NULL) {
        printf("Danh sach nhiem vu trong\n");
    }
    while (temp != NULL) {
        printf("Task id:%d, Task name: %s, Task priority: %d, Task deadline: %s,Task status: %s\n", temp->tasks.Id, temp->tasks.Title, temp->tasks.Priority, temp->tasks.deadline, temp->tasks.finish ? "Finished" : "Not Finished");
        temp = temp->next;
    }
}

TaskQueue* deleteTaskQueueId(TaskQueue* head, int id) {
    if (head == NULL) {
        printf("Danh sach nhiem vu trong\n");
        return NULL;
    }
    TaskQueue* temp = head;
    TaskQueue* prev = NULL;
    if (temp != NULL && temp->tasks.Id == id) {
        head = temp->next;
        free(temp);
        return head;
    }
    while (temp != NULL && temp->tasks.Id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        return head;
    }
    prev->next = temp->next;
    free(temp);
    return head;
}

void updateTask(TaskQueue* head, int id) {
    if (head == NULL) {
        printf("Danh sach nhiem vu trong\n");
        return;
    }
    TaskQueue* temp = head;
    while (temp != NULL && temp->tasks.Id != id) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Khong tim thay nhiem vu\n");
        return;
    }
    int newPriority;
    char newTitle[50];
    char newDeadline[50];
    printf("Nhap vao ten nhiem vu cap nhat: ");
    fgets(newTitle, 50, stdin);
    fflush(stdin);
    printf("Nhap vao muc do uu tien nhiem vu cap nhat: ");
    scanf("%d", &newPriority);
    getchar();
    printf("Nhap vao deadline cap nhat: ");
    fgets(newDeadline, 50, stdin);
    fflush(stdin);
    strcpy(temp->tasks.Title, newTitle);
    strcpy(temp->tasks.deadline, newDeadline);
    temp->tasks.Priority = newPriority;
    temp->tasks.finish = true;
}

void markTask(TaskQueue* head, int id) {
    TaskQueue* temp = head;
    while (temp != NULL && temp->tasks.Id != id) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Danh sach nhiem vu trong");
    }
    temp->tasks.finish = true;
    enqueueTaskHistory(head, temp);
    deleteTaskQueueId(head, id);
    free(temp);
    printf("Da danh dau hoan thanh nhiem vu");
};

int taskLength(TaskQueue* head) {
    int count = 1;
    while (head != NULL) {
        head = head->next;
    }
    return count;
}

void sortTask(TaskQueue* head) {
    int n = taskLength(head);
    if (head == NULL) {
        printf("Danh sach nhiem vu trong\n");
    }
    for (int i = 0; i < n - 1; i++) {
        if (head->tasks.Priority > head->next->tasks.Priority) {
            TaskQueue* temp = head->next;
            head->next = head->next->next;
            temp->next = head;
        }
    }
}

void searchTask(TaskQueue* head, char* title) {
    bool found = false;
    TaskQueue* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->tasks.Title, title) == 0) {
            printf("Nhiem vu co ton tai trong danh sahc");
            found = true;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("Khong tim thay nhiem vu trong danh sach\n");
    }
}

int main() {
    int choice = 0;
    TaskQueue* head = NULL;
    do {
        printf("---TASK MANAGER---");
        printf("\n1. Them nhiem vu");
        printf("\n2. Hien thi danh sach nhiem vu");
        printf("\n3. Xoa nhiem vu");
        printf("\n4. Cap nhat thong tin nhiem vu");
        printf("\n5. Danh dau nhiem vu da hoan thanh");
        printf("\n6. Sap xep nhiem vu");
        printf("\n7. Tim kiem nhiem vu");
        printf("\n8. Thoat chuong trinh");
        printf("\nNhap vao lua chon: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                int id, priority;
                char title[50];
                char deadline[50];
                printf("Nhap vao id nhiem vu:");
                scanf("%d", &id);
                getchar();
                printf("Nhap vao ten nhiem vu: ");
                fgets(title, 50, stdin);
                fflush(stdin);
                printf("Nhap vao muc do uu tien nhiem vu: ");
                scanf("%d", &priority);
                getchar();
                printf("Nhap vao deadline cua nhiem vu:");
                fgets(deadline, 50, stdin);
                fflush(stdin);
                Task* task = createTask(id, title, priority, deadline);
                head = enqueueTask(head, task);
                printf("Them vao nhiem vu thanh cong\n");
                break;
            case 2:
                printQueue(head);
                break;
            case 3:
                int delId;
                printf("Nhap vao id Nhiem vu can xoa: ");
                scanf("%d", &delId);
                deleteTaskQueueId(head, delId);
                printf("Da xoa nhiem vu thanh cong\n");
                break;
            case 4:
                int updateId;
                printf("Nhap vao id nhiem vu can cap nhat: ");
                scanf("%d", &updateId);
                getchar();
                updateTask(head, updateId);
                printf("Da cap nhat thanh cong");
                break;
            case 5:
                int markId;
                scanf("%d", &markId);
                markTask(head, markId);
                break;
            case 6:
                sortTask(head);
                printf("Da sap xep thanh cong");
                printQueue(head);
                break;
            case 7:
                char searchTitle[50];
                fgets(searchTitle, 50, stdin);
                fflush(stdin);
                searchTask(head, searchTitle);
                break;
            case 8:
                printf("Thoat khoi chuong trinh thanh cong");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 8);
    return 0;
}