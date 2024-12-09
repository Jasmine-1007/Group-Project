#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct task
{
    int index;
    char title[MAX];
    char date[10];
    char status;
} task;

typedef struct node
{
    task *content;
    node *next;
} node;

void addtask(node **head, task *task1)
{
    node *newnode = (node *)malloc(sizeof(node));
    if (newnode == NULL)
    {
        printf("Failed to allocate, exiting.\n");
        exit(1);
    }
    newnode->content = task1;
    newnode->next = NULL;

    if ((*head) == NULL)
    {
        *head = newnode;
        newnode->content->status = 'n';
    }
    else
    {
        node *ptr = *head;
        while (ptr->next)
        {
            ptr = ptr->next;
        }
        ptr->next = newnode;
        newnode->content->status = 'n';
    }
}

void deletetask(node **head, node *target)
{
    node *ptr = *head;
    if (*head == target)
    {
        *head = target->next;
    }
    else
    {
        while (ptr->next != target)
        {
            ptr = ptr->next;
        }
        ptr->next = ptr->next->next;
    }
    printf("The task with index %d is deleted.\n", target->content->index);
    free(target->content);
    free(target);
}


node *searchtask(node *head, int indexnum)
{
    while (head)
    {
        if (head->content->index == indexnum)
        {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

node *searchtask2(node *head, char *input)
{
    node *ptr = head;
    while (ptr)
    {
        if (strcmp(ptr->content->date, input) == 0 || strcmp(ptr->content->title, input) == 0)
        {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void updatetask(node *target)
{
    char choice;
    printf("What do you wish to modify?('d' for date, 'c' for content) \n");
    scanf("%c", &choice);
    if (choice == 'c')
    {
        printf("Enter the new task title: \n");
        getchar();
        fgets(target->content->title, sizeof(char) * MAX, stdin);
        target->content->title[strcspn(target->content->title, "\n")] = '\0';
        printf("Successfully updated the task#%d title to %s", target->content->index, target->content->title);
    }
    else if (choice == 'd')
    {
        printf("Enter the new task date: \n");
        printf("Enter the new task title: \n");
        getchar();
        fgets(target->content->date, sizeof(int) * 10, stdin);
        target->content->title[strcspn(target->content->title, "\n")] = '\0';
        printf("Successfully updated the task#%d title to %s", target->content->index, target->content->date);
    }
}

void displaytask(node *head)
{
    node *ptr = head;
    while (ptr)
    {
        if (ptr->content->status == 'n')
        {
            printf("#%d: %s , %s.\n", ptr->content->index, ptr->content->title, ptr->content->date);
        }
        else
        {
            printf("(complete) #%d: %s , %s.\n", ptr->content->index, ptr->content->title, ptr->content->date);
        }
        ptr = ptr->next;
    }
}

void markdone(node *target)
{
    target->content->status = 'y';
    printf("Task #%d complete.\n", target->content->index);
}

void loadfile() {}

int main()
{
    int choice;
    int f;
    node *list = (node *)malloc(sizeof(node));
    if (list == NULL)
    {
        printf("fail to initiate.\n");
        exit(1);
    }
    printf("1. add a new task.\n"
           "2. delete a task.\n"
           "3. update a task.\n"
           "4. display all tasks.\n"
           "5. display a task.\n"
           "6. mark a task as 'done'\n"
           "7. search for a task.\n"
           "");

    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        task *tasktoadd = (task *)malloc(sizeof(task));
        if (!tasktoadd) {
            printf("fail to initiate.\n");
            exit(1);
        }
        addtask(&list, tasktoadd);
        break;
    case 2:
        printf("Which task do you wish to delete (enter the index)?\n");
        scanf("%d", &f);
        node *target = searchtask(list, f);
        if (target) {
            deletetask(&list, target);
        }
        else printf("Task not found or list is empty!\n");
        break;
    case 3:
        printf("Which task do you wish to update (enter the index)?\n");
        scanf("%d", &f);
        node *target = searchtask(list, f);
        if (target) {
            updatetask(target);
        }
        else printf("Task not found!\n");
        break;
    case 4:
        displaytask(list);
    case 5:
        printf("Which task do you want to display?\n");
        scanf("%d", &f);
        node *target = searchtask(list, f);
        if (target) {
            displaytask(target);
        }
        else printf("Task not found!\n");
        break;
    case 6:
        printf("Which task did you complete?\n");
        scanf("%d", &f);
        node *target = searchtask(list, f);
        if (target) {
            markdone(target);
        }
        else printf("Task not found!\n");
        break;
    case 7:
        char tmp[100];
        printf("Search for a task with title or date: \n");
        scanf("%s", tmp);
        node *target = searchtask2(list, tmp);
        if (target) {
            printf("#%d: %s , %s.\n", target->content->index, target->content->title, target->content->date);
        }
        else printf("Task not found!\n");
        break;
    }

    return 0;
}
