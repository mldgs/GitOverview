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

struct workNode {
    char *name;
    struct workNode *next;
};

struct workHead{
   struct workNode *first;
};

struct ageNode{
    int age;
    struct ageNode *next;
};

struct ageHead{
    struct ageNode *first;
};
typedef struct LHead Head;

typedef struct LNode Node; /* datatype for pointer to node */

typedef struct info inf;

typedef struct workNode wrkNode;

typedef struct workHead wrkHead;

typedef struct ageNode ageNode;

typedef struct ageHead ageHead;

Head *make_head();

wrkHead *make_workhead();

ageHead *make_agehead();

wrkNode *create_wrknode(char *s);

ageNode *create_agenode(int age1);

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

inf** add_card(int n, int n1, int n2, inf **inf0, char sep0,Head *p0, Node *p);

void edit_card(int n,inf **inf0, Head *p0, Node *p, wrkHead *w0, wrkNode *w, ageHead *a0,ageNode *a);

void delete_card(Head *p0, Node *p, wrkHead *w0, wrkNode *w, ageHead *a0, ageNode *a);

void delete_agedir(ageHead *head, ageNode *age0);

void delete_wrkdir(wrkHead *head, wrkNode *wrd0);

void find_card(Head *p0, Node *p, wrkHead *w0, wrkNode *w, ageHead *a0, ageNode *a);
/*output to file*/
void save_to_file(Head *p0, Node *p, wrkHead *w0, wrkNode *w, ageHead *a0, ageNode *a);
/*functions below are needed for sort*/
float AgeValue(inf **str0, int i0);

float HwValue(inf **str0, int i0);

float csalValue(inf **str0, int i0);

float fsalValue(inf **str0, int i0);

float kpi1Value(inf **str0, int i0);

float kpi2Value(inf **str0, int i0);

float kpi3Value(inf **str0, int i0);

void SortKind(int n, inf **str0, float (*funcName)(inf**, int));

int main(){
    enum {maxlen = 512};
    inf **inf1;
    int n, n1, n2, slen, i, option,tmpage, inwork, inage;
    int *s5;
    float (**kind)(inf**, int)=NULL;
    char s1[MAXLEN],s[MAXLEN], sep;
    FILE *f1, *f2, *f3;
    char **s2,s3[MAXLEN], **s4 = NULL;
    Head *p0;
    Node *p, *my_node=NULL;
    ageHead *a0;
    ageNode *age0, *a;
    wrkHead *w0;
    wrkNode *wrk0, *w;

    sep = ';';
    n=0;
    n1=0;
    f2 = fopen("-win-work.txt","r");
    f3 = fopen("-win-age.txt","r");
    if (f2 != NULL && f3 != NULL){
        w0 = make_workhead();
        while((fgets(s3,maxlen,f2))!=NULL) n1++;
        s4=(char**)malloc((n1+1)*sizeof(char*));
        rewind(f2);
        for(i=0;i<n1;i++){
            fgets(s3,maxlen,f2);
            s3[strlen(s3) - 1]='\0';
            s4[i]=(char*)malloc(strlen(s3)*sizeof(char));
            strcpy(s4[i], s3);
        }
        fclose(f2);
        w = create_wrknode(s4[0]);
        w0->first=w;
        w=w0->first;
        for(i=1;i<n1;i++){
            wrk0 = create_wrknode(s4[i]);
            w->next=wrk0;
            w=wrk0;
        }
        n2=0;

        a0=make_agehead();
        while((fgets(s3,maxlen,f3))!=NULL) n2++;
        s5=(int*)malloc((n2+1)*sizeof(int));
        rewind(f3);
        for(i=0;i<n2;i++){
            fgets(s3,maxlen,f3);
            s3[strlen(s3) - 1]='\0';
            s5[i]=strtol(s3,NULL,0);
        }
        fclose(f2);
        fclose(f3);
        a = create_agenode(s5[0]);
        a0->first = a;
        a=a0->first;
        for(i=1;i<n2;i++){
            age0 = create_agenode(s5[i]);
            a->next=age0;
            a=age0;
        }
        a=a0->first;
        while (a->next != NULL) a=a->next;

    }else puts("error at opening reference book");
    w=w0->first;
    while(w->next != NULL) w=w->next;


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
    } else puts("error at opening f1!");


    do {
        option = show_menu1(n, inf1,p0,p);
        switch (option)
        {
            case 0:
                show_info();
                break;
            case 1:
                puts("Does new worker's plase of work situates in this list?\n1 - yes\n2 - no");
                w=w0->first;
                while (w != NULL){
                    printf("%s\n", w->name);
                    w=w->next;
                }
                scanf("%d",&inwork);
                getchar();
                if (inwork == 2){
                    s4=(char**)realloc(inf1,(n+1)*sizeof(char*));
                    puts("Enter new place of work:");
                    fgets(s, MAXLEN, stdin);

                    s[strlen(s) - 1]='\0';
                    s4[n - 1]=(char*)malloc(strlen(s)*sizeof(char));
                    strcpy(s4[n - 1],s);
                    w=w0->first;
                    while (w->next != NULL){
                        w=w->next;
                    }
                    w->next=create_wrknode(s4[n-1]);
                    w=w->next;
                }
                puts("\nValid places of work:");
                w = w0->first;
                while (w != NULL){
                    printf("%s\n", w->name);
                    w=w->next;
                }
                puts("Does new worker's age situates in this list?\n1 - yes\n2 - no");
                a=a0->first;
                while (a!= NULL){
                    printf("%d\n",a->age);
                    a=a->next;
                }
                scanf("%d",&inage);
                getchar();
                if (inage == 2){
                    s5=(int*)realloc(inf1,(n+1)*sizeof(int));
                    puts("Enter new age");
                    scanf("%d",&tmpage);
                    getchar();

                    a=a0->first;
                    while (a->next != NULL){
                        a=a->next;
                    }
                    a->next=create_agenode(tmpage);
                    a=a->next;
                }
                puts("\nValid age:");
                a = a0->first;
                while (a != NULL){
                    printf("%d\n", a->age);
                    a=a->next;
                }

                inf1=add_card(n,n1,n2,inf1,sep, p0, p);
                n++;
                continue1();
                break;
            case 2:
                edit_card(n,inf1,p0,p,w0,w,a0,a);
                continue1();
                break;
            case 3:
                delete_card(p0,p, w0, w, a0, a);
                n--;
                continue1();
                break;
            case 4:
                find_card(p0, p, w0, w, a0, a);
                continue1();
                break;
            case 5:
                kind=(float(**)(inf**,int))malloc(n*sizeof(float(*)(inf**,int)));
                if (inf1 != NULL && kind)
                {
                    kind[0] = AgeValue;
                    kind[1] = HwValue;
                    kind[2] = csalValue;
                    kind[3] = fsalValue;
                    kind[4] = kpi1Value;
                    kind[5] = kpi2Value;
                    kind[6] = kpi3Value;
                    option = 0;
                    while((option<1)||(option>7)) {

                            printf("Enter parameter:\n");
                            printf("1 - age\n");
                            printf("2 - number of hours per week\n");
                            printf("3 - current salary\n");
                            printf("4 - 1st salary\n");
                            printf("5 - kpi 1st month\n");
                            printf("6 - kpi 2nd month\n");
                            printf("7 - kpi 3rd month\n");
                            printf("Enter your choice: ");

                            scanf("%d", &option);
                            fgets(s1, MAXLEN, stdin);
                        }
                    }

                    puts("result:");
                    print_header();
                    SortKind(n,inf1,kind[option-1]);
                    option = 5;
                    continue1();
                break;
        }
    }while (option != 6);

    save_to_file(p0,p,w0,w,a0,a);
    /*clearing memory*/
    if (inf1!= NULL){
        free(inf1);
        inf1=NULL;
    }
    if(kind!=NULL)
    {
        free(kind);
        kind=NULL;
    }
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
/*del in future??????????????????????????????????????????*/
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
    puts("Author: Gusir Mikhail Yurievich, SPbsETU 'LETI' student");
    puts("----------------------------------------------------");
    continue1();
}

inf** add_card(int n,int n1, int n2, inf **inf0, char sep0,Head *p0, Node *p)
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
    fout = fopen("-win-base - Copy.txt","a");
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
    return inf0;
}

void edit_card(int n,inf **inf0, Head *p0, Node *p, wrkHead *w0, wrkNode *w, ageHead *a0,ageNode *a){
    int n1, new_int, field,choice,count, *s5;
    char *new_param, **s4=NULL;
    double new_double;
    Node *p1;

    s4=(char**)malloc((n+1)*sizeof(char*));

    puts("Enter worker's id:");
    scanf("%d", &n1);
    getchar();
    puts("Enter the field you want to edit:");
    puts("1 - name\n2 - plase ow work\n3 - age\n4 - hour\n5 - salary\n6 - 1 salary\n7 - month1\n8 - month2\n9 - month3");
    scanf("%d", &field);
    getchar();

    new_param=(char*)malloc((MAXLEN)*sizeof(char));

    if (field == 1){
        printf("enter new name: ");
        fgets(new_param, MAXLEN, stdin);
        new_param[strlen(new_param)-1]='\0';
        p=select_by_id(p0,n1);
        p->name = new_param;
        list_out(p);
    }
    if (field == 2){
        puts("Does new plase of work already exists?\n1-yes\n2-no");
        scanf("%d",&choice);
        getchar();
        printf("enter new plase of work: ");
        fgets(new_param, MAXLEN, stdin);
        new_param[strlen(new_param)-1]='\0';
        p=select_by_id(p0,n1);

        count = 0;
        p1 = p0 -> first;
        while (p1 != NULL){
            if (strcmp(p->plase_of_employment,p1->plase_of_employment) == 0) count++;
        p1 = p1 -> next;
        }
        printf("COUNT = %d\n",count);
        if (count == 1){
        w=w0->first;
        while(w != NULL){
            if (strcmp(p->plase_of_employment,w->name) == 0) delete_wrkdir(w0,w);
            w=w->next;
        }
        }
        if (choice == 2){
        w = w0 -> first;
        while(w -> next != NULL){
            w = w -> next;
        }
        s4[0]=(char*)malloc(strlen(new_param)*sizeof(char));
        strcpy(s4[0],new_param);
        w->next = create_wrknode(s4[0]);
        p->plase_of_employment=w->next->name;
        }
        else{
        w=w0 -> first;
        while(w -> next != NULL){
            if (strcmp(new_param,w->name) == 0)
                p->plase_of_employment = w->name;
            w = w -> next;
        }
        }
        p->plase_of_employment = new_param;
        list_out(p);
    }
    if (field == 3){
        puts("Does new age already exists?\n1-yes\n2-no");
        scanf("%d",&choice);
        getchar();
        printf("enter new age: ");
        scanf("%d", &new_int);
        p=select_by_id(p0,n1);

        count = 0;
        p1 = p0 -> first;
        while (p1 != NULL){
            if (p->age==p1->age) count++;
        p1 = p1 -> next;
        }
        printf("COUNT = %d\n",count);
        if (count == 1){
        a=a0->first;
        while(a != NULL){
            if (p->age==a->age) delete_agedir(a0,a);
            a=a->next;
        }
        }
        if (choice == 2){
        a = a0 -> first;
        while(a-> next != NULL){
            a=a-> next;
        }
        s5=(int*)malloc((new_int)*sizeof(int));
        s5[0]=new_int;
        a->next = create_agenode(s5[0]);
        p->age=a->next->age;
        }
        else{
        a=a0 -> first;
        while(a -> next != NULL){
            if (new_int==a->age) p->age = a->age;
            a=a->next;
        }
        }

        p->age = new_int;
        list_out(p);
    }
    if (field == 4){
        printf("enter new number of hours per week: ");
        scanf("%d", &new_int);
        p=select_by_id(p0,n1);
        p->number_of_hours_per_week = new_int;
        list_out(p);
    }
    if (field == 5){
        printf("enter new salary: ");
        scanf("%lf", &new_double);
        p=select_by_id(p0,n1);
        p->current_salary = new_double;
        list_out(p);
    }
    if (field == 6){
        printf("enter new first salary: ");
        scanf("%lf", &new_double);
        p=select_by_id(p0,n1);
        p->first_salary = new_double;
        list_out(p);
    }
    if (field == 7){
        printf("enter new number of hours per week: ");
        scanf("%d", &new_int);
        p=select_by_id(p0,n1);
        p->kpi_per_month[0] = new_int;
        list_out(p);
    }
    if (field == 8){
        printf("enter new number of hours per week: ");
        scanf("%d", &new_int);
        p=select_by_id(p0,n1);
        p->kpi_per_month[1] = new_int;
        list_out(p);
    }
    if (field == 9){
        printf("enter new number of hours per week: ");
        scanf("%d", &new_int);
        p=select_by_id(p0,n1);
        p->kpi_per_month[2] = new_int;
        list_out(p);
    }
}

void delete_card(Head *p0, Node *p, wrkHead *w0, wrkNode *w, ageHead *a0, ageNode *a){
    int n2, choice1, choice2,i, i1,flag;
    Node *tmp1=NULL;

    i=1;
    i1=1;
    flag=0;
    puts("Press:\n1 - to delete by id\n2 - to delete from place of work directory\n3 - to delete from age directory");
    scanf("%d",&choice1);
    getchar();
    if (choice1 == 1){
        printf("enter id: ");
        scanf("%d", &n2);
        getchar();
        tmp1=select_by_id(p0,n2);
        delete_selected(p0,tmp1);
    }else if (choice1 == 2){
        puts("pick place of work:");
        w=w0->first;
        while (w != NULL){
            printf("%d %s\n",i, w->name);
            w=w->next;
            i++;
        }
        scanf("%d",&choice2);
        getchar();
        w=w0->first;
        while (i1 < choice2){
            w=w->next;
            i1++;
        }
        p=p0->first;
        while (p!=NULL){
            if (strcmp(p->plase_of_employment,w->name)==0){
                tmp1 = p;
                delete_selected(p0,tmp1);
                p=p0->first;
                flag=2;
            }
            if (flag != 2) p=p->next;
            flag = 1;
        }
        delete_wrkdir(w0,w);
    }else if (choice1 == 3){
        puts("pick age:");
        a = a0->first;
        while (a != NULL){
            printf("%d %d\n",i, a->age);
            a=a->next;
            i++;
        }
        scanf("%d",&choice2);
        getchar();
        a=a0->first;
        while (i1 < choice2){
            a=a->next;
            i1++;
        }
        p=p0->first;
        while (p!=NULL){
            if (p->age == a->age){
                tmp1 = p;
                delete_selected(p0,tmp1);
                p=p0->first;
                flag=2;
            }
            if (flag != 2) p=p->next;
            flag = 1;
        }
        delete_agedir(a0, a);
    }
}

void find_card(Head *p0, Node *p, wrkHead *w0, wrkNode *w, ageHead *a0, ageNode *a){
    char new_param[MAXLEN], *newpar;
    int  new_int, field, i, i1,choice;
    double new_double;

    i=1;
    i1=1;
    printf("enter field:\n");
    puts("1 - name\n2 - plase ow work\n3 - age\n4 - hour\n5 - salary\n6 - 1 salary\n7 - month1\n8 - month2\n9 - month3");
    scanf("%d", &field);
    getchar();
    if (field == 1){
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
    if (field == 2){
        puts("enter plase of work:");
        w=w0->first;
        while (w != NULL){
            printf("%d %s\n",i, w->name);
            w=w->next;
            i++;
        }
        scanf("%d",&choice);
        getchar();
        w=w0->first;
        while (i1 < choice){
            w=w->next;
            i1++;
        }
        newpar=(char*)malloc((strlen(w->name))*sizeof(char));

        strcpy(newpar,w->name);
        print_list_header();
        p=p0->first;
        while(p!=NULL)
        {
            if (strcmp(newpar,p->plase_of_employment)==0) list_out(p);
            p=p->next;
        }
    }
    if (field == 3){
        printf("enter age:\n");
        a = a0->first;
        while (a != NULL){
            printf("%d %d\n",i, a->age);
            a=a->next;
            i++;
        }
        scanf("%d", &choice);
        getchar();

        a=a0->first;
        while (i1 < choice){
            a=a->next;
            i1++;
        }

        print_list_header();
        p=p0->first;
        while(p!=NULL)
        {
            if (p->age==a->age) list_out(p);
            p=p->next;
        }
    }
    if (field == 4){
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
    if (field == 5){
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
    if (field == 6){
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
    if (field == 7){
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
    if (field == 8){
        printf("enter kpi: ");
        scanf("%d", &new_int);
        print_list_header();
        p=p0->first;
        while(p!=NULL)
        {
            if (p->kpi_per_month[1] == new_int) list_out(p);
            p=p->next;
        }
    }
    if (field == 9){
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

void save_to_file(Head *p0, Node *p, wrkHead *w0, wrkNode *w, ageHead *a0, ageNode *a){
    FILE *fout1, *fout2, *fout3;

    fout1 = fopen("-win-base.txt","w");
    fout2 = fopen("-win-work.txt","w");
    fout3 = fopen("-win-age.txt","w");
    p=p0->first;
    if (fout1 !=NULL){
        while(p!=NULL){
            fprintf(fout1,"%s;%s;%d;%d;%f;%f;%d;%d;%d\n",p->name,p->plase_of_employment,p->age,p->number_of_hours_per_week,p->current_salary,p->first_salary,p->kpi_per_month[0],p->kpi_per_month[1],p->kpi_per_month[2]);
            p=p->next;
        }
    } else puts("Error at opening output file");
    fclose(fout1);
    a=a0->first;
    if (fout3!=NULL){
        while (a!= NULL){
            fprintf(fout3,"%d\n",a->age);
            a=a->next;
        }
    } else puts("Error at opening output file");
    fclose(fout3);
    w=w0->first;
    if (fout2 !=NULL){
        while (a!= NULL){
            fprintf(fout2,"%s\n",w->name);
            w=w->next;
        }
    } else puts("Error at opening output file");
    fclose(fout2);
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

void SortKind(int n, inf **str0, float (*funcName)(inf**, int))
{
   inf *tmp_struct;
   int i, j;

    for(i=0;i<n;i=i+1)
    {
        for(j=0;j<n-i-1;j=j+1)
        {
            if(funcName(str0,j)>funcName(str0,j+1))
            {
                tmp_struct=str0[j];
                str0[j]=str0[j+1];
                str0[j+1]=tmp_struct;
            }
        }
     }
    for (i=0;i<n;i++)
    {
            struct_out(str0[i]);
    }
}

float AgeValue(inf **str0, int i0)
{
    return str0[i0]->age;
}

float HwValue(inf **str0, int i0)
{
    return str0[i0]->number_of_hours_per_week;
}

float csalValue(inf **str0, int i0)
{
    return str0[i0]->current_salary;
}

float fsalValue(inf **str0, int i0)
{
    return str0[i0]->first_salary;
}

float kpi1Value(inf **str0, int i0)
{
    return str0[i0]->kpi_per_month[0];
}
float kpi2Value(inf **str0, int i0)
{
    return str0[i0]->kpi_per_month[1];
}

float kpi3Value(inf **str0, int i0)
{
    return str0[i0]->kpi_per_month[2];
}
wrkHead *make_workhead(){
    wrkHead *ph = NULL;
    ph=(wrkHead*)malloc(sizeof(wrkHead));
    if(ph)
    {
        ph->first=NULL;
    }
    return ph;
}

ageHead *make_agehead(){
    ageHead *ph = NULL;
    ph=(ageHead*)malloc(sizeof(ageHead));
    if(ph)
    {
        ph->first=NULL;
    }
    return ph;
}

wrkNode *create_wrknode(char *s){
    wrkNode *new_work=NULL;
    new_work = (wrkNode*)malloc(sizeof(wrkNode));
    if (new_work){
        new_work->name = s;
        new_work->next = NULL;
    }
    return new_work;
}

ageNode *create_agenode(int age1){
    ageNode *new_age=NULL;
    new_age = (ageNode*)malloc(sizeof(ageNode));
    if (new_age){
        new_age->age = age1;
        new_age->next = NULL;
    }
    return new_age;
}

void delete_agedir(ageHead *head, ageNode *age0){
    ageNode *a;

    a = head->first;
    while (a -> next != NULL)
        a = a -> next;
    a = head -> first;
    if (age0 == a){
        head->first = age0-> next;
        age0->next = NULL;
    }
    else{
        while (a != NULL){
            if (a -> next == age0){
                a -> next = age0 -> next;
                age0 -> next = NULL;
            }
            else a=a->next;
        }
    }
}

void delete_wrkdir(wrkHead *head, wrkNode *wrk0){
    wrkNode *w;

    w = head->first;
    while (w->next!=NULL)
        w=w->next;
    w=head -> first;
    if (wrk0 == w){
        head->first = wrk0-> next;
        wrk0->next = NULL;
    }
    else{
        while (w!=NULL){
            if (w->next==wrk0){
                w->next=wrk0->next;
                wrk0->next=NULL;
            }
            else w=w->next;
        }
    }
}
