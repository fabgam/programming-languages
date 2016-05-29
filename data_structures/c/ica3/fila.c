#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include <string.h>

//Função para criar uma fila
Queue *create_queue()
{
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->first = q->last = NULL;
    return q;
}

//Função para inicializar o vetor de filas
Queue *initialize_vqueue(Queue *q[], int n)
{
    int i;

    for(i = 0; i < n; i++)
        q[i] = create_queue();

    return q;
}

//Função para liberar o vetor de filas
void *dequeue(Queue *q[], int n_lanes)
{
    int i;

    for(i = 0; i < n_lanes; i++)
        free(q[i]);
}

//Função para inserir um elemento na fila
Queue *push(Queue *q, char id[], int entry_sequence)
{
    Node *node = (Node*)malloc(sizeof(Node));

    strcpy(node->id, id);
    node->next = NULL;
    node->sequence_entry = entry_sequence + 1;

    if(is_Empty(q))
        q->first = q->last = node;
    else
    {
        q->last->next = node;
        q->last = node;
    }
    return q;
}

//Função para remover um elemento da fila
Queue *pop(Queue *q)
{
    if(is_Empty(q))
        return NULL;
    else if(q->first == q->last)
    {
        free(q->first);
        q->first = q->last = NULL;
    }
    else
    {
        Node *aux = q->first->next;
        free(q->first);
        q->first = aux;
    }
    return q;
}

//Função para verificar se a fila está vazia
int is_Empty(Queue *q)
{
    return ((q->first == NULL) ? 1 : 0);
}

//Função para retornar o primeiro elemento
Node *first_node(Queue *q)
{
    return ((is_Empty(q)) ? NULL : q->first);
}

//Função para retornar o último elemento
Node *last_node(Queue *q)
{
    return ((is_Empty(q)) ? NULL : q->last);
}

//Função para contar a quantidade de elementos de uma fila
int count_elements(Queue *q)
{
    int count = 0;

    Node *aux = q->first;

    while(aux != NULL)
    {
        count++;
        aux = aux->next;
    }
    return count;
}

//Função para gerar uma ID aleatória
char *gen_id()
{
    int n_random, aux, i;
    char *id = (char*)malloc(6 * sizeof(char));
    char *num = (char*)malloc(6 * sizeof(char));

    for(i = 0; i < 4; i++)
    {
        n_random = rand() % 10;
        num[i] = n_random + '0';
    }

    for(i = 0; i < 2; i++)
    {
        aux = (65 + rand() % (91-65));
        id[i] = (char)aux;
    }

    strcat(id, num);
    free(num);

    return id;
}

//Função para retornar um número aleatório entre o intervalo de min_n - max_n
int random_n(int min_n, int max_n)
{
    int n_random;

    return n_random = (min_n + rand() % (max_n - min_n));
}

//Função para inserir os elementos no vetor de fila
Queue *insert_elements(Queue *q[], int n_lanes, int n)
{
    int i = search_entry(q, n_lanes), count_n = 0;
    char id[6];

    while(count_n != n)
    {
        if(i == n_lanes)
            i = 0;

        strcpy(id, gen_id());

        printf("\nInserindo aeronave %s na fila da pista %d", id, i);
        push(q[i], id, highest_entry(q, n_lanes));

        count_n++;
        i++;
    }
    return q;
}

//Função para procurar o maior número de entrada inserido
int highest_entry(Queue *q[], int n_lanes)
{
    int i, x = 0;

    for(i = 0; i < n_lanes; i++)
    {
        if(!is_Empty(q[i]))
        {
            Node *aux = q[i]->first;

            while(aux != NULL)
            {
                if(aux->sequence_entry > x)
                    x = aux->sequence_entry;

                aux = aux->next;
            }
        }
    }
    return x;
}

//Função para procurar a fila com menos elementos inseridos
int search_entry(Queue *q[], int n_lanes)
{
    int i, p, x = 0, y = 999999;

    for(i = 0; i < n_lanes; i++)
    {
        if(is_Empty(q[i]))
            return i;

        if(q[i]->last->sequence_entry < y)
        {
            y = q[i]->last->sequence_entry;
            p = i;
        }

    }
    return p;
}
//Função para imprimir um vetor de filas.
void print_queue(Queue *q[], int n, int display)
{
    int i;
    for(i = 0; i < n; i++)
    {
        Node *aux = q[i]->first;

        if(display == 1)
            printf("Pista %d: ", i);
        else
            printf("Finger %d: ", i);

        while(aux != NULL)
        {
            printf("#%d %s -> ", aux->sequence_entry, aux->id);
            aux = aux->next;
        }
        printf("\n");
    }
}

//Função para liberar os vetores de filas utilizados
void end_execution(Queue *q_la[], Queue *q_lo[], Queue *q_fingers[], int n_lanes, int n_fingers)
{
    dequeue(q_la, n_lanes);
    dequeue(q_lo, n_lanes);
    dequeue(q_fingers, n_fingers);
}
