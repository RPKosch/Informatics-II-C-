#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>



static void basicpointers() {
    int p = 77;
    int *adress = &p; // Corrected type to int*
    int **adresstoadress = &adress;
    int *q;           // Pointer variable, uninitialized

    printf("%d , %p, %p, %p, %p, %d \n", p, (void *)adress, (void *)q, (void *)adresstoadress, (void *)*adresstoadress, (void *)**adresstoadress); // Cast pointers to void* for printf
}


static void doublepointers(){
    int p = 99;
    int *pointer;
    int **pointertopointer = &pointer;
    *pointertopointer = &p;
    printf("%d %p %p \n", (void *)**pointertopointer, (void *)**pointertopointer, (void *)&p);
    //printf("%p , %p, %p \n", (void *)pointertopointer, (void *)*pointertopointer, (void *)**pointertopointer);
    pointertopointer = (int **)malloc(sizeof(int *));
    int a = 88;
    *pointertopointer = &a;
    printf("%d , %p, %p, %p, %d", a,(void *)pointertopointer, (void *)&a, (void *)*pointertopointer, (void *)**pointertopointer);
    free(pointertopointer);
}

static void triplepointers() {
    int x = 1111;
    int y = 888;
    int ***pointer1 = malloc(sizeof(int **));
    **pointer1 = &x;
    printf("\n %d %p %p %p \n", (void *)***pointer1, (void *)**pointer1,(void *)*pointer1, (void *)pointer1);
    **pointer1 = &y;
    printf("\n %d %p %p %p \n", (void *)***pointer1, (void *)**pointer1,(void *)*pointer1, (void *)pointer1);
    free(pointer1);
}

static void arraypointer() {
    int a[10];
    a[0] = 77;
    a[1] = 8;
    a[2] = 100;
    int *p = &a[0];
    printf("%d\n", *p);
    int *pa = a;
    (*pa)++;
    printf("%d\n", *pa);
    pa++;
    printf("%d\n", *pa);
    (*(pa+1))++;
    printf("%d\n", *(pa+1));
}

/* given month struct */
struct month {
    int month_number;
    char *month_name;
    struct month *next;
};

void print_months(struct month *head) {
    /* AHA: Understand while loop condition */
    printf("months: ");
    struct month *p = head;
    while (p != NULL) {
        printf("%s (%d), ", p->month_name, p->month_number);
        p = p->next;
    }
    printf("\n");
}

struct month *get_previous_month(struct month *head, struct month *a) {
    /* AHA: Understand trailing pointers */
    if (head == NULL || a == NULL) {
        return NULL;
    } else if (head->next == a) {
        return head;
    }

    struct month *p = head;

    while (p->next != a) {
        p = p->next;
    }
    return p;
}

struct month *swap_month(struct month *head, struct month *a, struct month *b) {

    /* printf("Swap %d with %d\n", a->month_number, b->month_number); */

    struct month *prev_a;
    struct month *prev_b;

    /* Since its incremental slection sort, it is not needed to check for
       head==b. We can always assume a comes before b in the order of the linked
       list. */
    if (a == b) {
        /* Trivial; nothing to do */
        return head;
    } else if (head == a) {
        /* Case: if a is head */
        /* AHA: prev_a does not work in this case, thus return first, or if
         * around
         */
        /* AHA: on head change, new head has to be returned and reassigned */

        if (a->next == b) {
            /* Subcase: if a and b are adjacent */
            /* AHA: this is also a subcase */
            a->next = b->next;
            b->next = a;
        } else {
            /* Subcase: a and b are not adjacent */
            /* These variables are needed in this case */
            /* temporary head next, because head gets reassigned */
            struct month *tmp_a_next = a->next;
            prev_b = get_previous_month(head, b); /* preceding of b */
            a->next = b->next;                    /* same as adjacent */
            b->next = tmp_a_next; /* AHA: cannot say head->next, because
                                     (head=a)->next gets reassigne */
            prev_b->next = a;     /* same as adjacent, but with prev_b */
        }
        head = b; /* for both subcases: reassigne head */
    }

    else if (a->next == b) {
        /* Case: a and b are adjacent */
        /* AHA: This is also a case to consider */

        prev_a = get_previous_month(head, a); /* get preceding of a */
        a->next = b->next;                    /* reasigne node pointers */
        b->next = a;
        prev_a->next = b;
    } else {
        /* otherwise */
        /* AHA: need to use tmp_a_next, instead of tmp_a at the beginning */

        /* temporary a next, because a gets reassigned */
        struct month *tmp_a_next = a->next;
        prev_a = get_previous_month(head, a); /* get preceding of a */
        prev_b = get_previous_month(head, b); /* and b */
        prev_a->next = b;                     /* use preceding of a */
        a->next = b->next;
        b->next = tmp_a_next;
        prev_b->next = a;
    }

    /* default return same head */
    return head;
}

struct month *selection_sort(struct month *head) {
    /* Implement the selection sort algorithm */
    /* AHA: k->next instead of i->next or tmp_i->next */

    struct month *i; /* traveling pointer outer loop */
    struct month *j; /* traveling pointer inner loop */
    struct month *k; /* temporary storage for min val in inner loop */

    i = head;
    while (i != NULL) { /* for i=1 to n-1 do */
        print_months(head);

        k = i; /* k=i */
        j = i->next;
        while (j != NULL) { /* for j=i+1 to n do  */
            if (j->month_number < k->month_number) {
                k = j; /* if A[j] < A[k] then k=j */
            }
            j = j->next; /* j++ */
        }
        head = swap_month(head, i, k); /* exchange A[i] and A[k]*/

        i = k->next; /* i++ */
    }

    /* because head might have changed */
    return head;
}

struct month *init_months(struct month *head) {
    int n = 12;
    int init_order[n];
    char *month_strings[] = {"January",   "February", "March",    "April",
                             "May",       "June",     "July",     "August",
                             "September", "Oktober",  "November", "Dezember"};
    struct month *h;
    struct month *p; /* trailing pointer */

    /* create random order with fisher-yates shuffle */
    for (int i = 0; i < n; ++i) {
        init_order[i] = i + 1;
    }
    srand(time(0));
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1); /* generate random index below i */
        /* swap a[i] with a[j] */
        int tmp = init_order[i];
        init_order[i] = init_order[j];
        init_order[j] = tmp;
    }

    /* create month linked list */
    h = malloc(sizeof(struct month)); /* first node, gets returned */
    h->month_number = init_order[0];  /*  */
    h->month_name = month_strings[h->month_number - 1];
    p = h; /* pointer that goes through list */
    for (int i = 1; i < n; ++i) {
        struct month *m = malloc(sizeof(struct month));
        /* printf("create month %d\n", i); */
        m->month_number = init_order[i];
        m->month_name = month_strings[m->month_number - 1];
        p->next = m; /* previous node points now to this */

        p = m; /* increment trailing pointer */
    }
    p->next = NULL;
    return h;
}

void free_months(struct month *head) {
    /* free month linked list */
    struct month *p = head;
    struct month *q = head->next;
    while (q) {
        /* printf("free %d\n", p->month_number); */
        free(p);
        p = q;
        q = q->next;
    }
    free(p);
}


//Merging


struct node
{
    int val;
    struct node *next;
    struct node *prev;
};

struct node *merge(struct node *list1, struct node *list2) {

    /* Check for empty lists */
    /* AHA: makes it faster */
    if (list1 == NULL) {
        return list2;
    } else if (list2 == NULL) {
        return list1;
    }

    /* pointer to the head of the new merged list */
    struct node *head = malloc(sizeof(struct node));
    head->next = NULL;
    head->prev = NULL;

    /* traveling pointers */
    struct node *p = head;      /* for the merge list */
    struct node *p1 = list1;    /* for the list 1 */
    struct node *p2 = list2;    /* for the list 2 */

    /* while both lists have elements */
    while (p1 && p2) {
        if (p1->val < p2->val) {
            p->next = p1;       /* link p1 to merged trailing */
            p1->prev = p;
            p1 = p1->next;      /* move traveling p1 */
        } else {
            p->next = p2;       /* link p2 to merged trailing */
            p2->prev = p;
            p2 = p2->next;      /* mvoe traveling p2 */
        }
        p = p->next;            /* move traveling p of merged to recently added */
    }

    /* once one list is finished, handle remaining in the other */
    /* AHA: no list is needed */
    /* AHA: here also if, because might finish at the same time */
    if (p1) {
        p->next = p1;
        p1->prev = p;
    } else if (p2) {
        p->next = p2;
        p2->prev = p;
    }

    /* return pointer to new head */
    return head->next;
}

void printList(struct node *head) {
    while (head != NULL) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

void printListback(struct node *tail) {
    while (tail != NULL) {
        printf("%d ", tail->val);
        tail = tail->prev;
    }
    printf("\n");
}

static void Task2MonthforAll () {
    /* example usage */
    struct node *list1 = NULL;
    struct node *list2 = NULL;

    /* populate the lists with sorted values */
    int list1Values[] = {1, 3, 5, 7, 9};
    int list2Values[] = {2, 4, 6, 8, 10};
    /* fill in reversed order to not loose the head list1 or list2 */
    for (int i = 4; i >= 0; --i) {
        struct node *newNode = malloc(sizeof(struct node));
        newNode->val = list1Values[i];
        newNode->next = list1;
        newNode->prev = NULL;
        if (list1 != NULL) {
            list1->prev = newNode;
        }
        list1 = newNode;
    }
    for (int i = 4; i >= 0; --i) {
        struct node *newNode = malloc(sizeof(struct node));
        newNode->val = list2Values[i];
        newNode->next = list2;
        newNode->prev = NULL;
        if (list2 != NULL) {
            list2->prev = newNode;
        }
        list2 = newNode;
    }

    printf("List 1: ");
    printList(list1);

    printf("List 2: ");
    printList(list2);

    /* merge the two lists and print the result */
    struct node *mergedList = merge(list1, list2);

    printf("Merged List: ");
    printList(mergedList);

    /* free */
    struct node *tmp;
    while (mergedList != NULL) {
        tmp = mergedList;
        mergedList= mergedList->next;
        free(tmp);
    }
}

struct mynode{
    int val;
    struct mynode *next;
    struct mynode *prev;
};


int main(int argc, char *argv[]) {
    basicpointers();
    doublepointers();
    triplepointers();
    arraypointer();

    struct month *head;
    //head = init_months(head);
    Task2MonthforAll();

    // printf("Sorting:\n");
    // print_months(head);
    //
    // /* sort and print */
    // head = selection_sort(head);
    // print_months(head);

    //free_months(head);

    char *string = "hello";
    char string1[] = "hello1234";
    printf("%s,  %c \n", string, *(string+2));
    printf("%s,  %c \n", string1, *(string1+1));

    // Transfrom Array into double linked list
    int array[] = { 5, 8, 9, 11, 14, 19, 44};
    struct mynode *head1 = NULL;
    struct mynode *tail = NULL;
    struct mynode *node;
    bool isFirstItertion = true;
    for(int x = 6; x >= 0; x--) {
        node = malloc(sizeof(struct mynode));
        node -> val = array[x];
        node -> next = head1;
        if(isFirstItertion) {
            tail = node;
            isFirstItertion = false;
        } else{
        node -> prev = NULL;
        }
        if(head1 != NULL) {
            head1->prev = node;
        }
        head1 = node;
    }

    printList(head1);
    printListback(tail);

    return 0;
}

