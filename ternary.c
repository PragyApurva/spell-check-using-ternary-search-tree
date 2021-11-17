// C program to insert a node in AVL tree
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

void suggest(struct node* root,char *word,char *real,int c)
{
	if(root==NULL)
	{
		return ;
	}
	if(*word<(root)->ch)
	{
		if(root->left!=NULL &&   root->left->ch==word[0])
		{
			c=1;
		}
		
		if(root->left!=NULL && c==1){
			
        strncat(real,&root->left->ch,1);
		}
		return suggest(root->left,word,real,c);
	}
	else if(*word>(root)->ch)
	{
		if(root->right!=NULL &&   root->right->ch==word[0])
		{
			c=1;
		}
		if(root->right!=NULL && c==1){
		strncat(real,&root->right->ch,1);
		}
		return suggest(root->right,word,real,c);
	}
	else
	{
		   if(root->equal!=NULL && root->equal->ch==word[0])
		{
			c=1;
		}
		    if(root->equal!=NULL && c==1){
		    strncat(real,&root->equal->ch,1);
			}
			return suggest(root->equal,word+1,real,c);
		
	}
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
	while(c=getchar())
	{
		c=tolower(c);
		if(c==' ' || c=='\n'||c==','||c=='.'||c=='!'||c=='?'||c==';'||c==':')
		{
			
			if(search(root,s))
			{
				printf("%s ",s);
			}
			else{
				int c=0;
				suggest(root,s,real,c);
				printf(" \e[4m%s\e[0m (did you mean %s)",s,real);
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