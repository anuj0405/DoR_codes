#include<bits/stdc++.h>
using namespace std;
#define MAX 30
int nop;
struct block
{
    int tNodes;
    block *parentblock;
    int value[MAX];
    block *childblock[MAX];
    block(){
        tNodes = 0;
        parentblock = NULL;
        for(int i=0; i<MAX; i++){
            value[i] = INT_MAX;
            childblock[i] = NULL;
        }
    }
};
block *rootblock = new block();
void split_l(block *curblock)
{
    int x, i, j;

    if(nop%2)
        x = (nop+1)/2;
    else x = nop/2;

    block *rightblock = new block();

    curblock->tNodes = x;
    rightblock->tNodes = nop-x;
    rightblock->parentblock = curblock->parentblock;

    for(i=x, j=0; i<nop; i++, j++)
    {
        rightblock->value[j] = curblock->value[i];
        curblock->value[i] = INT_MAX;
    }
    int val = rightblock->value[0];

    if(curblock->parentblock==NULL)
    {
        block *parentblock = new block();
        parentblock->parentblock = NULL;
        parentblock->tNodes=1;
        parentblock->value[0] = val;
        parentblock->childblock[0] = curblock;
        parentblock->childblock[1] = rightblock;
        curblock->parentblock = rightblock->parentblock = parentblock;
        rootblock = parentblock;
        return;
    }
    else
    {
        curblock = curblock->parentblock;

        block *newChildblock = new block();
        newChildblock = rightblock;


        for(i=0; i<=curblock->tNodes; i++)
	{
            if(val < curblock->value[i])
	    {
                swap(curblock->value[i], val);
            }
        }

        curblock->tNodes++;

        for(i=0; i<curblock->tNodes; i++)
	{
            if(newChildblock->value[0] < curblock->childblock[i]->value[0]){
                swap(curblock->childblock[i], newChildblock);
            }
        }
        curblock->childblock[i] = newChildblock;

        for(i=0;curblock->childblock[i]!=NULL;i++)
	{
            curblock->childblock[i]->parentblock = curblock;
        }
    }

}
void split_nonl(block *curblock)
{
    int x, i, j;
    x = nop/2;
    block *rightblock = new block();
    curblock->tNodes = x;
    rightblock->tNodes = nop-x-1;
    rightblock->parentblock = curblock->parentblock;

    for(i=x, j=0; i<=nop; i++, j++){
        rightblock->value[j] = curblock->value[i];
        rightblock->childblock[j] = curblock->childblock[i];
        curblock->value[i] = INT_MAX;
        if(i!=x)curblock->childblock[i] = NULL;
    }

    int val = rightblock->value[0];
    memcpy(&rightblock->value, &rightblock->value[1], sizeof(int)*(rightblock->tNodes+1));
    memcpy(&rightblock->childblock, &rightblock->childblock[1], sizeof(rootblock)*(rightblock->tNodes+1));


    for(i=0;curblock->childblock[i]!=NULL;i++){
        curblock->childblock[i]->parentblock = curblock;
    }
    for(i=0;rightblock->childblock[i]!=NULL;i++){
        rightblock->childblock[i]->parentblock = rightblock;
    }

    if(curblock->parentblock==NULL){
        block *parentblock = new block();
        parentblock->parentblock = NULL;
        parentblock->tNodes=1;
        parentblock->value[0] = val;
        parentblock->childblock[0] = curblock;
        parentblock->childblock[1] = rightblock;

        curblock->parentblock = rightblock->parentblock = parentblock;

        rootblock = parentblock;
        return;
    }
    else{
	curblock = curblock->parentblock;

        block *newChildblock = new block();
        newChildblock = rightblock;

        for(i=0; i<=curblock->tNodes; i++){
            if(val < curblock->value[i]){
                swap(curblock->value[i], val);
            }
        }
        curblock->tNodes++;

        for(i=0; i<curblock->tNodes; i++){
            if(newChildblock->value[0] < curblock->childblock[i]->value[0]){
                swap(curblock->childblock[i], newChildblock);
            }
        }
        curblock->childblock[i] = newChildblock;
         for(i=0;curblock->childblock[i]!=NULL;i++){
            curblock->childblock[i]->parentblock = curblock;
        }
    }

}

void insertNode(block *curblock, int val)
{

    for(int i=0; i<=curblock->tNodes; i++){
        if(val < curblock->value[i] && curblock->childblock[i]!=NULL){
            insertNode(curblock->childblock[i], val);
            if(curblock->tNodes==nop)
                split_nonl(curblock);
            return;
        }
        else if(val < curblock->value[i] && curblock->childblock[i]==NULL){
            swap(curblock->value[i], val);
            if(i==curblock->tNodes){
                    curblock->tNodes++;
                    break;
            }
        }
    }

    if(curblock->tNodes==nop){

            split_l(curblock);
    }
}

/*
void redistributeblock(block *leftblock, block *rightblock, bool isLeaf, int posOfLeftblock, int whichOneisCurblock){
    int PrevRightFirstVal = rightblock->value[0];

    if(whichOneisCurblock==0){ 
        if(!isLeaf){
            leftblock->value[leftblock->tNodes] = leftblock->parentblock->value[posOfLeftblock];
            leftblock->childblock[leftblock->tNodes+1] = rightblock->childblock[0];
            leftblock->tNodes++;
            leftblock->parentblock->value[posOfLeftblock] = rightblock->value[0];
            memcpy(&rightblock->value[0], &rightblock->value[1], sizeof(int)*(rightblock->tNodes+1));
            memcpy(&rightblock->childblock[0], &rightblock->childblock[1], sizeof(rootblock)*(rightblock->tNodes+1));
            rightblock->tNodes--;

        }else{
            leftblock->value[leftblock->tNodes] = rightblock->value[0];
            leftblock->tNodes++;
            memcpy(&rightblock->value[0], &rightblock->value[1], sizeof(int)*(rightblock->tNodes+1));
            rightblock->tNodes--;

            leftblock->parentblock->value[posOfLeftblock] = rightblock->value[0];
        }



    }else{
	if(!isLeaf){

            memcpy(&rightblock->value[1], &rightblock->value[0], sizeof(int)*(rightblock->tNodes+1));
            memcpy(&rightblock->childblock[1], &rightblock->childblock[0], sizeof(rootblock)*(rightblock->tNodes+1));
            rightblock->value[0] = leftblock->parentblock->value[posOfLeftblock];
            rightblock->childblock[0] = leftblock->childblock[leftblock->tNodes];

            rightblock->tNodes++;

            leftblock->parentblock->value[posOfLeftblock] = leftblock->value[leftblock->tNodes-1];
            leftblock->value[leftblock->tNodes-1] = INT_MAX;
            leftblock->childblock[leftblock->tNodes] = NULL;
            leftblock->tNodes--;

        }else{
            memcpy(&rightblock->value[1], &rightblock->value[0], sizeof(int)*(rightblock->tNodes+1));
            rightblock->value[0] = leftblock->value[leftblock->tNodes-1];
            rightblock->tNodes++;

            leftblock->value[leftblock->tNodes-1] = INT_MAX;
            leftblock->tNodes--;

            leftblock->parentblock->value[posOfLeftblock] = rightblock->value[0];
        }
    }
}

void mergeblock(block *leftblock, block *rightblock, bool isLeaf, int posOfRightblock){

    if(!isLeaf){

        leftblock->value[leftblock->tNodes] = leftblock->parentblock->value[posOfRightblock-1];
        leftblock->tNodes++;
    }

    memcpy(&leftblock->value[leftblock->tNodes], &rightblock->value[0], sizeof(int)*(rightblock->tNodes+1));
    memcpy(&leftblock->childblock[leftblock->tNodes], &rightblock->childblock[0], sizeof(rootblock)*(rightblock->tNodes+1));


    leftblock->tNodes += rightblock->tNodes;

    memcpy(&leftblock->parentblock->value[posOfRightblock-1], &leftblock->parentblock->value[posOfRightblock], sizeof(int)*(leftblock->parentblock->tNodes+1));
    memcpy(&leftblock->parentblock->childblock[posOfRightblock], &leftblock->parentblock->childblock[posOfRightblock+1], sizeof(rootblock)*(leftblock->parentblock->tNodes+1));
    leftblock->parentblock->tNodes--;

     for(int i=0;leftblock->childblock[i]!=NULL;i++){
        leftblock->childblock[i]->parentblock = leftblock;
    }



}*/
bool dataFound;
void print(vector < block* > blocks){
    vector < block* > newblocks;
    for(int i=0; i<blocks.size(); i++){ 
        block *curblock = blocks[i];

        cout <<"[|";
        int j;
        for(j=0; j<curblock->tNodes; j++){
            cout << curblock->value[j] << "|";
            if(curblock->childblock[j]!=NULL)
            newblocks.push_back(curblock->childblock[j]);
        }
        if(curblock->value[j]==INT_MAX && curblock->childblock[j]!=NULL)
            newblocks.push_back(curblock->childblock[j]);

        cout << "]  ";
    }

    if(newblocks.size()==0){

        cout<<"";
        cout<<"";
        blocks.clear();
    }
    else {             
        cout<<"";
        cout<<"";
        blocks.clear();
        print(newblocks);
    }
}

int main()
{
	int n=0;
	cout<<"\nEnter the no of element you wants to Store: ";
	cin>>n;    
	int arr[n];	
	for(int i=0;i<n;i++)	
	{
		cout<<"\nEnter the Element in tree: ";
		cin>>arr[i];
	}
	
	vector < block* > blocks;
    	cout<<"Pointers: ";
    	cin>>nop;
	for(int i=0;i<n;i++)
		insertNode(rootblock, arr[i]);

	blocks.clear();
        blocks.push_back(rootblock);
        print(blocks);



   return 0;
}
