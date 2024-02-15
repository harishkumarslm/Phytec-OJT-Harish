#include<stdio.h>
int harish=0, kalai=0, nandha=0, param=0;
void electionResult()
{
    int wonByVote;
    if (harish > kalai && harish > nandha && harish > param)
    {
        printf("\n***harish won the election***\n\n");
        printf("Total vote of harish : %d\n",harish);
        wonByVote=harish-kalai;
        printf("harish won by %d votes to kalai\n",wonByVote);
        wonByVote=harish-nandha;
        printf("harish won by %d votes to nandha\n",wonByVote);
        wonByVote=harish-param;
        printf("harish won by %d votes to param\n",wonByVote);
    }
    else if (kalai > nandha && kalai > param)
    {
        printf("\n***kalai won the election***\n\n");
        printf("Total vote of kalai : %d\n",kalai);
        wonByVote=kalai-harish;
        printf("kalai won by %d votes to harish\n",wonByVote);
        wonByVote=kalai-nandha;
        printf("kalai won by %d votes to nandha\n",wonByVote);
        wonByVote=kalai-param;
        printf("kalai won by %d votes to param\n",wonByVote);
    }
    else if (nandha > param)
    {
        printf("\n***nandha won the election***\n\n");
        printf("Total vote of nandha : %d\n",nandha);
        wonByVote=nandha-kalai;
        printf("nandha won by %d votes to kalai\n",wonByVote);
        wonByVote=nandha-harish;
        printf("nandha won by %d votes to harish\n",wonByVote);
        wonByVote=nandha-param;
        printf("nandha won by %d votes to param\n",wonByVote);
    }
    else if(harish == kalai && harish == nandha && harish == param)
    {
        printf("\nNo one won the election\n\n");
        printf("            harish---kalai---nandha---param\n");
        printf("Total Vote   %d       %d        %d     %d\n",harish,kalai,nandha,param);
    }
    else
    {
        printf("\n***param won the election***\n\n");
        printf("Total vote of param : %d\n",param);
        wonByVote=param-kalai;
        printf("param won by %d votes to kalai\n",wonByVote);
        wonByVote=param-nandha;
        printf("param won by %d votes to nandha\n",wonByVote);
        wonByVote=param-harish;
        printf("param won by %d votes to harish\n",wonByVote);
    }
}
void calculateVote(int vote)
{
    switch (vote)
    {
    case 1:
        harish+=1;
        break;
    case 2:
        kalai+=1;
        break;
    case 3:
        nandha+=1;
        break;
    case 4:
        param+=1;
        break;
    }
}
void main()
{
    int choose;
    
    
        printf("\n*********Welcome to the simple voting system project*********\n\n");
        printf("                         MP election                        \n\n");
        printf("*************************************************************\n");
        printf("|           1.harish             |          2.kalai         |\n");
        printf("*************************************************************\n");
        printf("|           3.APP             |          4.param              |\n");
        printf("*************************************************************\n\n");
    do
    {    
        printf("Press 1 to vote harish(001)\n");
        printf("Press 2 to vote kalai(002)\n");
        printf("Press 3 to vote nandha(003)\n");
        printf("Press 4 to vote param(004)\n");
        printf("Press 5 to show election result\n");
        printf("Please choose : ");
        scanf("%d", &choose);
        if (choose==5)
        {
            electionResult();
        }else
        {
            calculateVote(choose);            
        } 
        printf("\n");
    } while (choose != 5);
}

