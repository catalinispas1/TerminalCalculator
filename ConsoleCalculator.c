#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct numNode
{
    double data;
    struct numNode* next;
}NumNode;

NumNode* num_head;

void add_num(int data)
{
    NumNode* node = (NumNode*)malloc(sizeof(NumNode));
    node -> data = data;
    node -> next = NULL;

    if(num_head == NULL)
    {
        num_head = node;
        return;
    }
    NumNode* n = num_head;
    
    while(n -> next != NULL)
    {
        n = n -> next;
    }
    n -> next = node;
}

void remove_num(int index)
{
    if(num_head == NULL) return;

    if(index == 0)
    {
        NumNode* temp = num_head;
        num_head = num_head -> next;
        free(temp);
        return;
    }

    NumNode* n = num_head;
    for(int i = 0; i < index - 1; i++)
    {
        if(n == NULL) return;
        n = n -> next; 
    }
    NumNode* temp = n -> next;
    n -> next = n -> next -> next;
    free(temp);
}

void set_num(int index, double data)
{
    NumNode* set_node = (NumNode*)malloc(sizeof(NumNode));
    set_node -> data = data;
    set_node -> next = NULL;

    if(index == 0)
    {
        set_node -> next = num_head;
        num_head = set_node;
    }

    NumNode* n = num_head;
    for(int i = 0; i < index - 1; i++)
    {
        if(n == NULL) return;
        n = n -> next;
    }

    NumNode* temp = n -> next -> next;
    n -> next = set_node;
    set_node -> next = temp;     
}

double get_num(int index)
{
    NumNode* n = num_head;
    for(int i = 0; i < index; i++)
    {
        n = n -> next;
    }
    return n -> data;
}

typedef struct signNode
{
    char sign;
    struct signNode* next;
}SignNode;

SignNode* sign_head;

void add_sign(char sign)
{
    SignNode* node = (SignNode*)malloc(sizeof(SignNode));
    node -> sign = sign;
    node -> next = NULL;

    if(sign_head == NULL)
    {
        sign_head = node;
        return;
    }
    SignNode* n = sign_head;
    
    while(n -> next != NULL)
    {
        n = n -> next;
    }
    n -> next = node;
}

void remove_sign(int index)
{
    if(sign_head == NULL) return;
    SignNode* n = sign_head;

    if(index == 0)
    {
        sign_head = sign_head -> next;
        free(n);
        return;
    }

    for(int i = 0; i < index - 1; i++)
    {
        if(n == NULL) return;
        n = n -> next;
    }
    SignNode* temp = n -> next;
    n -> next = n -> next -> next;
    free(temp);
}

char get_char(int index)
{
    SignNode* n = sign_head;
    for(int i = 0; i < index; i++)
    {
        n = n -> next;
    }
    return n -> sign;
}

void print_nums()
{
    NumNode* n = num_head;
    SignNode* m = sign_head;
    int index = 0;

    while (n != NULL)
    {
        if(sign_head == NULL) printf("Final result:\n");
        if(index % 2 == 0)
        {
            printf("%.2f", n -> data);
            n = n -> next;
        }
        else
        {
            printf(" %c ", m -> sign);
            m = m -> next;
        }
        index++;
    }
    printf("\n");
}

void plus(int index)
{
    double num1 = get_num(index);
    double num2 = get_num(index + 1);
    double plus = num1 + num2;
    set_num(index, plus);
    remove_num(index + 1);
    remove_sign(index);
}

void minus(int index)
{
    double num1 = get_num(index);
    double num2 = get_num(index + 1);
    double minus = num1 - num2;
    set_num(index, minus);
    remove_num(index + 1);
    remove_sign(index);
}

void hashtag(int index)
{
    double num1 = get_num(index);
    double num2 = get_num(index + 1);
    double hashtag = (num1 + num2) * (num1 + num2);
    set_num(index, hashtag);
    remove_num(index + 1);
    remove_sign(index);
}

void multiplication(int index)
{
    double num1 = get_num(index);
    double num2 = get_num(index + 1);
    double multiplication = num1 * num2;
    set_num(index, multiplication);
    remove_num(index + 1);
    remove_sign(index);
}

void divide(int index)
{
    double num1 = get_num(index);
    double num2 = get_num(index + 1);
    double divide = num1 / num2;
    set_num(index, divide);
    remove_num(index + 1);
    remove_sign(index);
}

bool check_sign_input(char* sign)
{
    int coun_size = 0;

    while(*(sign + coun_size) != '\0'){
        coun_size++;
        if(coun_size == 2) return false;
    }
    return (*sign == '+' || *sign == '-' || *sign == '#' || *sign == '*' || *sign == '/');
}

int main()
{
    int n;
    printf("Enter the number of numbers: ");
    scanf("%d", &n);
    for(int i = 0; i < n + n -1; i++)
    {
        if(i % 2 == 0)
        {
            int num;
            scanf("%d", &num);
            add_num(num);
        }
        else
        {
            char sign[3];
            scanf("%2s", &sign);
            if(!check_sign_input(sign)){
                printf("Wrong format");
                return 0;
            }
            char singleSign = sign[0];
            add_sign(singleSign);
        }
    }

    int priority = 3;
    int size_modified = 0;

    while(priority > 0)
    {
        for(int i = 0; i < n - 1 - size_modified; i++)
        {
            char sign = get_char(i);

            if(priority == 3)
            {
                if(sign == '*')
                {
                    multiplication(i);
                    print_nums();
                    i--;
                    size_modified++;
                }
                else if(sign == '/')
                {
                    divide(i);
                    print_nums();
                    i--;
                    size_modified++;
                }
            }

            else if(priority == 2)
            {
                if(sign == '#')
                {
                    hashtag(i);
                    print_nums();
                    i--;
                    size_modified++;
                }
            }

            else if(priority == 1)
            {
                if(sign == '+')
                {
                    plus(i);
                    print_nums();
                    i--;
                    size_modified++;
                }
                else if(sign == '-')
                {
                    minus(i);
                    print_nums();
                    i--;
                    size_modified++;
                }
            }
        }
        priority--;
    }
    return 0; 
}