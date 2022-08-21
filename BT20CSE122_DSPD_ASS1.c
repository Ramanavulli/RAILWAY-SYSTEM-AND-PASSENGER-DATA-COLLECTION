#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node																//node of passenger data!!!
{
	// data;
	char name[10];
	int passenger_id;
	char boarding_train[10];
	char boarding_station[10];
	char travelling_class[10];		//(sleeper,3AC,2AC,1AC)
	char destination_station[10];
	int train_id;
	int bogie_no; //NO.OF.BOGIES assumed to be 10
	int seat_no;	//seats assumed to be 50
	char date_of_travel[10];
	struct node* next;
};




struct train_node									// node of train data
{
	int train_id;
	int count;
	struct train_node* next;
};




struct node *start=NULL;
struct node* sorted = NULL;
struct train_node* lptr=NULL;


void display();
int search(int train,int bogie,int seat);

//input of passengers
void insert()
{
        printf("NO .OF passengers added one time:");
        int n;
        scanf("%d",&n);
        while(n!=0)
    	{
    		struct node *temp;
    		struct train_node* t_temp;
	        temp=(struct node *)malloc(sizeof(struct node));
	        if(temp==NULL)
	        {
	                printf("\n\t***\t reservation failed.\t***\t\n");
	                return;
	        }
	        printf("\nEnter the data values for the node:\t" );
	        printf("\nname\tpass_id \tdes_station\ttrain_id\n");
	        scanf("%s",&temp->name);
	        scanf("%d",&temp->passenger_id);
	        scanf("%s",&temp->destination_station);
	        scanf("%d",&temp->train_id);
	        t_temp->train_id=temp->train_id;		//stores data of trainid in train node also
	        printf("\nenter the bogie no in between 1-10  :");
	        scanf("%d",&temp->bogie_no);
	        printf("\nenter the bogie no in between 1-50   :");
	        scanf("%d",&temp->seat_no);
	        int s;
		   s=search(temp->train_id,temp->bogie_no,temp->seat_no);
	       if(s==1)
	        {
	        	printf("boige and seatno entered is booked alredy enter another value");
	        	display();
	        	scanf("%d",&temp->seat_no);
	    	}
	        
	        printf("BOARDING_TRAIN	BOARD_STATION	\n");
	      	scanf("%s",&temp->boarding_train);
	        scanf("%s",&temp->boarding_station);
	        printf("\nselect class:(sleeper,3AC,2AC,1AC)");
	        scanf("%s",&temp->travelling_class);
	        printf("Enter the travel date:");
	        scanf("%s",temp->date_of_travel);
	        printf("\n\t***\tThe Reservation done successfully\t***\n ");
	        temp->next =NULL;
	        if(start==NULL)
	        {
	                start=temp;
	        }
	        else
	        {
	                temp->next=start;
	                start=temp;
	        }
	        
	        n--;
		}
}


//Deletes an element if the passenger cancels the reservation.
void Delete()
{
    struct node * temp1 = start;
    struct node * temp2 = start; 
    int passenger_id;
    printf("Enter passenger id to delete all records of that particular passenger id.: ");
    scanf("%d", &passenger_id);
    while(temp1!=NULL){
        
        if(temp1->passenger_id==passenger_id){
            
            printf("Record with passenger_id %d Found !!!\n ", passenger_id);
            
            if(temp1==temp2){
                // this condition will run if
                // the record that we need to delete is the first node
                // of the linked list
                start = start->next;
                free(temp1);
            }
            else{
                // temp1 is the node we need to delete
                // temp2 is the node previous to temp1
                temp2->next = temp1->next;
                free(temp1); 
            }
            
            printf("\n the  Reservation cancelled successfully!!!\n");
            return;
            
        }
        temp2 = temp1;
        temp1 = temp1->next;
        
    }
    printf("passenger with passenger_id %d is not found !!!\n   Reservation Cancellation failed.\n", passenger_id);
    
}



int search(int train,int bogie,int seat)
{
	
	struct node* temp = start;
    while(temp!=NULL)
	{
		
        if((temp->bogie_no==bogie)&&(temp->seat_no==seat)&&(temp->train_id==train))
		{
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}


//display function
void display()
{
        struct node *ptr;
        if(start==NULL)
        {
                printf("\nList is empty\n");
                return;
        }
        else
        {
                ptr=start;
                printf("\nThe List elements are:\n");
                while(ptr!=NULL)
                {
                		int n;
                		printf("%d.)",n+1);
                		n++;
						printf("%s\t",ptr->name);
                        printf("%d\t",ptr->passenger_id);
                        printf("%s\t",ptr->destination_station);
	       				printf("%d\t",ptr->train_id);
	       				printf("bogie:%d\t",ptr->bogie_no);
	       				printf("seatno:%d\t",ptr->seat_no);
	       				printf("date of travel:%s",ptr->date_of_travel);
	       				printf("\n");
	       				printf("boarding_train:%s\t",ptr->boarding_train);
	        			printf("boarding_station:%s\t",ptr->boarding_station);
	        			printf("travelling_class:%s\t\n",ptr->travelling_class);
                        ptr=ptr->next ;
                }
        }
}

 





//Gives the list of passengers having the same destination station and same train id
//get_List_Destination
void get_List_Destination()
{
	printf("Enter the destination station and  train id to get the list:");
	char des_station[10];
	int t_id;
	scanf("%s",&des_station);
	scanf("%d",&t_id);
	int flag=0;
	
	struct node* temp = start;
    while(temp!=NULL)
	{
        if((strcmp(temp->destination_station,des_station))==0&&(temp->train_id==t_id))
		{
            printf("\npassenger name: %s\t", temp->name);
            printf("passenger id: %d\t", temp->passenger_id);
            printf("destination_station:%s \t",temp->destination_station);
	       	printf("train_id:%d\n",temp->train_id);
            flag=1;
            
        }
        temp = temp->next;
    }
    if(flag==0)
    {
    	printf("train with destination station and  train id  %d is not found !!!\n", t_id);
	}
}




//SortByTravelDate
void SortByTravelDate(struct node* temp)
{
	int p_id;
	printf("Enter the passenger_id to search the data: ");
	scanf("%d",&p_id);
	int flag=0;
	temp = start;
	printf("THE LIST OF DESTINATION STATIONS ARE:\n");
	while(temp!=NULL)
	{
		if(temp->passenger_id==p_id)
		{
			printf("\n destination_station:%s \t",temp->destination_station);
			printf("travel date:%s\n",temp->date_of_travel);
			flag=1;
		}
		temp=temp->next;
	}
	if(flag==0)
	{
		printf("Passenger with passenger_id %d is not found!!\n",p_id);
	}
}




//sort_train_id
void sort_train_id(struct node* newnode)
{
    
    if (sorted == NULL || sorted->train_id >= newnode->train_id) {
        newnode->next = sorted;
        sorted = newnode;
    }
    else {
        struct node* current = sorted;
        while (current->next != NULL&& current->next->train_id< newnode->train_id) 
		{
            current = current->next;
        }
        newnode->next = current->next;
        current->next = newnode;
    }
}



//Sort_Trains
void Sort_Trains()
{
	struct node* current = start;
 
    while (current != NULL) {
 
        // Store next for next iteration
        struct node* next = current->next;
 
        // insert current in sorted linked list
        sort_train_id(current);
        int train_id=current->train_id;
 		
        // Update current
        current = next;
    }
    // Update start to point to sorted linked list
    start = sorted;
    printf("SORTED");
    display();
}

//passenger_count
void passenger_count()			//stores the passenger count of particular train
{
	struct node* temp=start;
	struct train_node* t_temp=lptr;
	int count=0;
	while(temp!=NULL)
	{
		
		printf("%d",t_temp->train_id);
		while(t_temp->train_id==temp->train_id)
		{
			count++;
			temp=temp->next;
		}
		printf("%d",count);
		t_temp->count =count;
		t_temp=t_temp->next;
	}
}



//Promote_Passengers
void Promote_Passengers(struct node* list_ptr)
{

	int train,seatno;
	char date[10],dest[10];
	printf("Enter – Train id and date of travel\t:");
	scanf("%d %s",&train,&date);
	printf("\n enter the  destination:");
	scanf("%s",&dest);
	printf("\n Enter the seat no");
	scanf("%d",&seatno);
	struct node *temp =start;
    struct node *temp1;
    while(temp=NULL)
    {
        temp1=temp->next;
        while(temp1!=NULL)
        {
            if(temp->train_id==temp1->train_id && strcmp(temp->date_of_travel,temp1->date_of_travel)==0)
            {
                if(strcmp(temp->travelling_class,"Sleeper")==0 && strcmp(temp->destination_station,dest)==0)
                {
                    if(temp->seat_no<=seatno && temp1->seat_no<=seatno)
                    {
                        strcpy(temp->travelling_class,"3AC");
                        temp->seat_no=temp1->seat_no;
                        temp->bogie_no=temp1->bogie_no;
                    }
                }
                else if(strcmp(temp->travelling_class,"3AC")==0 && strcmp(temp->destination_station,dest)==0)
                {
                    if(temp->seat_no<=seatno && temp1->seat_no<=seatno)
                    {
                        strcpy(temp->travelling_class,"2AC");
                        temp->seat_no=temp1->seat_no;
                        temp->bogie_no=temp1->bogie_no;
                    }
                }
                else if(strcmp(temp->travelling_class,"2AC")==0 && strcmp(temp->destination_station,dest)==0)
                {
                    if(temp->seat_no<=seatno && temp1->seat_no<=seatno)
                    {
                        strcpy(temp->travelling_class,"1AC");
                        temp->seat_no=temp1->seat_no;
                        temp->bogie_no=temp1->bogie_no;
                    }
                }
                
            }
            temp1=temp1->next;
        }
        temp=temp->next;
    }
    
    display();
}



int main()     
{
		struct node* list_ptr;
		list_ptr=start;
        int choice;
        while(1){
               
                printf("\n                Choices                            \n");
                printf("\n 1.Insert     \n");
                printf("\n 2.Delete    \n");
                printf("\n 3. display   \n");
               printf("\n 4.get_List_Destination\n");
                printf("\n 5.SortByTravelDate\n");
                printf("\n 6.Sort_Trains\n");
                printf("\n 7.PromotePassengers     \n");
                printf("\n 8.Exit       \n");
                printf("\n--------------------------------------\n");
                printf("Enter your choice:\t");
                scanf("%d",&choice);
                
                switch(choice)
                {
                        
                        case 1: 
                                        insert();
                                        break;
                        case 2:
                                        Delete();
                                        break;
                        case 3:
                                        display();
                                        break;
                        case 4:
                                      get_List_Destination();
                                        break;
                        case 5:
                                      SortByTravelDate(start);
                                        break;
                        
                        
                        case 6:
                                      Sort_Trains();
                                        break;
                        case 7:
                        			Promote_Passengers(list_ptr);
                        				break;
                        case 8:
                                       exit(0);
                                        break;
                             
                        default:
                                        printf("\n Wrong Choice:\n");
                                        break;
                }
        }
        return 0;
}
