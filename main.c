#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10000 /*�μ�����Ԫ�ص�������*/
#define INF 0x3f
#include <time.h>//�õ�clock()����
typedef	int	KeyType;
typedef int InfoType;
typedef struct {
    KeyType	key;
    InfoType weight;	// �����ֶΣ��Լ���ƣ�
}RedType;

typedef struct
{
    RedType	r[MAXSIZE+1];
    int	length; /*�μ�����Ԫ�ص�ʵ�ʸ���*/
}SqList;

//���ݳ�ʼ������
void partially_ordered_init(SqList* M);
void partially_reverse_init(SqList* M);
void completely_random_init(SqList* M,int size);
void print_L(SqList* L);//��ӡL

int SelectMinKey(SqList* L,int i);//ѡ��[i,length]�����Сֵ�������±�
void Swap(SqList* L, int x, int y);//�����±�Ϊi��index������

void SelectSort(SqList* L,int* compare_count,int* move_count);//ѡ������
void InsertSort(SqList* L,int* compare_count,int* move_count);//��������
void BubbleSort(SqList* L,int* compare_count,int* move_count);//ð������
void BInsertSort(SqList* L,int* compare_count,int* move_count);//�۰��������
void QuickSort_Recursion(SqList* L,int low,int high,int* compare_count,int* move_count);//�������򡪡��ݹ�

int Partition(SqList* L,int low,int high,int* compare_count,int* move_count);//������L�����Ữ�ֿ���ʹ������ߵ���������С���ұ߶�������,lowΪ����ߵ��±꣬highΪ���ұߵ��±�
void HeapSort(SqList* L,int* compare_count,int* move_count);//������
void Build_Heap(SqList* L,int* compare_count,int* move_count);//������
void Heapify(SqList* L,int i,int* compare_count,int* move_count);//��һ����������ġ��󶥶ѡ�ת����һ������Ķ�

//void QuickSort_NotR(SqList *l);//�������򡪡��ǵݹ�

void MergingSort(SqList* M,int l,int m,int r,int* compare_count,int* move_count);//�����������е� �鲢����
void MergeSort(SqList* M,int l,int r,int* compare_count,int* move_count);//��ȫ��������й鲢����
void ShellSort(SqList* M,int* compare_count,int* move_count);   //ϣ������

void reset(SqList* M,SqList* L);//��������
void menu();//һ���˵�
void menu1();//�����˵�
void menu2(SqList* M,SqList* L);//�����˵�

void show_selection(int m);

int main() {
    menu();
    return 0;
}

void menu()
{
    printf("ѡ��һ���������ݣ��������򣬲������򣬲���������ȫ���\n");

    printf("\t\t1.��������\n");
    printf("\t\t2.��������\n");
    printf("\t\t3.��ȫ���\n");
    printf("\t\t4.��տ���̨\n");
    printf("\t\t0.�˳�����\n");
    menu1();
    return;

}

void menu1()
{

    SqList* M = (SqList*)malloc(sizeof(SqList));
    SqList* L = (SqList*)malloc(sizeof(SqList));
    int k;
    printf("��ѡ�������");
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
            printf("����ѡ�񲿷���������\n");
        else if(k==2)
            printf("����ѡ�񲿷���������\n");
        else if(k==3)
            printf("����ѡ����ȫ�������\n");
        printf("\n");
        break;
    }

    printf("��ʾԭʼ���飺\n");
    print_L(M);
    printf("\n");
    printf("����������ѡ��һ�����򷽷�\n");
    printf("\t\t1.ѡ������\n");
    printf("\t\t2.��������\n");
    printf("\t\t3.ð������\n");
    printf("\t\t4.�۰��������\n");
    printf("\t\t5.��������\n");
    printf("\t\t6.�ѱȽ�����\n");
    printf("\t\t7.�鲢����\n");
    printf("\t\t8.ϣ������\n");
    printf("\t\t9.������һ��\n");
    printf("\t\t10.����\n");

    reset(M,L);

    menu2(M,L);
}

void menu2(SqList* M,SqList* L)
{
    int m;
    int low =0 ,high = L->length - 1;
    int l = 0, r = L->length-1;

    printf("���������Ĳ�����");
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
                printf("�Ƚϴ�����%-8d�ƶ�������%-8d\n",compare_count,move_count);
                break;
            case 2:
                compare_count=move_count=0;
                InsertSort(L,&compare_count,&move_count);
                printf("�Ƚϴ�����%-8d�ƶ�������%-8d\n",compare_count,move_count);
                break;
            case 3:
                compare_count=move_count=0;
                BubbleSort(L,&compare_count,&move_count);
                printf("�Ƚϴ�����%-8d�ƶ�������%-8d\n",compare_count,move_count);
                break;
            case 4:
                compare_count=move_count=0;
                BInsertSort(L,&compare_count,&move_count);
                printf("�Ƚϴ�����%-8d�ƶ�������%-8d\n",compare_count,move_count);
                break;
            case 5:
                compare_count=move_count=0;
                QuickSort_Recursion(L,low,high,&compare_count,&move_count);
                printf("�Ƚϴ�����%-8d�ƶ�������%-8d\n",compare_count,move_count);
                break;
            case 6:
                compare_count=move_count=0;
                HeapSort(L,&compare_count,&move_count);
                printf("�Ƚϴ�����%-8d�ƶ�������%-8d\n",compare_count,move_count);
                break;
            case 7:
                compare_count=move_count=0;
                MergeSort(L,l,r,&compare_count,&move_count);
                printf("�Ƚϴ�����%-8d�ƶ�������%-8d\n",compare_count,move_count);
                break;
            case 8:
                compare_count=move_count=0;
                ShellSort(L,&compare_count,&move_count);
                printf("�Ƚϴ�����%-8d�ƶ�������%-8d\n",compare_count,move_count);
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
        printf("��������\n");
        printf("\n");
        reset(M,L);
        printf("\n");
        break;
    }

    menu2(M,L);

}

//��������
void partially_ordered_init(SqList* M){
    int a[] = {49,3,37,67,89,23,15,35,123,45,5,47,49,98,56,46,13,78,8,12,46,75,46,58,96,45,35,35,23,56,67,89,23,14,25,67,34,68,97,14,5,12,34,57,49,79,78,65,43,46};
    M->length=sizeof(a)/4;
    for (int i = 0; i < M->length; ++i) {
        M->r[i].key=a[i];
        M->r[i].weight = i;
    }
}

//��������
void partially_reverse_init(SqList* M)
{
    int a[] = {49,3,37,67,89,23,15,35,123,45,5,47,49,143,92,56,34,32,14,12,7,75,46,58,96,45,35,35,23,56,67,89,23,14,25,67,34,68,97,14,5,12,34,57,49,79,78,65,43,46};
    M->length=sizeof(a)/4;
    for (int i = 0; i < M->length; ++i) {
        M->r[i].key=a[i];
        M->r[i].weight = i;
    }
}

//�����������
void completely_random_init(SqList* M,int size)
{
    M->length=size;
    for (int i = 0; i < M->length; ++i) {
        M->r[i].key = rand() % (100 - 0 + 1);
        M->r[i].weight = i;
    }

}

//�������ź��������
void reset(SqList* M,SqList* L)
{
    L->length=M->length;

    for (int i = 0; i < M->length; ++i) {
        L->r[i].key=M->r[i].key;
        L->r[i].weight = M->r[i].weight;
    }

}
//��ʾѡ����Ǻ��������㷨
void show_selection(int m)
{
    while(m)
    {
        switch(m)
        {
            case 1:
                printf("\t\t��ѡѡ������\n");
                break;
            case 2:
                printf("\t\t��ѡ��������\n");
                break;
            case 3:
                printf("\t\t��ѡð������\n");
                break;
            case 4:
                printf("\t\t��ѡ�۰��������\n");
                break;
            case 5:
                printf("\t\t��ѡ��������\n");
                break;
            case 6:
                printf("\t\t��ѡ�ѱȽ�����\n");
                break;
            case 7:
                printf("\t\t��ѡ�鲢����\n");
                break;
            case 8:
                printf("\t\t��ѡϣ������\n");
                break;
        }
        break;
    }
    printf("�����ʾ��\n");
}
//��ӡL
void print_L(SqList* L){
    for (int i = 0; i < L->length; ++i) {
        printf("key:%-4d weight:%-4d\n",L->r[i].key,L->r[i].weight);
    }
}
//ֵ����
void Swap(SqList* L, int x, int y){
    RedType temp;
    if (L->r[x].key != L->r[y].key){
        temp = L->r[x];
        L->r[x] = L->r[y];
        L->r[y] = temp;
    }
}
//ѡ������
void SelectSort(SqList* L,int* compare_count,int* move_count){
    int length=L->length;//���鳤��
    //ѭ���Ƚϣ��������鳤��Ϊ10����ѭ��9�Ρ���һ��ѭ����10�������ҳ���ʮ��������Сֵ����һλ���ڶ���ѭ���ҳ�����9��������Сֵ���������ֵڶ�λ���������ҳ�����8������Сֵ���Դ�����...
    for(int i=0;i<length-1;i++){
        //��������ÿһ����Сֵ������±꣬��ʼǰ�����һ������Ϊ���˵���Сֵ
        int minIndex=i;
        //�ҳ�ÿһ�˵���Сֵ���������Сֵ�ͽ����˵���Сֵ�������������һ��λ�����û����Сֵ�ͼ���ִ����һ��
        for(int j=i+1;j<length;j++){
            if(L->r[j].key<L->r[minIndex].key){
                //�����һ������Сֵ,�򱣴������±ꡣ�����һ��û����Сֵ�����±껹�����˵ĵ�һ������
                minIndex=j;
                (*compare_count)++;
            }
        }
        //�����˵ĵ�һ�����ֺ����˵���Сֵ����λ��
        Swap(L, i, minIndex);
        (*move_count)++;
    }
}
//ѡ����Сֵ
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
//��������
void InsertSort(SqList* L,int* compare_count,int* move_count){
    int i,j;
    int length=L->length;
    for(i=1;i<length;i++)
    {
        for(j=i-1;j>=0&&L->r[i].key<L->r[j].key;j--)
        {
            //L->[i].key����Ҫ��������֣�L->[j].key������Ҫ�Ƚϴ�С�����֣�j�ݼ�
            //��L->[i].key����L->[j].keyʱ��L->[i].key�����λ�ã�Ҳ����˵����j�ĺ�һλ������L->[i].keyΪ��ǰ�������Сֵʱ
            //����ʱ��jΪ-1,Ҳ����˵L->[i].keyҪ���ڵ�һλ������j
            (*compare_count)++;
        }
        int temp=L->r[i].key;

        for(int k=i;k>j+1;k--)
        {
            //��i��j��Χ�����������һλ
            L->r[k].key=L->r[k-1].key;
            (*move_count)++;
        }
        //intArrays[i]����j�ĺ�һλ
        L->r[j+1].key=temp;
        (*move_count)++;
    }
}
//ð������
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
//�۰��������
void BInsertSort(SqList* L,int* compare_count,int* move_count){
    RedType R; //�ݴ�λ��
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
//��������
void QuickSort_Recursion(SqList* L,int low,int high,int* compare_count,int* move_count){
    int pivotloc;
    if (low<high){
        pivotloc = Partition(L,low,high,compare_count,move_count);
        QuickSort_Recursion(L,low,pivotloc-1,compare_count,move_count);
        QuickSort_Recursion(L,pivotloc+1,high,compare_count,move_count);
    }

}
//������L�����Ữ�ֿ���ʹ������ߵ���������С���ұ߶�������
int Partition(SqList* L,int low,int high,int* compare_count,int* move_count){
    RedType R = L->r[low];//�������lowλ���������ݴ���R��������Ϊ����
    int pivotkey = L->r[low].key;
    while(low<high){
        //���highλ��key����pivotkey����highָ�������ƣ�֪��highλ��key<pivotkeyʱ������ѭ����Ȼ��highλ��ֵ����lowλ
        while (low<high && L->r[high].key>=pivotkey)     --high;
        L->r[low] = L->r[high];
        //���lowλ��key<pivotkey������ָ�����ƣ�ֱ��lowλ��key>pivotkeyʱ������ѭ����Ȼ�󽫸�lowλ��ֵ����highλ
        while(low<high && L->r[low].key<=pivotkey)   ++low;
        L->r[high] = L->r[low];
        (*move_count)++;
        (*compare_count)++;
    }
    //low==high ʱѭ����������ʱlow����high��λû�����ݣ�����������ݸ���lowλ
    L->r[low] = R;
    (*move_count)++;
    return low;
}
//������
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
//����
void Build_Heap(SqList* L,int* compare_count,int* move_count){
    int last_node = L->length - 1;
    int Last_parent = (last_node - 1) / 2;
    for (int i=Last_parent; i >=0 ; --i) {
        Heapify(L,i,compare_count,move_count);
    }
}
//��һ����������Ķ�ת����һ������ġ��󶥶ѡ�
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
//�����������й鲢����
//lΪ�����Ԫ���±꣬rΪ���ұ�Ԫ���±�,mΪ�ڶ�������ĵ�һ���±�
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
//��ȫ��������й鲢����
//lΪ�����Ԫ���±꣬rΪ���ұ�Ԫ���±�
void MergeSort(SqList* L,int l,int r,int* compare_count,int* move_count){
    if(l==r) return;
    else{
        int m = (l+r)/2;
        MergeSort(L,l,m,compare_count,move_count);
        MergeSort(L,m+1,r,compare_count,move_count);
        MergingSort(L,l,m+1,r,compare_count,move_count);
    }
}
//ϣ������
void ShellSort(SqList* L,int* compare_count,int* move_count)
{ /* ϣ������ - ��Sedgewick�������� */
    int Si, D, P, i;
    RedType x;
    /* ����ֻ�г�һС�������� */
    int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};
    for ( Si=0; Sedgewick[Si]>=L->length; Si++ )
        ; /* ��ʼ������Sedgewick[Si]���ܳ����������г��� */
    for ( D=Sedgewick[Si]; D>0; D=Sedgewick[++Si] )
        for ( P=D; P<L->length; P++ ) { /* ��������*/
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
