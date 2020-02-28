#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#define MAX_LEVEL 6
const float P = 0.5;
using namespace std;

struct Node
{
    int value;
    Node **Forword;
    Node(int level, int &value)
    {
        Forword = new Node * [level + 1];
        memset(Forword, 0, sizeof(Node*) * (level + 1));
        this->value = value; 
    }
    ~Node()
    {
        delete [] Forword;        
    } 
};
class s_list
{
    public:
    Node *header;
    int value;
    int level;
    s_list() 
    {
        header = new Node(MAX_LEVEL, value);
        level = 0;
    }
    ~s_list() 
    {
        delete header;
    }
    void display();
    bool search(int &);
    void insert_element(int &);
    void delete_element(int &);        
};

 
float frand() 
{
    return (float) rand() / RAND_MAX;
}
int random_level() 
{
    static bool first = true;
    if (first) 
    {
        srand((unsigned)time(NULL));
        first = false;
    }
    int lvl = (int)(log(frand()) / log(1.-P));
    return lvl < MAX_LEVEL ? lvl : MAX_LEVEL;
}
void s_list::insert_element(int &value) 
{
    Node *x = header;	
    Node *update[MAX_LEVEL + 1];
    memset(update, 0, sizeof(Node*) * (MAX_LEVEL + 1));
    for (int i = level;i >= 0;i--) 
    {
        while (x->Forword[i] != NULL && x->Forword[i]->value < value) 
        {
            x = x->Forword[i];
        }
        update[i] = x; 
    }
    x = x->Forword[0];
    if (x == NULL || x->value != value) 
    {        
        int lvl = random_level();
        if (lvl > level) 
        {
            for (int i = level + 1;i <= lvl;i++) 
            {
                update[i] = header;
            }
            level = lvl;
        }
        x = new Node(lvl, value);
        for (int i = 0;i <= lvl;i++) 
        {
            x->Forword[i] = update[i]->Forword[i];
            update[i]->Forword[i] = x;
        }
    }
}
 
void s_list::delete_element(int &value) 
{
    Node *x = header;	
    Node *update[MAX_LEVEL + 1];
    memset (update, 0, sizeof(Node*) * (MAX_LEVEL + 1));
    for (int i = level;i >= 0;i--) 
    {
        while (x->Forword[i] != NULL && x->Forword[i]->value < value)
        {
            x = x->Forword[i];
        }
        update[i] = x; 
    }
    x = x->Forword[0];
    if (x->value == value) 
    {
        for (int i = 0;i <= level;i++) 
        {
            if (update[i]->Forword[i] != x)
                break;
            update[i]->Forword[i] = x->Forword[i];
        }
        delete x;
        while (level > 0 && header->Forword[level] == NULL) 
        {
            level--;
        }
    }
}
 
void s_list::display() 
{
    const Node *x = header->Forword[0];
    while (x != NULL) 
    {
        cout << x->value;
        x = x->Forword[0];
        if (x != NULL)
            cout << " - ";
    }
    cout <<endl;
}
 
bool s_list::search(int &s_value) 
{
    Node *x = header;
    for (int i = level;i >= 0;i--) 
    {
        while (x->Forword[i] != NULL && x->Forword[i]->value < s_value)
        {
            x = x->Forword[i];
        }
    }
    x = x->Forword[0];
    return x != NULL && x->value == s_value;
}

int main() 
{
    s_list a;
    int choice, n,e=0;
    while (1)
    {
        cout<<"\n1.Insert Element";
        cout<<"\n2.Delete Element";
        cout<<"\n3.Search Element";
        cout<<"\n4.Display List ";
        cout<<"\n5.Exit ";
        cout<<"\nEnter your choice : ";
        cin>>choice;
        switch(choice)
        {
        case 1:
             cout<<"\nEnter the no of element to be inserted: ";
             cin>>n;
	     for(int i=0;i<n;i++)
	     {
		cout<<"\nEnter the element to be inserted: ";
             	cin>>e;	
             	a.insert_element(e);
             }
	     break;
        case 2:
             cout<<"\nEnter the element to be deleted: ";
             cin>>n;
             if(!a.search(n))
             {
                 cout<<"\nElement not found"<<endl;
                 break;
             }
             a.delete_element(n);
             if(!a.search(n))
                 cout<<"\nElement Deleted"<<endl;
             break;
        case 3:
             cout<<"\nEnter the element to be searched: ";
             cin>>n; 
             if(a.search(n))
                 cout<<"\nElement "<<n<<" is in the list"<<endl;
             else
                 cout<<"\nElement not found"<<endl;
        case 4:
             cout<<"\nThe List is: ";
             a.display();
             break;
        case 5:
             exit(1);
             break;
        }
    }
    return 0;
}

