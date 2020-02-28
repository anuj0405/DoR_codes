#include<iostream>
#include<limits.h>

using namespace std; 
void insert(int arr[],int size)
{
    int data,position,n=0;
 
	cout<<"\nEnter key data to insert";
	cin>>data;
 
	position = data%size;
 
	while(arr[position]!= INT_MIN) 
	{ 
		if(arr[position]== INT_MAX)//Assign INT_MAX to check if array is full or not
	            break;
		position = (position+1)%size;
		n++;
		if(n==size)
		    break;    
	}
 
	if(n==size)
        cout<<"\nHash table was full of datas\tNo Place to insert this data";
	else
        arr[position] = data;
}
 
void delet(int arr[],int size)
{
	int data,n=0,position;
 
	cout<<"\nEnter data to delete";
	cin>>data;
 
	position=data%size;
 
	while(n++ != size){
		if(arr[position]==INT_MIN){
			cout<<"\ndata not found in hash table";
			break;
		}
		else if(arr[position]==data){
			arr[position]=INT_MAX;
			cout<<"\ndata deleted";
			break;
		}
		else{
			position = (position+1) % size;
		}
	}
	if(--n==size)
        cout<<"\ndata not found in hash table";
}
 
void search(int arr[],int size)
{
	int data,position,n=0;
 
	cout<<"\nEnter data you want to search";
	cin>>data;
 
	position = data%size;
 
	while(n++ != size){
		if(arr[position]==data){
			cout<<"\nData found at index"<<position;
			break;
		}
		else
            if(arr[position]==INT_MAX ||arr[position]!=INT_MIN)
                position = (position+1) %size;
	}
	if(--n==size) 
		cout<<"\nData not found in hash table";
}
 
void display(int arr[],int size){
	int i;
 
	cout<<"\nIndex \t Value \n";
 
	for(i=0;i<size;i++)
	{
		if(arr[i]==INT_MAX)
		{	
			cout<<i<<"\t"<<"Null"<<endl;
		}        				
		else
		{
			cout<<i<<"\t"<<arr[i]<<endl;
		}	
	}
}
int main()
{
	int size,i,choice;
 
	cout<<"\nEnter size of hash table: ";
	cin>>size;
 
	int arr[size];
 
 
	for(i=0;i<size;i++)
        	arr[i]=INT_MIN; //Assigning INT_MIN indicates that cell is empty
 
	do{
		cout<<"\nEnter your choice ";
		cout<<"\n 1-> Insert\n 2-> Delete\n 3-> Display\n 4-> Searching\n 5-> Exit";
		cout<<"\nEnter your choice: ";
		cin>>choice;
 
		switch(choice){
			case 1:
				insert(arr,size);
				break;
			case 2:
				delet(arr,size);
				break;
			case 3:
				display(arr,size);
				break;
			case 4:
				search(arr,size);
				break;
			case 5: 
				exit(0);
			default:
				cout<<"\nEnter correct choice";
				break;
		}
	}while(choice);
 
	return 0;
}
