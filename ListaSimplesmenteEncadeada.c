#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>



typedef struct node
{
    int id;
    struct node* next;

} Node;

typedef struct list
{
    int size;
    Node* head;
    Node* tail;

} List;

/* Cabeçalhos */
List* createList();
void push (List* list, int id);
void pushEnd (List* list, int id);

void printList(List* list);
void pop(List* list);
void popEnd(List* list);

int isEmpty(List* list);
Node* atPos(List* List, int index);
Node* atPosUl(List* List);
int indexOf(List* list, Node* node);
void erase(List* list, int index);
void insert(List* list, int data, int index);
int size(List * list);
void ordena(List* list);
List insereEordena(List l, int inteiro);

/* Funções */
List* createList()
{
    List* list = (List*) malloc(sizeof(List));
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;

    return list;
}


void push (List* list, int id)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->id = id;
    node->next = list->head;
    list->head = node;
    list->size++;
}
void pushEnd (List* list, int id)
{
    Node* node = (Node*)malloc(sizeof(Node));
    Node* nodecurrent = atPosUl(list);

    node->id = id;
    if(list->size>0)
    {
        nodecurrent->next = node;

    }
    else
    {
        list->head = node; // resolve o problema do ponteiro de node sem acesso à um next.
    }


    node->next = NULL;

    list->tail = node;

    list->size++;
}

void printList(List* list)
{

    if(isEmpty(list))
    {
        printf("Lista vazia \n");
        return;
    }
    Node* pointer = list->head;
    printf("\n[");
    while(pointer != NULL)
    {
        printf("%d ", pointer->id);
        pointer = pointer->next;

    }
    printf("]");

}

void pop(List* list)
{
    if(list->size>0)
    {
        Node* pointer = list->head;
        list->head = pointer->next;
        free(pointer);
        list->size--;
    }
    else
    {
        printf("\nA lista está vazia não há o que retirar! \n");
    }
}

void popEnd(List* list)
{
    if(list->size>0)
    {
        Node* pointer = atPosUl(list);
        list->size--;
        Node* node = atPosUl(list);
        list->tail = node;
        node->next = NULL;
        free(pointer);
    }
    else
    {
        printf("\n A lista está vazia não há o que retirar! \n");

    }
}


int isEmpty(List* list)
{
    if(list->size<1)
    {

        return 1;
    }
    else
    {


        return 0;
    }

}


Node* atPos(List* list, int index)
{
    if(index >= 0 && index < list->size)
    {
        Node* node = list->head;

        int i;
        for(i= 0; i <index; i++)
        {
            node = node->next;

        }
        return node;

    }
    else
    {

        return 0;
    }



}

Node* atPosUl(List* list)
{
    int tamanho = size(list);


    if(tamanho >= 0 && tamanho <= list->size)
    {
        Node* node = list->head;
        int i;

        if(list->size==0)
        {




            return node;
        }
        else
        {
            for(i = 0; i <(list->size)-1; i++)
            {


                node = node->next;

            }
            return node;

        }


    }

    return 0;


}
int indexOf(List* list, Node* node)
{
    if(node !=NULL)
    {
        Node* pointer = list->head;
        int index = 0;

        while(pointer!= node && pointer != NULL )
        {
            pointer = pointer->next;
            index++;
        }
        if(pointer != NULL)
        {
            return index;


        }
    }
    printf("\nNó não pertencente a lista \n");
    return -1;

}

void erase(List *list, int index)
{
    if(index == 0)
    {
        pop(list);

    }
    else
    {
        Node* current = atPos(list, index);
        if(current != NULL)
        {
            Node* previous = atPos(list, index-1);
            previous->next = current->next;
            free(current);
            list->size--;



        }
    }
}



void insert(List* list, int id, int index)
{
    if(index == 0)
    {
        push(list, id);
    }
    else
    {
        Node* current = atPos(list, index);

        if(current!= NULL)
        {
            Node* previous = atPos(list, index-1);
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->id = id;
            previous->next = newNode;
            newNode->next = current;
            list->size++;

        }

    }
}

int size(List * list)
{
    return(list->size);
}

void ordena(List* list)
{
    if(list->size<2)
    {
        printf("\n A lista so possui um elemento\n");
    }
    else
    {

        int i,j;
        for(i=0; i<list->size-1; i++)
        {
            Node* pointerBack = NULL;
            Node* pointerHalf = list->head;
            Node* pointerFront = list->head->next;
            for(j=0; j<list->size-1; j++)
            {
                if(j == 0)
                {

                    if(pointerHalf->id > pointerHalf->next->id)
                    {
                        pointerFront = pointerFront->next;
                        pointerHalf->next->next = pointerHalf;
                        list->head = list->head->next;
                        pointerHalf->next = pointerFront;
                        pointerBack = list->head;
                    }
                    else
                    {
                        pointerBack = list->head;
                        pointerHalf = pointerHalf->next;
                        pointerFront = pointerFront->next;

                    }
                }
                else
                {
                    if(pointerHalf->id > pointerHalf->next->id)
                    {
                       // printf("\n  Passou if");
                        //printList(list);
                        pointerFront = pointerFront->next;
                        //printf("\n   Passou front = front->next");
                       // printList(list);
                        pointerHalf->next->next = pointerHalf;
                        //printf("\n Passou pointerHalf->next->next = pointerHalf;");
                       // printList(list);
                        pointerBack->next = pointerBack->next->next;
                        //printf("\n   Passou pointerBack->next = pointerBack->next->next;");
                        //printList(list);
                        pointerHalf->next = pointerFront;
                        //printf("\n   Passou pointerHalf->next = pointerFront;");

                        //printList(list);
                        pointerBack = pointerBack->next;
                        //printf("\n   Passou pointerBack = pointerBack->next;");
                        //printList(list);

                        //printList(list);

                    }else{
                        //printList(list);
                        pointerBack = pointerBack->next;
                        //printList(list);
                        pointerHalf = pointerHalf->next;
                        //printList(list);
                        pointerFront = pointerFront->next;
                        //printList(list);
                    }

                }

            }
        }


    }


}


List insereEordena(List l, int inteiro)
{

}
int main()
{
    int opcao, indice, tamanho, vazia;
    List* l = createList();
    int id;

    Node* ax;

    setlocale(LC_ALL, "Portuguese_Brazil");
    do
    {
        printf("Escolha as opções abaixo digitando os algarismos associados: \n");
        printf("1-Inserir no início \n");
        printf("2-Inserir no fim \n");
        printf("3-Printar \n");
        printf("4-Retirar do início \n");
        printf("5-retirar do fim \n");
        printf("6-Verificar se a lista está vazia \n");
        printf("7- Elemento de uma determinada posição \n");
        printf("8-Tamanho da lista \n");
        printf("9-Ordenar lista \n");
        printf("10-Sair \n");
        ;
        scanf("%d", &opcao);
        switch(opcao)
        {
        case 1:
            printf("\nDigite o número que deseja inserir: \n");
            scanf("%d", &id);
            push(l, id);
            printList(l);
            break;
        case 2:
            printf("\nDigite o número que deseja inserir: \n");
            scanf("%d", &id);
            pushEnd(l, id);
            printList(l);

            break;

        case 3:
            printList(l);

            break;

        case 4:
            pop(l);
            printList(l);
            break;

        case 5:
            popEnd(l);
            printList(l);

            break;

        case 6:
            vazia = isEmpty(l);
            if(vazia==0)
            {
                printf("\nLista não vazia \n");
            }
            else
            {
                printf("\nLista vazia \n");

            }
            break;

        case 7:
            printf("\nDigite o numero da posição que deseja checar\n");
            scanf("%d", &indice);
            ax = atPos(l,indice);
            if(ax!=0)
            {
                printf("\nA posição %d contém o valor %d \n", indice, ax->id);
                break;

            }
            else
            {
                printf("\nÍndice inválido \n");
            }


        case 8:
            tamanho = size(l);
            printf("\nO tamanho da lista é %d \n", tamanho);
            break;

        case 9:
            ordena(l);
            printList(l);
            break;
        case 10:
            printf("\n Tchau! \n");
            break;

        default:
            printf("\n Opção inválida \n");
            break;






        }
    }
    while(opcao!= 10);

    free(l);
}
