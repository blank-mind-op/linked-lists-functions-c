#include <stdio.h>
#include <stdlib.h>

typedef struct cel
{
    // 1 : les datas pour nos tests
    int val;
    char s[80];
    // 2 : le pointeur pour l'élément suivant
    struct cel* next;
}cell;


cell* init()
{
    char* n[]={"A","B","C","D","E","F","G","H","I","J","K",
    "L","M","N","O","P","Q","R","S","T","U","V","X","Y","Z"};
    cell *e=malloc(sizeof(cell));
    e->val=rand()%26;
    strcpy(e->s,n[rand()%26]);
    e->next=NULL;
    return e;
}
cell* init2(int val,char*st)
{
    cell *e=malloc(sizeof(cell));
    strcpy(e->s,st);
    e->val = val;
    e->next=NULL;
    return e;
}
cell* ajout_debut1(cell*prem,cell*e)
{
    e->next=prem;
    prem=e;
    return prem;
}
void ajout_debut2(cell **prem,cell*e)
{
    e->next=*prem;
    *prem=e;
}
void print_liste(cell *L)
{
    cell *p=NULL;
    if(L==NULL)
    {
        printf("La liste est VIDE!\n");
    }
    else
    {
        for(p=L;p!=NULL;p=p->next)
        {
            printf("%s %d\n",p->s,p->val);
        }
    }
}
void supprimer_debut(cell**prem)
{
    cell*p=NULL;
    if(*prem!=NULL)
    {
        p=*prem;
        *prem=(*prem)->next;
        free(p);
    }
}
void supprime_x(cell**prem,int x)
{
    cell *prec=NULL,*p=NULL;
    int ind=0;
    p=*prem;
    prec=*prem;
    if(*prem==NULL)
    {
       printf("la liste est vide!\n");
    }
    else
    {
        if(p->val==x)
        {
            supprimer_debut(prem);
        }
        else
        {
            while(p!=NULL)
            {
                if(p->val!=x)
                {
                    prec=p;
                    p=p->next;
                }
                else
                {
                    prec->next=prec->next->next;
                    free(p);
                    ind=1;
                    break;
                }
            }
            if(ind==0)
            {
                printf("la valeur %d n'existe pas\n\n",x);
            }
        }
    }
}

void supprime_liste(cell **L)
{

    while(*L!=NULL)
    {
        supprimer_debut(L);
    }
}
void sauvgarde_txt(cell **L)
{
    FILE* f=fopen("sauv.txt","w");
    cell *p=*L;
    while(p!=NULL)
    {
        fprintf(f,"%d %s\n",p->val,p->s);
        p=p->next;
    }
    supprime_liste(L);
    fclose(f);
}
void sauvgarde_bin(cell **L)
{
    FILE* f=NULL;
    cell *p=*L;
    if((f=fopen("save_liste.bin","wb"))!=NULL)
    {
        while(p!=NULL)
        {
            fwrite(p,sizeof(cell),1,f);
            p=p->next;
        }
    }
   supprime_liste(L);
    fclose(f);
}
cell *restorer_txt(void)
{
    FILE* f=fopen("sauv.txt","r");

    int x;
    char Ch[4];
    cell* premier=NULL;
    cell*nouveau;
    do
    {
        fscanf(f,"%d %s",&x,Ch);
        //printf("%d %s\n",x,Ch);
        nouveau=init2(x,Ch);
        ajout_debut2(&premier,nouveau);

    }while(feof(f)==0);
    fclose(f);
    return premier;
}

cell *restorer_bin(void)
{
    FILE* f=NULL;
    fopen("sauv.txt","r");

    cell* premier=NULL;
    cell*nouveau;
    if(f=fopen("save_liste.bin","rb"))
    {
        do
        {
            nouveau=malloc(sizeof(cell));
            fread(nouveau,sizeof(cell),1,f);
            ajout_debut2(&premier,nouveau);

        }while(feof(f)==0);
    }

    fclose(f);
    return premier;
}


