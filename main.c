#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10000 /*参加排序元素的最大个数*/
#define INF 0x3f
#include <time.h>//用到clock()函数
typedef	int	KeyType;
typedef int InfoType;
typedef struct {
    KeyType	key;
    InfoType weight;	// 其他字段（自己设计）
}RedType;

typedef struct
{
    RedType	r[MAXSIZE+1];
    int	length; /*参加排序元素的实际个数*/
}SqList;

//数据初始化部分
void partially_ordered_init(SqList* M);
void partially_reverse_init(SqList* M);
void completely_random_init(SqList* M,int size);
void print_L(SqList* L);//打印L

int SelectMinKey(SqList* L,int i);//选择[i,length]里的最小值并返回下标
void Swap(SqList* L, int x, int y);//交换下标为i和index的数据

void SelectSort(SqList* L,int* compare_count,int* move_count);//选择排序
void InsertSort(SqList* L,int* compare_count,int* move_count);//插入排序
void BubbleSort(SqList* L,int* compare_count,int* move_count);//冒泡排序
void BInsertSort(SqList* L,int* compare_count,int* move_count);//折半插入排序
void QuickSort_Recursion(SqList* L,int low,int high,int* compare_count,int* move_count);//快速排序——递归

int Partition(SqList* L,int low,int high,int* compare_count,int* move_count);//将数列L按枢轴划分开，使枢轴左边的数都比他小，右边都比他大,low为最左边的下标，high为最右边的下标
void HeapSort(SqList* L,int* compare_count,int* move_count);//堆排序
void Build_Heap(SqList* L,int* compare_count,int* move_count);//构建堆
void Heapify(SqList* L,int i,int* compare_count,int* move_count);//将一个部分有序的“大顶堆”转换成一个有序的堆

//void QuickSort_NotR(SqList *l);//快速排序——非递归

void MergingSort(SqList* M,int l,int m,int r,int* compare_count,int* move_count);//两个有序序列的 归并排序
void MergeSort(SqList* M,int l,int r,int* compare_count,int* move_count);//完全无序的序列归并排序
void ShellSort(SqList* M,int* compare_count,int* move_count);   //希尔排序

void reset(SqList* M,SqList* L);//重置数组
void menu();//一级菜单
void menu1();//二级菜单
void menu2(SqList* M,SqList* L);//三级菜单

void show_selection(int m);

int main() {
    menu();
    return 0;
}

void menu()
{
    printf("选择一个测试数据，进行排序，部分有序，部分逆序，完全随机\n");

    printf("\t\t1.部分有序\n");
    printf("\t\t2.部分逆序\n");
    printf("\t\t3.完全随机\n");
    printf("\t\t4.清空控制台\n");
    printf("\t\t0.退出程序\n");
    menu1();
    return;

}

void menu1()
{

    SqList* M = (SqList*)malloc(sizeof(SqList));
    SqList* L = (SqList*)malloc(sizeof(SqList));
    int k;
    printf("请选择操作：");
    scanf("%d",&k);

    while(k!=7)
    {
        switch(k) {
            case 1:  partially_ordered_init(M);  break;
            case 2:  partially_reverse_init(M); break;
            case 3:  completely_random_init(M,10); break;
            case 4:
                system("cls");
                menu();
                break;
            case 0:
                free(M);
                free(L);
                return;
        }
        if(k==1)
            printf("您已选择部分有序数据\n");
        else if(k==2)
            printf("您已选择部分逆序数据\n");
        else if(k==3)
            printf("您已选择完全随机数据\n");
        printf("\n");
        break;
    }

    printf("显示原始数组：\n");
    print_L(M);
    printf("\n");
    printf("接下来，请选择一个排序方法\n");
    printf("\t\t1.选择排序法\n");
    printf("\t\t2.插入排序法\n");
    printf("\t\t3.冒泡排序法\n");
    printf("\t\t4.折半插入排序法\n");
    printf("\t\t5.快速排序法\n");
    printf("\t\t6.堆比较排序法\n");
    printf("\t\t7.归并排序法\n");
    printf("\t\t8.希尔排序法\n");
    printf("\t\t9.返回上一级\n");
    printf("\t\t10.结束\n");

    reset(M,L);

    menu2(M,L);
}

void menu2(SqList* M,SqList* L)
{
    int m;
    int low =0 ,high = L->length - 1;
    int l = 0, r = L->length-1;

    printf("请输入您的操作：");
    scanf("%d",&m);
    printf("\n");
    int compare_count,move_count;
    while(m!=16)
    {
        show_selection(m);
        switch(m)
        {
            case 1:
                compare_count=move_count=0;
                SelectSort(L,&compare_count,&move_count);
                printf("比较次数：%-8d移动次数：%-8d\n",compare_count,move_count);
                break;
            case 2:
                compare_count=move_count=0;
                InsertSort(L,&compare_count,&move_count);
                printf("比较次数：%-8d移动次数：%-8d\n",compare_count,move_count);
                break;
            case 3:
                compare_count=move_count=0;
                BubbleSort(L,&compare_count,&move_count);
                printf("比较次数：%-8d移动次数：%-8d\n",compare_count,move_count);
                break;
            case 4:
                compare_count=move_count=0;
                BInsertSort(L,&compare_count,&move_count);
                printf("比较次数：%-8d移动次数：%-8d\n",compare_count,move_count);
                break;
            case 5:
                compare_count=move_count=0;
                QuickSort_Recursion(L,low,high,&compare_count,&move_count);
                printf("比较次数：%-8d移动次数：%-8d\n",compare_count,move_count);
                break;
            case 6:
                compare_count=move_count=0;
                HeapSort(L,&compare_count,&move_count);
                printf("比较次数：%-8d移动次数：%-8d\n",compare_count,move_count);
                break;
            case 7:
                compare_count=move_count=0;
                MergeSort(L,l,r,&compare_count,&move_count);
                printf("比较次数：%-8d移动次数：%-8d\n",compare_count,move_count);
                break;
            case 8:
                compare_count=move_count=0;
                ShellSort(L,&compare_count,&move_count);
                printf("比较次数：%-8d移动次数：%-8d\n",compare_count,move_count);
                break;
            case 9:
                menu();
                break;
            case 10:
                free(M);
                free(L);
                return;
        }


        print_L(L);
        printf("\n");
        printf("重置数组\n");
        printf("\n");
        reset(M,L);
        printf("\n");
        break;
    }

    menu2(M,L);

}

//部分有序
void partially_ordered_init(SqList* M){
    int a[] = {49,3,37,67,89,23,15,35,123,45,5,47,49,98,56,46,13,78,8,12,46,75,46,58,96,45,35,35,23,56,67,89,23,14,25,67,34,68,97,14,5,12,34,57,49,79,78,65,43,46};
    M->length=sizeof(a)/4;
    for (int i = 0; i < M->length; ++i) {
        M->r[i].key=a[i];
        M->r[i].weight = i;
    }
}

//部分逆序
void partially_reverse_init(SqList* M)
{
    int a[] = {49,3,37,67,89,23,15,35,123,45,5,47,49,143,92,56,34,32,14,12,7,75,46,58,96,45,35,35,23,56,67,89,23,14,25,67,34,68,97,14,5,12,34,57,49,79,78,65,43,46};
    M->length=sizeof(a)/4;
    for (int i = 0; i < M->length; ++i) {
        M->r[i].key=a[i];
        M->r[i].weight = i;
    }
}

//随机产生数组
void completely_random_init(SqList* M,int size)
{
    M->length=size;
    for (int i = 0; i < M->length; ++i) {
        M->r[i].key = rand() % (100 - 0 + 1);
        M->r[i].weight = i;
    }

}

//重置已排好序的数组
void reset(SqList* M,SqList* L)
{
    L->length=M->length;

    for (int i = 0; i < M->length; ++i) {
        L->r[i].key=M->r[i].key;
        L->r[i].weight = M->r[i].weight;
    }

}
//显示选择的是何种排序算法
void show_selection(int m)
{
    while(m)
    {
        switch(m)
        {
            case 1:
                printf("\t\t已选选择排序法\n");
                break;
            case 2:
                printf("\t\t已选插入排序法\n");
                break;
            case 3:
                printf("\t\t已选冒泡排序法\n");
                break;
            case 4:
                printf("\t\t已选折半插入排序法\n");
                break;
            case 5:
                printf("\t\t已选快速排序法\n");
                break;
            case 6:
                printf("\t\t已选堆比较排序法\n");
                break;
            case 7:
                printf("\t\t已选归并排序法\n");
                break;
            case 8:
                printf("\t\t已选希尔排序法\n");
                break;
        }
        break;
    }
    printf("结果显示：\n");
}
//打印L
void print_L(SqList* L){
    for (int i = 0; i < L->length; ++i) {
        printf("key:%-4d weight:%-4d\n",L->r[i].key,L->r[i].weight);
    }
}
//值交换
void Swap(SqList* L, int x, int y){
    RedType temp;
    if (L->r[x].key != L->r[y].key){
        temp = L->r[x];
        L->r[x] = L->r[y];
        L->r[y] = temp;
    }
}
//选择排序
void SelectSort(SqList* L,int* compare_count,int* move_count){
    int length=L->length;//数组长度
    //循环比较，假如数组长度为10，则循环9次。第一趟循环有10个数，找出这十个数的最小值放在一位。第二次循环找出另外9个数的最小值，放在数字第二位。第三次找出另外8个数最小值，以此类推...
    for(int i=0;i<length-1;i++){
        //用来保存每一趟最小值数组的下标，开始前假设第一个数字为这趟的最小值
        int minIndex=i;
        //找出每一趟的最小值，如果有最小值就将这趟的最小值放在这趟数组第一个位，如果没有最小值就继续执行下一趟
        for(int j=i+1;j<length;j++){
            if(L->r[j].key<L->r[minIndex].key){
                //如果这一趟有最小值,则保存它的下标。如果这一趟没有最小值，这下标还是这趟的第一个数字
                minIndex=j;
                (*compare_count)++;
            }
        }
        //将这趟的第一个数字和这趟的最小值交换位置
        Swap(L, i, minIndex);
        (*move_count)++;
    }
}
//选择最小值
int SelectMinKey(SqList* L,int i){
    int min=INF;
    int index;
    for (int j=i+1; j < L->length; ++j) {
        if (L->r[j].key<min){
            min = L->r[j].key;
            index=j;
        }
    }return index;
}
//插入排序
void InsertSort(SqList* L,int* compare_count,int* move_count){
    int i,j;
    int length=L->length;
    for(i=1;i<length;i++)
    {
        for(j=i-1;j>=0&&L->r[i].key<L->r[j].key;j--)
        {
            //L->[i].key代表要插入的数字，L->[j].key代表需要比较大小的数字，j递减
            //当L->[i].key大于L->[j].key时（L->[i].key插入的位置，也就是说插在j的后一位）或者L->[i].key为当前数组的最小值时
            //（此时的j为-1,也就是说L->[i].key要插在第一位）返回j
            (*compare_count)++;
        }
        int temp=L->r[i].key;

        for(int k=i;k>j+1;k--)
        {
            //将i到j范围的数组向后移一位
            L->r[k].key=L->r[k-1].key;
            (*move_count)++;
        }
        //intArrays[i]插在j的后一位
        L->r[j+1].key=temp;
        (*move_count)++;
    }
}
//冒泡排序
void BubbleSort(SqList* L,int* compare_count,int* move_count){
    for (int i = 1; i < L->length; ++i) {
        for (int j = 0; j < L->length-i; ++j) {
            if (L->r[j].key > L->r[j+1].key){
                Swap(L,j,j+1);
                (*compare_count)++;
                (*move_count)++;
            }
        }
    }
}
//折半插入排序
void BInsertSort(SqList* L,int* compare_count,int* move_count){
    RedType R; //暂存位置
    int low,high,mid,i,j;
    for (i = 1; i < L->length; ++i) {
        R = L->r[i];
        low = 0;
        high = i-1;
        while(low<=high){
            mid = (low+high)/2;
            if(R.key < L->r[mid].key)
                high = mid-1;
            else
                low = mid+1;
            (*compare_count)++;
        }
        for (j = i-1; j >= high+1 ; --j){
            L->r[j+1] = L->r[j];
            (*move_count)++;
        }
        L->r[high+1] = R;
        (*move_count)++;
    }
}
//快速排序
void QuickSort_Recursion(SqList* L,int low,int high,int* compare_count,int* move_count){
    int pivotloc;
    if (low<high){
        pivotloc = Partition(L,low,high,compare_count,move_count);
        QuickSort_Recursion(L,low,pivotloc-1,compare_count,move_count);
        QuickSort_Recursion(L,pivotloc+1,high,compare_count,move_count);
    }

}
//将数列L按枢轴划分开，使枢轴左边的数都比他小，右边都比他大
int Partition(SqList* L,int low,int high,int* compare_count,int* move_count){
    RedType R = L->r[low];//将最左边low位得数据先暂存在R，该数据为枢轴
    int pivotkey = L->r[low].key;
    while(low<high){
        //如果high位得key大于pivotkey，则high指针向左移，知道high位得key<pivotkey时，结束循环，然后将high位得值赋给low位
        while (low<high && L->r[high].key>=pivotkey)     --high;
        L->r[low] = L->r[high];
        //如果low位得key<pivotkey，则咯哇指针右移，直至low位得key>pivotkey时，结束循环，然后将该low位得值赋给high位
        while(low<high && L->r[low].key<=pivotkey)   ++low;
        L->r[high] = L->r[low];
        (*move_count)++;
        (*compare_count)++;
    }
    //low==high 时循环结束，此时low（或high）位没有数据，将枢轴得数据赋给low位
    L->r[low] = R;
    (*move_count)++;
    return low;
}
//堆排序
void HeapSort(SqList* L,int* compare_count,int* move_count){
    Build_Heap(L,compare_count,move_count);
    int n = L->length;
    for (int i = n-1; i >=0 ; --i) {
        Swap(L,i,0);
        L->length-=1;
        Heapify(L,0,compare_count,move_count);
    }
    L->length = n;
}
//建堆
void Build_Heap(SqList* L,int* compare_count,int* move_count){
    int last_node = L->length - 1;
    int Last_parent = (last_node - 1) / 2;
    for (int i=Last_parent; i >=0 ; --i) {
        Heapify(L,i,compare_count,move_count);
    }
}
//将一个部分有序的堆转换成一个有序的“大顶堆”
void Heapify(SqList* L,int i,int* compare_count,int* move_count){
    int left = i * 2 + 1;
    int right = i * 2 + 2;
    int max = i;
    if(left < L->length && L->r[left].key > L->r[max].key){
        max = left;
        (*compare_count)++;
    }
    if(right < L->length && L->r[right].key > L->r[max].key){
        max = right;
        (*compare_count)++;
    }
    if(max != i){
        Swap(L,i,max);
        (*move_count)++;
        Heapify(L,max,compare_count,move_count);
    }

}
//两个有序序列归并排序
//l为最左边元素下标，r为最右边元素下标,m为第二个数组的第一个下标
void MergingSort(SqList* L,int l,int m,int r,int* compare_count,int* move_count){
    int LEFT_SIZE = m-l;
    int RIGHT_SIZE = r-m+1;
    RedType left[LEFT_SIZE];
    RedType right[RIGHT_SIZE];
    int i,j,k=l;
    for (i = 0; i < LEFT_SIZE; ++i) {
        left[i] = L->r[k];
        k++;
    }
    for (j = m; j <=r ; ++j) {
        right[j-m] = L->r[j];
    }
//    for (int n = 0; n < RIGHT_SIZE; ++n) {
//        printf("%d ",right[n].key);
//    }
//    printf("\n");
    i=0;    j=0;    k=l;
    while(i<LEFT_SIZE && j<RIGHT_SIZE){
        if(left[i].key < right[j].key){
            L->r[k] = left[i];
            i++;
            k++;
        }
        else{
            L->r[k] = right[j];
            j++;
            k++;
        }
        (*compare_count)++;
        (*move_count)++;
    }
    while(i < LEFT_SIZE){
        L->r[k] = left[i];
        i++;
        k++;
        (*move_count)++;
    }
    while(j < RIGHT_SIZE){
        L->r[k] = right[j];
        j++;
        k++;
        (*move_count)++;
    }
}
//完全无序的序列归并排序
//l为最左边元素下标，r为最右边元素下标
void MergeSort(SqList* L,int l,int r,int* compare_count,int* move_count){
    if(l==r) return;
    else{
        int m = (l+r)/2;
        MergeSort(L,l,m,compare_count,move_count);
        MergeSort(L,m+1,r,compare_count,move_count);
        MergingSort(L,l,m+1,r,compare_count,move_count);
    }
}
//希尔排序
void ShellSort(SqList* L,int* compare_count,int* move_count)
{ /* 希尔排序 - 用Sedgewick增量序列 */
    int Si, D, P, i;
    RedType x;
    /* 这里只列出一小部分增量 */
    int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};
    for ( Si=0; Sedgewick[Si]>=L->length; Si++ )
        ; /* 初始的增量Sedgewick[Si]不能超过待排序列长度 */
    for ( D=Sedgewick[Si]; D>0; D=Sedgewick[++Si] )
        for ( P=D; P<L->length; P++ ) { /* 插入排序*/
            x = L->r[P];
            (*move_count)++;
            for ( i=P; i>=D && L->r[i-D].key > x.key; i-=D ){
                L->r[i] = L->r[i-D];
                (*move_count)++;
                (*compare_count)++;
            }
            L->r[i] = x;
        }
}
