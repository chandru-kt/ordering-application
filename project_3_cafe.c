#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

int FRONT = -1,REAR = -1,SIZE = 10;
int q_data[10][2];
int enqueue(int a,int b)
{
	if (REAR == SIZE - 1)
       printf("Order Overflow \n");
    else
    {
        if (FRONT == - 1)
        	FRONT = 0;
        REAR = REAR + 1;
		q_data[REAR][0] = a;
		q_data[REAR][1] = b;
	}
}
void empty()
{
	FRONT = -1;
	REAR = -1;
}
int dequeue()
{
	if (FRONT == - 1 || FRONT > REAR)
    {
        printf("Order Underflow \n");
        return ;
    }
    else
    {
        printf("Your First Order deleted from the List\n\n");
        FRONT = FRONT + 1;
	}
}
void show()
{
	if (FRONT == -1)
        printf("Empty List\n");
    else
    {
    	int i;
        printf("Your Orders: \n");
        for (i = FRONT; i <= REAR; i++)
            printf("Food ID : %d\nQuantity : %d\n\n", q_data[i][0],q_data[i][1]);
        printf("\n");
    }
}

int assign_queue(int r,int i)
{
	if (FRONT == - 1)
        return 0;
    else
    {
        	return q_data[r][i];
    }
}

struct insert_list
{
	int s_no;
	char name[10];
	float price;
};
struct order_dish
{
	int total_order;
    int a[10][2];
    float total_amount;
    char name[25];
    char Date[20];
    char Time[10];
};
struct admin_data
{
	int total_customer;
	float total_income;
};
void insert()
{
	struct insert_list *l;
	FILE *fp;
	int n=1;
	l=(struct insert_list*)calloc(n, sizeof(struct insert_list));
	fp=fopen("menulist.txt","a");
    printf("Enter the index number: ");
    scanf("%d",&l->s_no);
    printf("Enter the item name: ");
    scanf("%s",&l->name);
    printf("Enter the price: ");
    scanf("%f",&l->price);
    fwrite(l, sizeof(struct insert_list),1,fp);
fclose(fp);
	 
}

void order()
{
	struct order_dish *o;
	FILE *fp,*fp1;
	o=malloc(sizeof(struct order_dish));
	int n,j=0,i=0,id,quan,ord=0;
	do{
            printf("Pleaze enter the FOOD ID NUMBER OF ITEM AND ITS QUENTITY:");
                scanf("%d %d",&id,&quan);
            j++;
            enqueue(id,quan);
            if(ord >= 2)
            {
            	while(1)
            	{
	            	printf("1.Do you want More item\n2.Cancel First Order\n3.Show Previous Orders\n0.Close Order\n");
	            	scanf("%d",&n);
	            	if(n == 2)
	            	{
	            		dequeue();
	            		ord--;
	            		j--;
	            	}
	            	if(n == 3)
	            	{
	            		show();
	            		ord++;
	            	}
	            	if(n == 1 || n == 0)
	            	{
	            		break;
	            		ord++;
	            	}
            	}
        	}else
        	{
        		printf("you want More item\n1.yes\n0.no\n");
            	scanf("%d",&n);
            	ord++;
			}
    }while(n!=0);
    int r,k=0;
    for(r=FRONT;r<=REAR;r++)
    {
    	for(i=0;i<2;i++)
        	o->a[k][i] = assign_queue(r,i);
        k++;
    }
    empty();
    printf("Enter your Name : ");
    scanf("%s",&o->name);
    fflush(stdin);
    printf("Enter Today's Date : ");
    scanf("%s",&o->Date);
    fflush(stdin);
    printf("Enter Today's Time : ");
    scanf("%s",&o->Time);
    k=0;
    printf("\n-------------------------------------------------------------------------------------------------------\n");
    printf("                                          BILL                             \n");

    printf("Name:-%s\n",o->name);
    printf("Date:-%s\n",o->Date);
    printf("Time:-%s\n",o->Time);
    o->total_amount = 0;
    struct insert_list *p;
    char g_d_name[10];
	float g_d_price;
	fp1 = fopen("order_database.txt","a");
	o->total_order = (j-1);
    for(k=0;k<j;k++)
    {
    	fp = fopen("menulist.txt","r");
    	p=malloc(sizeof(struct insert_list));
		while(fread(p,sizeof(struct insert_list),1,fp))
		{
		    if(p->s_no == o->a[k][0])
		    {
		    	strcpy(g_d_name,p->name);
		    	g_d_price = p->price;
		    	break;
			}
		}
		fclose(fp);
        printf("-------------------------------------------------------------------------------------------------------\n");
        float rr = (o->a[k][1]*g_d_price);
        printf("%d\t%s\t%d\t\t%f\n",o->a[k][0],g_d_name,o->a[k][1],rr);
        o->total_amount += rr;
        free(p);
    }
    

    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("\nTotal Payble amount is:-\t\t%f\n",o->total_amount);
    printf("-------------------------------------------------------------------------------------------------------\n");
    fwrite(o, sizeof(struct order_dish),1,fp1);
	fclose(fp1);
}
void display_income()
{
	struct order_dish *l1;
	l1=malloc(sizeof(struct order_dish));
	FILE *fp;
	fp=fopen("order_database.txt","r");
	float t_income=0;
	while(fread(l1,sizeof(struct order_dish),1,fp))
	{
		t_income+=(l1->total_amount);
	}
	printf("Total Income : %.2f\n\n",t_income);
fclose(fp);
}

void display_t_customer()
{
	struct order_dish *l1;
	l1=malloc(sizeof(struct order_dish));
	FILE *fp;
	fp=fopen("order_database.txt","r");
	int t_cus=0;
	while(fread(l1,sizeof(struct order_dish),1,fp))
	{
		t_cus+=1;
	}
	printf("Total Customer : %d\n\n",t_cus);
fclose(fp);
}
void display_customer()
{
	struct order_dish *l1;
	l1=malloc(sizeof(struct order_dish));
	FILE *fp;
	fp=fopen("order_database.txt","r");
	while(fread(l1,sizeof(struct order_dish),1,fp))
	{
		int i;
	    printf("Customer Name : %s\nOrder Date : %s\nOrder Time : %s\n",l1->name,l1->Date,l1->Time);
	    for(i=0;i<=l1->total_order;i++)
	    {
	    	printf("Dish Id : %d\tQuantity : %d\n",l1->a[i][0],l1->a[i][1]);
		}
		printf("Total Amount : %.2f\n\n",l1->total_amount);
	}
fclose(fp);
}
void display()
{
	struct insert_list *l1;
	l1=malloc(sizeof(struct insert_list));
	FILE *fp;
	fp=fopen("menulist.txt","r");
	printf("                                                -------------                                            \n");
    printf("-----------------------------------------------------MENU-------------------------------------------------\n");
    printf("                                                -------------                                            \n");
    printf("INDEX   ITEM NAME    PRICE   \n");
	while(fread(l1,sizeof(struct insert_list),1,fp))
	{
	    printf("%d\t%s\t%f\n",l1->s_no,l1->name,l1->price);
	
	}
fclose(fp);
}
int login()
{

    char username[20];
    char userpwd[11];
    int i;

    printf("Enter your User Name : ");
    scanf("%s",username);

    printf("Enter your password : ");
    for(i=0;i<3;i++)
    {
        userpwd[i]=getch();
        printf("*");
    }
    userpwd[i]='\0';


    if(!strcmp(username,"admin") && !strcmp(userpwd,"123"))
    {
        printf("\n\nLogged In Successful\n");
        return 1;
    }

    else
    {
        printf("\n\nIncorrect username or password\n");
        return 0;
    }
}
void main()
{
	int choice;
	do{
		system("cls");
		printf("\t\t\t\t\t\t\tCAS CAFETIERA\n\n");
        printf("\n-------------------------------------------------------------------------------");
        printf("\n1....FOOD PART");
        printf("\n2....ADMIN PANEL");
        printf("\n3....EXIT");

        printf("\nEnter your choice:");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                printf("");
                int ex;

                do{
                    printf("1.       FOOD LIST\n2.       ORDER\n");
                    int n;
                    scanf("%d",&n);

                    switch(n)
                    {
                        case 1: display();
                                break;
                        case 2: 
							order();
                            break;
                                
                    }

                    printf("1.FOOD PART\n2.MAIN MENU\n");
					scanf("%d",&ex);
				}while(ex==1);
            break;

            case 2:
                printf("\n");
                int k=login();
                int e;
                if(k==1){

                do{
                    printf("-------------------------------------------------------------------------------------------------------\n");
                    printf("1.     ADD NEW DISH\n");
                    printf("2.     TODAY'S  TOTAL INCOME\n");
                    printf("3.     TODAY TOTAL NO OF CUSTOMER\n");
                    printf("4.     ORDER HISTORY\n");
                    printf("5      LIST OF ITEM\n");
                    printf("\n------------------------------------------------------------------------------------------------------\n");

                    int ch;
                    scanf("%d",&ch);
                    switch(ch)
                    {
                        case 1:
                        	insert();
                            printf("-------------------------------------------------------------------------------------------------------\n");
					        printf("                 NEW DISH IS ADDED SUCESSFULLY.......\n");
                            printf("-------------------------------------------------------------------------------------------------------\n");
					        printf("\n");
                        	break;

                        case 2:
                            printf("-------------------------------------------------------------------------------------------------------\n");
                            printf("        TODAY'S  TOTAL INCOME IS:\n");
                            printf("-------------------------------------------------------------------------------------------------------\n");
                        	display_income();
							break;

                        case 3:
                            printf("-------------------------------------------------------------------------------------------------------\n");
					        printf("        TODAY TOTAL NO OF CUSTOMER VISITED\n");
                            printf("-------------------------------------------------------------------------------------------------------\n");
                        	display_t_customer();
							break;

                        case 4:
                            printf("-------------------------------------------------------------------------------------------------------\n");
					        printf("	                ORDER SUMMARY\n");
					        printf("-------------------------------------------------------------------------------------------------------\n");
                            printf("\n");
                            display_customer();
                        	break;

                        case 5:
                            printf("\n");
                            display();
                            break;

					}

					printf("1.ADMIN PANEL\n2.MAIN MENU\n");
					scanf("%d",&e);

				}while(e==1);
			}
			break;
        }

    }while(choice!=3);

}
