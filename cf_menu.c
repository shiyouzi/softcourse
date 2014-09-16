/*******************************************************************************
/* FILE NAME               : cf_menu.c
/* PRINCIPAL AUTHOR        : chenfeng
/* SUBSYSTEM NAME          : menu
/* MODULE NAME             : menu
/* LANGUAGE                : C
/* TARGET ENVIRONMENT      : ANY
/* DATE OF FIRST RELEASE   : 2014/09/15
/* DESCRIPTION             : This is a menu
/*******************************************************************************

/*
 * Revision log;
 *
 * Created by chenfeng,2014/09/15
 *
 */



#include <stdio.h>
#include <stdlib.h>

#define DESC_LEN 1024
#define CMD_MAX_LEN 1024

typedef struct DataNode
{
	char* cmd;
	char* desc;
	int (*handler)();
	struct DataNode *next;
}tDataNode;

tDataNode* head = NULL;
tDataNode* NewOneNode();
int AddLinkTableNode(tDataNode* newNode);
int InitMenuData();
int ShowAllCmd();
int Help();
int Quit();

main()
{
	InitMenuData(); 
   /* cmd line begins */
    while(1)
    {
        char cmd[CMD_MAX_LEN];
        printf("Input a cmd number > ");
        scanf("%s", cmd);
        tDataNode* p = head;
	    while(p!=NULL)
		{
	        if(!strcmp(p->cmd,cmd))
	            break;
	        p=p->next;
		}
        if( p == NULL)
        {
            printf("This is a wrong cmd!\n ");
            continue;
        }
        printf("%s - %s\n", p->cmd, p->desc); 
        if(p->handler != NULL) 
        { 
            p->handler();
        }
   
    }
}

tDataNode* NewOneNode()
{
	return (tDataNode*)malloc(sizeof(tDataNode));
}

int AddLinkTableNode(tDataNode* newNode)
{
	if(newNode == NULL)
		return 0;
	if(head == NULL)
		head = newNode;
	else
	{
		newNode->next = head->next;
		head->next = newNode;
	}
	return 1;
}

int InitMenuData()
{
    tDataNode* pNode = NewOneNode();
    pNode->cmd = "help";
    pNode->desc = "this is help cmd";
    pNode->handler = Help;
	pNode->next = NULL;
    AddLinkTableNode(pNode);
	
    pNode = NewOneNode();
    pNode->cmd = "version";
    pNode->desc = "Menu Program V1.0";
    pNode->handler = NULL; 
	pNode->next = NULL;
    AddLinkTableNode(pNode);
	
    pNode = NewOneNode();
    pNode->cmd = "quit";
    pNode->desc = "Quit from Menu Program V1.0";
    pNode->handler = Quit; 
	pNode->next = NULL;
    AddLinkTableNode(pNode);
 
    return 0; 
}

/* show all cmd in listlist */
int ShowAllCmd()
{
    tDataNode* pNode = head->next;
    while(pNode != NULL)
    {
        printf("%s - %s\n", pNode->cmd, pNode->desc);
        pNode = pNode -> next;
    }
    return 0;
}


int Help()
{
    ShowAllCmd();
    return 0; 
}

int Quit()
{
    exit(0);
}

