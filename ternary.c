
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>


struct node{
	char ch;
	int end;
	struct node* left;
	struct node* right;
	struct node* equal;
};

struct Node{
    struct node* first;
    char second[100];
    int third;
};

struct qnode
{
    struct Node* newnode;
    struct qnode* next;
};

struct node* newnode(char ch)
{
	struct node* newnode=(struct node*)malloc(sizeof(struct node));
	newnode->ch=ch;
	newnode->end=0;
	newnode->left= newnode->equal=newnode->right=NULL;
	return newnode;
}
void insert(struct node** root, char *word)
{
	if(*root==NULL)
	{
		*root=newnode(*word);
	}
	if((*word)<(*root)->ch)
	{
		insert(&((*root)->left),word);
	}
	else if((*word)>(*root)->ch)
	{
		insert(&((*root)->right),word);
	}
	else
	{
		if(*(word+1))
		{
			insert(&((*root)->equal),word+1);
		}
		else
		{
			(*root)->end=1;
		}
	}
}


int search(struct node* root,char *word)
{
	if(root==NULL)
	{
		return 0;
	}
	if(*word<(root)->ch)
	{
		
		return search(root->left,word);
		
	}
	else if(*word>(root)->ch)
	{
		return search(root->right,word);
		

	}
	else
	{
		if(*(word+1)=='\0')
		{
		
			return root->end;
		}
		else
		{
			
			return search(root->equal,word+1);
			
		}
	}
}


struct qnode* head=NULL;
struct qnode* tail=NULL;
void push(struct node* curr,char *str,int val)
{
   struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
   temp->first=curr;
   strncpy(temp->second,"",sizeof(temp->second));
   strncat(temp->second,str,strlen(str));
   temp->third=val;
   struct qnode* temp2=(struct qnode*)malloc(sizeof(struct qnode));
   temp2->newnode=temp;
   if(head==NULL)
   {
      head=temp2;
      tail=temp2;
      temp2->next=NULL;
   }
   else
   {
       tail->next=temp2;
       tail=temp2;
       temp2->next=NULL;
   }
   
}

struct Node* pop()
{
    struct Node* temp=head->newnode;
    head=head->next;
    return temp;
}

int empty()
{
    if(head==NULL)return 1;
    else return 0;
}

char** bfs(struct node* root,char *str)
{
    char** substr=malloc(100*sizeof(char*));
    for(int i=0;i<100;i++)
    {
        substr[i]=malloc(100*sizeof(char));
        strncpy(substr[i],"",sizeof(substr[i]));
    }
    struct node* cur=(struct node*)malloc(sizeof(struct node));
    push(root,str,1);
    int i=0;
    while(!empty())
    {
        struct Node* temp;
        temp=pop();
        cur=temp->first;
        char str[100]="";
        strncpy(str,"",sizeof(str));
        strncat(str,temp->second,strlen(temp->second));
        int add=temp->third;
        
        if(cur->end==1 && add==1)
        {
            strncat(substr[i],str,strlen(str));
            i++;
        }
        if(i==99)break;
        if(cur->left!=NULL)push(cur->left,str,0);
        if(cur->equal!=NULL)push(cur->equal,strncat(str,&(cur->ch),1),1);
        if(cur->right!=NULL)push(cur->right,str,0);
    }
    return substr;
}


void final(struct node* root,char* str,char* ret,struct node* temp)
{
    int add=0;

    while(search(temp,ret)!=1)
    {
        
        strncat(ret,&(root->ch),1);
        if(search(temp,ret))
        {
            return ;
        }
        add=1;
        root=root->equal;
        
    }
}


void suggest(struct node* root,char *str,char *ret,struct node* temp)
{
    char** substr=malloc(100*sizeof(char*));
    for(int i=0;i<100;i++)
    {
        substr[i]=malloc(100*sizeof(char));
        substr[i]="";
    }
    struct node* prev=NULL;
    int n=strlen(str);
    int i=0;
    while(i<n)
    {
        if(root==NULL)return ;
        if(root->ch==str[i])
        {
            prev=root;
            root=root->equal;
            i++;
            continue;
        }
        if(root->ch<str[i])root=root->right;
        else root=root->left;
    }
    strncpy(ret,str,strlen(str));
    final(root,str,ret,temp);
}




int main()
{
	FILE *fptr=fopen("./words.txt","r");
	if(fptr==NULL)
	{
		printf("Error openeing the file");
		exit(1);
	}
    struct node* root=NULL;
	char a;
	char real[100]="";
	char word[100]="";
	
	while ((a=fgetc(fptr))!=EOF)
	{ 
		if(a =='\n')
		{
			insert(&root,word);
			memset(word,0,strlen(word));
		}
		else
		{
			strncat(word,&a,1);
		}
	} 

    char s[100]="";
	char c;
	char cha;
    struct node* temp=root;
	while(c=getchar())
	{
        char** substr;
		c=tolower(c);
		if(c==' ' || c=='\n'||c==','||c=='.'||c=='!'||c=='?'||c==';'||c==':')
		{
			
			if(search(root,s))
			{
				printf("%s ",s);
			}
			else{
				suggest(root,s,real,temp);
                root=temp;
				printf(" \e[4m%s\e[0m ",s);
				printf("(did you mean: ");
				printf("%s",real);
                
				printf(")");
            
				memset(real,0,strlen(real));
			}
			
			memset(s,0,strlen(s));
		}
		else
		{
            strncat(s,&c,1);
		}
		int val=strcmp(s,"exit");
		if(val==0) return 0;
	}
            
}