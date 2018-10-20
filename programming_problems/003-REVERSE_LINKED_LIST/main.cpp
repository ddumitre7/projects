
#include <stdio.h>
#include <stdlib.h>
#include<iostream>

using namespace std;


/* Link list Node */
struct Node {
    int data;
    struct Node* next;
};


Node *reverse(Node *);


// Helper functions
void printList(Node *);
void append(Node**, Node**, int);

/* Driver program to test above function*/
int main()
{
    int T,n,l;
    cin>>T;
    while(T--)
    {
        struct Node *head = NULL,  *tail = NULL;
        cin>>n;
        for (int i=1; i<=n; i++)
        {
            cin>>l;
            append(&head, &tail, l);
        }
       head = reverse(head);
       printList(head);
       cout << endl;
    }
    return 0;
}

Node* reverse(Node *head)
{
  
  if (!head) return nullptr;
  
  if (!head->next) return head;
 
  Node *cursor{head}, *cursor_next{head->next};
  
  cursor->next = nullptr;
  
  while (cursor_next->next) {
      
          Node *new_cursor_next = cursor_next->next;
          
          cursor_next->next = cursor;
          cursor = cursor_next;
          cursor_next = new_cursor_next;
      
  } // End while
  
  cursor_next->next = cursor;
  
  return cursor_next;
  
}

void append(Node** head_ref, Node **tail_ref,
            int new_data)
{
    Node* new_node = new Node;
    new_node->data  = new_data;
    new_node->next = NULL;
    if (*head_ref == NULL)
        *head_ref = new_node;
    else
        (*tail_ref)->next = new_node;
    *tail_ref = new_node;
}



void printList(struct Node *head)
{
    struct Node *temp = head;
    while (temp != NULL)
    {
       printf("%d ", temp->data);
       temp  = temp->next;
    }
}

  
  
