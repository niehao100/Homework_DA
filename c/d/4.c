#include<stdio.h>
#include<stdlib.h>
//二叉搜索树
#define Tnode struct tnode

typedef int Elemtype;

struct tnode{
		Elemtype data;
		int count;
		Tnode* Tleft;
		Tnode* Tright;
		Tnode* parent;
};

Tnode* CreateTree(); //建树   
Tnode* insert(Tnode* root, Elemtype data);//插入节点   
 
Tnode* CreateTree(){  
    Tnode* root = NULL, *newNode = (Tnode*)malloc(sizeof(Tnode));   
    Elemtype temp = 0; 
    int i=0,count=0;
    scanf("%d", &count); 
    if(count==0) return root;
    scanf("%d", &temp);
    newNode->data = temp ;
    newNode->count = 1;
    newNode->Tleft = NULL;  
    newNode->Tright = NULL;
		root = newNode;
    for(i=1;i<count;i++){  
        scanf("%d", &temp);    
        insert(root, temp);    
    }  
      
    return root;   
} 

Tnode* insert(Tnode* root, Elemtype data){  
    Tnode* ptr = root;  
    Tnode* tempNode;   
    Tnode* newNode = (Tnode*)malloc(sizeof(Tnode));   
    //初始化元素
    newNode->data = data ;  
    newNode->count = 1;
    newNode->Tleft = NULL;  
    newNode->Tright = NULL;  
      
    
    while(ptr != NULL){  
        tempNode = ptr;
        ptr->count++;
        if(data < ptr->data)  
            ptr = ptr->Tleft;   
        else  
            ptr = ptr->Tright;   
              
    }   
          
     if(data < tempNode->data ){  
        tempNode->Tleft =  newNode;   
        }else{  
           tempNode->Tright =  newNode;   
        
        }   
      
    return root;   
} 

void InBTree(Tnode* root){  
    if(root != NULL){  
        InBTree(root->Tleft);   
        printf("%d ", root->data);   
        InBTree(root->Tright);  
    }  
    else printf("# "); 
}  

void PreBTree(Tnode* root){  
    if(root != NULL){  
        printf("%d ", root->data);   
        PreBTree(root->Tleft);   
        PreBTree(root->Tright);  
    } 
    else printf("# "); 
}   
void BackBTree(Tnode* root){  
    if(root != NULL){  
        BackBTree(root->Tleft);   
        BackBTree(root->Tright);  
        printf("%d ", root->data);  
    }  
    else printf("# "); 
}


int BTreeDepth(Tnode*root)
{
    if(root == NULL)
        return 0;
    //计算左子树深度
    int dpt1 = BTreeDepth(root->Tleft);
    //计算右子树深度
    int dpt2 = BSTreeDepth(root->Tright);
    //返回树的深度
    if(dpt1 > dpt2)
        return dpt1+1;
    else
        return dpt2+1;
}

int compare(Tnode* a,Tnode* b){
    if(a->count!=b->count) return 0;
    if(compare(a
}

int main(void){
    Tnode* CreateTree(),* root=CreateTree()，search=CreateTree();
		void InBTree(Tnode*), PreBTree(Tnode* ),BackBTree(Tnode*);
    int deep=BTreeDepth(search);
    PreBTree(root);
    printf("\n");
    InBTree(root);
    printf("\n");
    BackBTree(root);
    printf("\n");
    printf("%d\n", BTreeDepth(root));
    
    return 0;
    
}
