#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 3
#define MAXLEN 512
#ifdef OS_TYPE
    #define CLS system("clear")
#else
    #define CLS system("cls")
#endif /*OS_TYPE*/
struct info{
    char *name;
    char *plase_of_employment;
    int age;
    int number_of_hours_per_week;
    float current_salary;
    float first_salary;
    int kpi_per_month[LEN];
};

struct LNode {
    int   id;
    char  *name;  /* data area */
    char *plase_of_employment;
    int age;
    int number_of_hours_per_week;
    float current_salary;
    float first_salary;
    int kpi_per_month[LEN];
    struct LNode *next;     /* link to next node */
};

struct LHead {
    int cnt;
    int max_id;
    struct LNode *first;
    struct LNode *last;
};

typedef struct LHead Head;

typedef struct LNode Node; /* datatype for pointer to node */

typedef struct info inf;

Head *make_head();

Node *create_node(inf *str0);

void add_first(Head *my_head, Node *new_node);

void insert_after(Head *my_head, Node *new_node, Node *current_node);

Node *select_by_id(Head *my_head, int n);

void delete_selected(Head *my_head, Node *current_node);

char **simple_split(char *str, int length, char sep);

void clear_string_array(char **str, int n);

inf *struct_fill(char **str);

void struct_out(inf *str0);
void print_header();

void print_list_header();

void list_out(Node *str0);

int show_menu1(int n, inf **str0, Head *p0, Node *p);

void show_info();

void continue1();

void add_card(int n, inf **inf0, char sep0,Head *p0, Node *p);

inf **edit_card(int n,inf **inf0, Head *p0, Node *p);

void delete_card(Head *p0, Node *p);

void find_card(Head *p0, Node *p);

int main(){

    enum {maxlen = 512};
    inf **inf1;
    int n, slen, i,option, m, add;
    float (**kind)(inf**, int)=NULL;
    char s1[MAXLEN], sep;
    FILE *f1;
    char **s2;
    Head *p0;
    Node *p, *my_node=NULL;

    sep = ';';
    f1 = fopen("-win-base.txt","r");
    if (f1 != NULL){
        n=0;

        while((fgets(s1,maxlen,f1))!=NULL) n++;
        rewind(f1);

        inf1=(inf**)malloc(n*sizeof(inf));
        if (inf1 != NULL)
        {
        for(i=0;i<n;i++)
        {
            fgets(s1,maxlen,f1);
            slen=strlen(s1);
            s1[slen-1]='\0';
            slen=strlen(s1);

            s2=simple_split(s1,slen,sep);
            if (s2!=NULL)
            {
                inf1[i]=struct_fill(s2);
                if (inf1[i]==NULL)
                {
                    printf("structure not allocated");
                    i=n;
                }
            }
            else printf("error at data reading");
        }
        }
        else printf("error at memory allocation!");
        fclose(f1);

        p0=make_head();
        p=create_node(inf1[0]);
        add_first(p0,p);
        p=p0->first;
        for (i=1;i<n;i++){
            my_node=create_node(inf1[i]);
            insert_after(p0, my_node, p);
            p=my_node;
        }
        p=p0->first;
        for(i=0;i<(p0->cnt);i++){
            if ((p->id) > (p0->max_id)){
                p0->max_id=p->id;
            }
            p=p->next;
        }
    } else puts("error at opening file!");

    do {
        option = show_menu1(n, inf1,p0,p);
        switch (option)
        {
            case 0:
                show_info();
                break;
            case 1:
                add_card(n,inf1,sep, p0, p);
                n++;
                continue1();
                break;
            case 2:
                inf1=edit_card(n,inf1,p0,p);
                continue1();
                break;
            case 3:
                delete_card(p0,p);
                n--;
                continue1();
                break;
            case 4:
                find_card(p0, p);
                continue1();
                break;
            case 5:
                continue1();
                break;
        }
    }while (option != 6);
    return 0;
}

char **simple_split(char *str, int length, char sep)
{
    char **str_array=NULL;
    int i,j,k,m;
    int key,count;
    for(j=0,m=0;j<length;j++)
    {
        if(str[j]==sep) m++;
    }

    key=0;
    str_array=(char**)malloc((m+1)*sizeof(char*));
    if(str_array!=NULL)
    {
        for(i=0,count=0;i<=m;i++,count++)
        {
            str_array[i]=(char*)malloc(length*sizeof(char));
            if(str_array[i]!=NULL) key=1;
            else
            {
                key=0;
                i=m;
            }
        }
        if(key)
        {
            k=0;
            m=0;
            for(j=0;j<length;j++)
            {
                if(str[j]!=sep) str_array[m][j-k]=str[j];
                else
                {
                    str_array[m][j-k]='\0';
                    k=j+1;
                    m++;
                }
            }
        }
        else
        {
            clear_string_array(str_array,count);
        }
     }
     return str_array;
}

void clear_string_array(char **str, int n)
{
    int i;

    for(i=0;i<n;i++)
    {
        free(str[i]);
        str[i]=NULL;
    }
    free(str);
    str=NULL;

}

inf *struct_fill(char **str)
{
    inf *str0=NULL;

    str0=(inf*)malloc(sizeof(inf));
    if(str0!=NULL)
    {
        str0->name=str[0];
        str0->plase_of_employment=str[1];
        str0->age=atoi(str[2]);
        str0->number_of_hours_per_week=atoi(str[3]);
        str0->current_salary=atof(str[4]);
        str0->first_salary=atof(str[5]);
        str0->kpi_per_month[0]=atoi(str[6]);
        str0->kpi_per_month[1]=atoi(str[7]);
        str0->kpi_per_month[2]=atoi(str[8]);
    }
    return str0;
}


void print_header()
{
    printf("|%20s |%20s |%6s |%4s |%8s |%8s |%6s |%6s|%6s|\n","name","plase of work","age","hour","salary","1 salary","month1","month2","month3");
    printf("+---------------------+---------------------+-------+-----+---------+---------+-------+------+------+\n");
}

void print_list_header()
{
    printf("|%3s|%20s |%20s |%6s |%4s |%8s |%8s |%6s |%6s|%6s|\n","id","name","plase of work","age","hour","salary","1 salary","month 1","month 2","month 3");
    printf("+---+---------------------+---------------------+-------+-----+---------+---------+--------+-------+-------+\n");
}

void list_out(Node *str0)
{
    printf("|%3d|%20s |%20s |%6d |%4d |%8.3f |%8.3f |%7d |%7d|%7d|\n",
        str0->id,str0->name,str0->plase_of_employment,str0->age,str0->number_of_hours_per_week,str0->current_salary,str0->first_salary,str0->kpi_per_month[0],str0->kpi_per_month[1],str0->kpi_per_month[2]);
}
/*del in future*/
void struct_out(inf *str0)
{
    printf("|%20s |%20s |%6d |%4d |%8.3f |%8.3f |%6d |%6d|%6d|\n",
        str0->name,str0->plase_of_employment,str0->age,str0->number_of_hours_per_week,str0->current_salary,str0->first_salary,str0->kpi_per_month[0],str0->kpi_per_month[1],str0->kpi_per_month[2]);
}

Head *make_head()
{
    Head *ph=NULL;

    ph=(Head*)malloc(sizeof(Head));
    if(ph)
    {
        ph->cnt=0;
        ph->max_id=0;
        ph->first=NULL;
        ph->last=NULL;
    }
    return ph;
}

Node *create_node(inf *str0) /* node initialization */
{
    Node *new_node=NULL; /* pointer to new node */


    new_node = (Node*)malloc(sizeof(Node));

    if(new_node)
    {
        new_node->id = 1;    /* setting node ID to 1 */
        new_node->name=str0->name;
        new_node->plase_of_employment=str0->plase_of_employment;
        new_node->age=str0->age;
        new_node->number_of_hours_per_week=str0->number_of_hours_per_week;
        new_node->current_salary=str0->current_salary;
        new_node->first_salary=str0->first_salary;
        new_node->kpi_per_month[0]=str0->kpi_per_month[0];
        new_node->kpi_per_month[1]=str0->kpi_per_month[1];
        new_node->kpi_per_month[2]=str0->kpi_per_month[2];
        new_node->next = NULL;           /* next node is absent */
    }
    return new_node;  /* return of node address */
}

void add_first(Head *my_head, Node *new_node)
{
    if(my_head&&new_node)
    {
        my_head->first = new_node;
        my_head->last = new_node;
        my_head->cnt++;
        my_head->max_id++;
    }
}

void insert_after(Head *my_head, Node *new_node, Node *current_node)
{
    int n;
    if(my_head&&new_node&&current_node)
    {
        n=my_head->cnt+1;
        if(current_node->next==NULL)
        {
            current_node->next=new_node;
            my_head->last=new_node;
        }
        else
        {
            new_node->next = current_node->next;
            current_node->next=new_node;
        }
        new_node->id=n;
        my_head->cnt=n;
    }
}


Node *select_by_id(Head *my_head, int n)
{
    Node *q;
    int k;

    q=my_head->first;
    k=my_head->cnt; /* last node id */
    if((n>0)&&(n<=k))
    {
        while((q->id)!=n) q=q->next;
    }
    else q=NULL;
    return q;
}

void delete_selected(Head *my_head, Node *current_node)
{
    Node *q, *q1;

    q=my_head->first;
    q1=my_head->last;
    if(current_node==q)
    {
        my_head->first=current_node->next;
        current_node->next=NULL;
        free(current_node);
    }
    else
    {
        while(q!=NULL)
        {
            if(q->next==current_node)
            {
                if(current_node==q1) my_head->last=q;
                q->next=current_node->next;
                current_node->next=NULL;
                free(current_node);
            }
            else q=q->next;
        }
    }
    my_head->cnt--;
    my_head->max_id=0;
}

int show_menu1(int n, inf **str0, Head *p0, Node *p){
    int way;

    print_list_header();
    p=p0->first;
    while(p!=NULL)
    {
        list_out(p);
        p=p->next;
    }
    do{
        puts("Press:");
        puts("0 - information about program");
        puts("1 - add card");
        puts("2 - edit card");
        puts("3 - delete card");
        puts("4 - find cards by parameter");
        puts("5 - sort cards by parameter");
        puts("6 - save and exit");

        scanf("%d", &way);
        if (way<0 || way>6)
            {
                puts("try again");
            }
    } while (way<0 || way>6);
    return way;
}

void show_info(int n, inf **str0)
{
    puts("----------------------------------------------------");
    puts("Information about program:");
    puts("This program works with information about employees.");
    puts("You can see, search, edit and sort it.\n");
    puts("Author: Gusir Mikhail Yurievich, SPbETU 'LETI' student");
    puts("----------------------------------------------------");
    continue1();
}

void add_card(int n, inf **inf0, char sep0,Head *p0, Node *p)
{
    char s1[MAXLEN];
    int slen;
    char **s2;
    FILE *fout;
    Node *my_node=NULL;

    n++;
    inf0=(inf**)realloc(inf0,n*sizeof(inf));
    printf("Enter all array, use ';' as separator: ");

    fgets(s1, MAXLEN, stdin);
    fgets(s1, MAXLEN, stdin);

    fout = fopen("-win-base.txt","a");
    if (fout !=NULL){
        fputs(s1,fout);
    } else puts("Error at opening output file");
    fclose(fout);

    slen=strlen(s1);
    s1[slen-1]='\0';
    slen=strlen(s1);

    s2=simple_split(s1,slen,sep0);

    if (s2!=NULL)
    {
        inf0[n-1]=struct_fill(s2);
        puts("Successful!");
    }
    else printf("error at data reading");
    my_node=create_node(inf0[n-1]);
    p=p0->last;
    insert_after(p0, my_node, p);
    p=my_node;


}

inf **edit_card(int n,inf **inf0, Head *p0, Node *p){
    int n1, new_int;
    char field[MAXLEN], new_param[MAXLEN];
    double new_double;

    puts("Enter worker's id:");
    scanf("%d", &n1);
    puts("Enter the field you want to edit:");
    fgets(field, MAXLEN, stdin);
    fgets(field, MAXLEN, stdin);
    field[strlen(field)-1]='\0';
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! тут поменять!!!!!!*/
    if (strcmp(field,"name")==0){
        printf("enter new name: ");
        fgets(new_param, MAXLEN, stdin);
        new_param[strlen(new_param)-1]='\0';
        p=select_by_id(p0,n1);
        p->name = new_param;
        list_out(p);
    }
    if (strcmp(field,"plase of work")==0){
        printf("enter new plase of work: ");
        fgets(new_param, MAXLEN, stdin);
        new_param[strlen(new_param)-1]='\0';
        p=select_by_id(p0,n1);
        p->plase_of_employment = new_param;
        list_out(p);
    }
    if (strcmp(field,"age")==0){
        printf("enter new age: ");
        scanf("%d", &new_int);
        p=select_by_id(p0,n1);
        p->age = new_int;
        list_out(p);
    }
    if (strcmp(field,"hour")==0){
        printf("enter new number of hours per week: ");
        scanf("%d", &new_int);
        p=select_by_id(p0,n1);
        p->number_of_hours_per_week = new_int;
        list_out(p);
    }
    if (strcmp(field,"salary")==0){
        printf("enter new salary: ");
        scanf("%lf", &new_double);
        p=select_by_id(p0,n1);
        p->current_salary = new_double;
        list_out(p);
    }
    if (strcmp(field,"1 salary")==0){
        printf("enter new first salary: ");
        scanf("%lf", &new_double);
        p=select_by_id(p0,n1);
        p->first_salary = new_double;
        list_out(p);
    }
    if (strcmp(field,"month 1")==0){
        printf("enter new number of hours per week: ");
        scanf("%d", &new_int);
        p=select_by_id(p0,n1);
        p->kpi_per_month[0] = new_int;
        list_out(p);
    }
    if (strcmp(field,"month 2")==0){
        printf("enter new number of hours per week: ");
        scanf("%d", &new_int);
        p=select_by_id(p0,n1);
        p->kpi_per_month[1] = new_int;
        list_out(p);
    }
    if (strcmp(field,"month 3")==0){
        printf("enter new number of hours per week: ");
        scanf("%d", &new_int);
        p=select_by_id(p0,n1);
        p->kpi_per_month[2] = new_int;
        list_out(p);
    }
    return inf0;
}

void delete_card(Head *p0, Node *p){
    int n2;
    char str[MAXLEN];
    Node *tmp1=NULL;

    printf("enter id: ");
    scanf("%d", &n2);

    tmp1=select_by_id(p0,n2);
    delete_selected(p0,tmp1);
}

void find_card(Head *p0, Node *p){
    char field[MAXLEN],new_param[MAXLEN];
    int n1, new_int;
    double new_double;

    printf("enter field: ");
    fgets(field, MAXLEN, stdin);
    fgets(field, MAXLEN, stdin);
    field[strlen(field)-1]='\0';

    if (strcmp(field,"name")==0){
        printf("enter name: ");
        fgets(new_param, MAXLEN, stdin);
        new_param[strlen(new_param)-1]='\0';
        print_list_header();
        p=p0->first;
        while(p!=NULL)
        {
            if (strcmp(new_param,p->name)==0) list_out(p);
            p=p->next;
        }
    }
    if (strcmp(field,"plase of work")==0){
        printf("enter plase of work: ");
        fgets(new_param, MAXLEN, stdin);
        new_param[strlen(new_param)-1]='\0';
        print_list_header();
        p=p0->first;
        while(p!=NULL)
        {
            if (strcmp(new_param,p->plase_of_employment)==0) list_out(p);
            p=p->next;
        }
    }
    if (strcmp(field,"age")==0){
        printf("enter age: ");
        scanf("%d", &new_int);
        print_list_header();
        p=p0->first;
        while(p!=NULL)
        {
            if (p->age==new_int) list_out(p);
            p=p->next;
        }
    }
    if (strcmp(field,"hour")==0){
        printf("enter number of hours per week: ");
        scanf("%d", &new_int);
        print_list_header();
        p=p0->first;
        while(p!=NULL)
        {
            if (p->number_of_hours_per_week==new_int) list_out(p);
            p=p->next;
        }
    }
    if (strcmp(field,"salary")==0){
        printf("enter salary: ");
        scanf("%lf", &new_double);
        print_list_header();
        p=p0->first;
        while(p!=NULL)
        {
            if (p->current_salary==new_double) list_out(p);
            p=p->next;
        }

    }
    if (strcmp(field,"1 salary")==0){
        printf("enter first salary: ");
        scanf("%lf", &new_double);
        print_list_header();
        p=p0->first;
        while(p!=NULL)
        {
            if (p->first_salary==new_double) list_out(p);
            p=p->next;
        }
    }
    if (strcmp(field,"month 1")==0){
        printf("enter kpi: ");
        scanf("%d", &new_int);
        print_list_header();
        p=p0->first;
        while(p!=NULL)
        {
            if (p->kpi_per_month[0]==new_int) list_out(p);
            p=p->next;
        }
    }
    if (strcmp(field,"month 2")==0){
        printf("enter kpi: ");
        scanf("%d", &new_int);
        print_list_header();
        p=p0->first;
        while(p!=NULL)
        {
            if (p->kpi_per_month[1]==new_int) list_out(p);
            p=p->next;
        }
    }
    if (strcmp(field,"month 3")==0){
        printf("enter kpi: ");
        scanf("%d", &new_int);
        print_list_header();
        p=p0->first;
        while(p!=NULL)
        {
            if (p->kpi_per_month[2]==new_int) list_out(p);
            p=p->next;
        }
    }
}

void continue1() {
    int next;

    printf("Press 1 to continue \n");
    scanf("%d", &next);
    while (next != 1) {
        scanf("%d", &next);
    }
    CLS;
}
