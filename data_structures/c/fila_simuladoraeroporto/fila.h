/*  Ambiente de desenvolvimento:
    OS: Ubuntu 16.04 LTS
    IDE: CodeBlocks 16.01
    GCC: 5.3.1*/

#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

typedef struct node
{
    char id[8];
    int sequence_entry;
    int c_shift;
    struct node *next;
} Node;

typedef struct q
{
    Node *first;
    Node *last;
} Queue;

Queue *create_queue();
Queue *initialize_vqueue(Queue*[], int, int);
void *dequeue(Queue*[], int);
Queue *push(Queue*, char[], int);
Queue *pop(Queue*);
int is_Empty(Queue*);
int count_elements(Queue*);
int count_qelements(Queue*[], int);
int count_free_finger(Queue*[], int);
int free_finger(Queue*[], int);
char *gen_id();
int random_n(int, int);
int highest_shift(Queue*[], int);
int highest_entry(Queue*[], int);
int smaller_entry(Queue*[], int);
int search_entry(Queue*[], int);
void insert_elements(Queue*[], int, int);
void land(Queue*[], Queue*[], int, int, int);
void land_wq(Queue*[], Queue*, int, int);
void lift_off(Queue*[], int, int);
void f_qlo(Queue*[], Queue*[], int, int, int);
void w_fingers(Queue*[], Queue*, int, int);
void print_queue(Queue*[], int, int);
void update_shift(Queue*[], Queue *, int);
void end_execution(Queue*[], Queue*[], Queue*[], int, int);

#endif // FILA_H_INCLUDED