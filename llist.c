#include "llist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    char *insert_head = "ih";
    char *insert_tail = "it";
    char *delete_head = "dh";
    char *print = "p";
    char *free = "f";

    // Initialize the head node to NULL 
    struct node *head = NULL;
   
    for (int i = 1; i < argc; i++){
        // Insert at Head
        if (strcmp(argv[i], insert_head) == 0){
            i += 1; // The next argument is the value of the new node
            int value = atoi(argv[i]);
            struct node *new_node = node_alloc(value); // Allocate memory for new node       
            llist_insert_head(&head, new_node);
        }
        // Insert at Tail
        else if (strcmp(argv[i], insert_tail) == 0){
            i += 1; // The next argument is the value of the new node
            int value = atoi(argv[i]);
            struct node *new_node = node_alloc(value); // Allocate memory for new node
            llist_insert_tail(&head, new_node);
        }
        // Delete Head
        else if (strcmp(argv[i], delete_head) == 0){
            if(head == NULL){
                continue;
            }
            llist_delete_head(&head);
        }
        // Print List
        else if (strcmp(argv[i], print) == 0){
            llist_print(head);
        }
        // Free List
        else if (strcmp(argv[i], free) == 0){
            llist_free(&head);
        }
    }
    return 0;
}

void llist_insert_head(struct node **head, struct node *n){
    if(*head == NULL){ // If head is NULL, list is empty, so to add we just set the head equal to the new node.
        *head = n;
        return;
    }
    n->next = *head; // Otherwise set new nodes next to current head, then set the current head to point to the new node
    *head = n;
}

struct node *llist_delete_head(struct node **head){
    if(*head == NULL){ // Do nothing if the list is empty (head is null)
        return *head;
    }
    struct node *next = (*head)->next; //Save the pointer to the next node
    node_free(*head); // Free memory locaion that head points to
    *head = next; // Set head to point to the second node.
    return *head;
}

void llist_insert_tail(struct node **head, struct node *n){
    if (*head == NULL){ // If head is NULL, list is empty, so to add we just set the head equal to the new node.
        *head = n;
        return;
    }
    struct node *curr_node = *head; // Use *curr_node variable so we dont modify head
    while((curr_node)->next != NULL){
        curr_node = curr_node->next;
    }
    curr_node->next = n;
}
void llist_print(struct node *head){
    if(head == NULL){
        printf("[empty]\n");
        return;
    }
    while(head->next != NULL){
        printf("%d --> ",head->value);
        head = head->next;
    }
    printf("%d\n",head->value); // Print tail

}
void llist_free(struct node **head){
    while ( (*head)->next != NULL){ // Just call delete head until next is null (Last node)
        llist_delete_head(head);
    } 
    llist_delete_head(head); // Then call one more time to delete last node   
}

struct node *node_alloc(int value){
    struct node *node = (struct node*) malloc(sizeof(struct node));
    node->value = value;
    node->next = NULL;
    return node;
}
void node_free(struct node *n){
    free(n);
}