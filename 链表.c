/*首先要明白，链表原理是创建一个节点，这个节点里面有一个东西来放数据，一个东西来指向下一个节点
也就是一个指针存下一个节点，这个指向下一个节点的指针和这个数据被存在同一个节点里面*/

#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

//单链表定义
typedef struct node
{
	ElemType data;		//这里，next必须是指针，指向下一个节点，所以是struct node*类型
	struct node* next;
}Node;

//单链表初始化
Node* initList()							 //这是一个Node*类型的函数，return的head也必须是Node*类型，Node为前面自定义的数据类型
{
	/*注意初始节点也被称作头节点，后续说数据位置是不算头节点的*/
	Node* head = (Node*)malloc(sizeof(Node));//初始节点data为0
	head->data = 0;							 //初始节点只有一个节点，next指针没有指向，只能是NULL指针
	head->next = NULL;
	return head;
}

//单链表头插法（结合那个网课的图理解吧
int insertHead(Node* L, ElemType e)
{
	Node* p = (Node*)malloc(sizeof(Node));   //p为新创建的节点，有一个data和next
	p->data = e;							 //将需求的数值e赋值给新节点p的data
	p->next = L->next;						 //由于p节点后续是没有节点的，所以要将初始节点的NULL赋值给p节点,后续继续头插依旧是NULL，因为p为新节点，p->next后面始终没有东西
	L->next = p;							 //将p节点的地址传给初始节点，使初始节点的next能指向下一个节点也就是节点p
	return 1; 
}

//单链表遍历输出
void listNode(Node* L)
{
	//从头节点的下一个节点开始，注意这个p指向的一直都是节点啊
	Node* p = L->next;

	//这里需要遍历到没有节点为止，没有节点的情况下p指向的就是NULL
	while (p!=NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

//单链表获取尾节点（你在调用函数然后传入主函数中list的时候每次传入的节点实际上都是头节点，因为初始化函数里面返回head，所以尾插法要先获取尾部地址
Node* get_tail(Node* L)
{
	/*看到这里，包括前面和后面所有，为什么形参L已经传入了还要新创建一个指针p呢，就是为了不修改头节点的位置
	如果直接对L进行变动，那么头节点就会一直变*/
	Node* p = L;			
	while (p->next != NULL)	//遍历到了next为NULL说明这个节点是最后一个节点了
	{
		p = p->next;
	}
	return p;				//然后将最后一个节点的指针返回
}

//单链表尾插法（要先获取尾节点
Node* insertTail(Node* tail, ElemType e)
{
	Node* p = (Node*)malloc(sizeof(Node));	//依旧p为新的节点
	p->data = e;							//新节点的数据域为传入的e
	tail->next = p;							//传入的尾节点tail里面的next指向新创建的节点，也就是将新节点创建在最后
	p->next = NULL;							//新节点的next后面没有节点，赋值NULL
	return p;
}

//单链表在指定位置插入数据(我们再说数据位置的时候不包含头节点，所以第二个数据的位置实际上是链表的第三个节点
int insertNode(Node* L, int pos, ElemType e)
{
	Node* p = L;
	int i = 0;

	/*这个地方虽然不涉及下标，但是依旧可以近似下标来理解，因为头节点不计入数据数量
	比如我要第在第2个数据位置插入数据，那实际上是第三个节点，pos = 2，
	那就要在i等于0的时候往前挪1次找到这个节点的前驱，但是实际上为了便于理解，我们可以直接i = 1
	然后就可以不用谢i < pos - 1了，写i < pos就行*/
	while (i < pos - 1)		//因为头插法list位置不变，只是list里面的next在变，所以可以这样遍历
	{
		p = p->next;		
		i++;
		if (p == NULL)		//如果遍历到NULL就说明插入的位置就超出链表总长度了对吧，所以就不执行
		{
			return 0;
		}
	}//上面走完其实是遍历到的插入位置的前驱，比如

	/*有一个很重要的需要注意，我们插入的时候一定要先把插入的节点先指向他的后继
	然后再把他的前驱指向要插入的元素，如果你先把前驱指向该插入元素，后继的地址会丢失
	一定不要忘，很重要*/
	Node* q = (Node*)malloc(sizeof(Node));//这里新插入的节点参数是q
	q->data = e;			//需求的数值赋值给q节点
	q->next = p->next;		//这里，p是q的上一个节点，在p->next被修改之前，它指向的是q的后一个节点，所以要赋值给q->next，让q指向它插入位置的后一个节点
	p->next = q;			//然后让p指向q节点，也就是p->next赋值为q
	return 1;
}

//单链表删除节点（删除的时候记得要释放内存，因为我们都是动态分配的内存
int deleteNode(Node* L, int pos)
{
	Node* p = L;
	int i = 0;
	while (i < pos - 1)		//这里和上面插入是一样的，如果i = 1就可以写i < pos
	{
		/*这里还是和插入的函数一样，遍历到了要删除的那个节点的前一个节点
		因为我们要用这个指向删除节点的后继*/
		p = p->next;		
		i++;
		if (p == NULL)
		{
			return 0;
		}
	}

	/*这个地方是一个必要的判断*/
	if (p->next == NULL)
	{
		printf("要删除的位置错误\n");
		return 0;
	}

	Node* q = p->next;		//q是要删除的节点，然后p其实是q的前驱
	p->next = q->next;		//将p节点指向要删除的节点之后的节点，所以要讲中间这个节点q的next赋值给p，这一步很重要，要让删除节点q的前驱指向q的后继
	free(q);				//这一步很重要不要忘了，删内存
	return 1;
}

//单链表获取链表长度
int listLength(Node* L)//卧槽这个太他妈简单了，我学到这紧皱的眉头舒展开了
{
	Node* p = L;
	int len = 0;
	while (p != NULL)
	{
		p = p->next;
		len++;
	}
	return len;
}

/*释！放！链表
思路是创建一个p和q，p指向第一个节点，q第二个节点，然后开始
判断p是否为空，如果不是，用q记录p的后继，这样free(p)过后p的后继不会丢失
释放p，然后pq往后挪，重复以上操作*/
void freeList(Node* L)
{
	Node* p = L->next;		//因为L是头节点啊，所以让这个p指向真正有数值的第一个节点开始
	Node* q;
	while (p != NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;			//这里不能单独剩一个节点，这个指针没有指向任何东西，必须赋值NULL
}


/*----------------下面为单链表应用----------------*/


/*双指针找到倒数第k个节点，原理是创建两个指针，一个快指针一个慢指针
比如要找倒数第3个指针吧，就先把快指针往前挪3个，然后快慢指针一起往前移动
直到快指针指向空，也就是把链表遍历完了，此时慢指针指向倒数第3个节点*/
void findNodeFS(Node* L, int k)
{
	Node* fast = L->next;
	Node* slow = L->next;
	for (int i = 0; i < k; i++)
	{
		fast = fast->next;
	}
	while (fast != NULL)
	{
		fast = fast->next;
		slow = slow->next;
	}
	printf("倒数第%d个节点值为：%d\n", k, slow->data);
}

int main()
{
	/*list直接等于上面初始化的函数，不用传入任何值，list会被返回head节点，head里面是一个Node类型的数据，就是一个节点，但是数据域是0，指针域是NULL
	而且这个地方一定一定要记住，list的位置是始终不变的，一直都是头节点，只是list里面的next一直在变*/
	Node* list = initList();	

	/*由于头插入法是始终在头节点面前创建新指针，所以越先创建的指针排序越靠后
	这一步最终的输出结果应该是30 20 10*/
	insertHead(list, 10);		
	insertHead(list, 20);
	insertHead(list, 30);		
	listNode(list);

	/*这里需要一个工具tail用来搬运尾部插入的新节点，这个tail节点位于整个链表结构之外，用于存储链表最后一个节点的地址，
	因为尾插法的子函数会返回一个p到tail->next，此时tail里面存储了最新节点的地址而tail的data里面什么都没有
	尾插法是在尾部插入的，所以代码到此为止输出的话输出顺序应该是30 20 10 40*/
	Node* tail = get_tail(list);
	tail = insertTail(tail, 40);//这里为什么要tail本身来接收这个返回值，因为要保证tail始终指向最后一个节点，而这个insertTail子函数会返回最后一个节点的地址
	listNode(list);

	/*这个是插入，到这输出应该是30 15 20 10 40*/
	insertNode(list, 2, 15);	
	listNode(list);

	/*这里把刚添加的第二个元素15删除了，输出应该是30 20 10 40*/
	deleteNode(list, 2);		
	listNode(list);

	/*这里获取倒数第二个节点的数据*/
	findNodeFS(list, 2);

	/*这里是获取链表长度和释放链表*/
	printf("链表长度为：%d\n", listLength(list));		//这里输出5，因为还包含一个头节点，如果后面什么都没有说明我们删除链表成功了
	freeList(list);
	printf("链表释放完毕，长度为：%d", listLength(list));		//这里输入1说明我们删除链表成功了
	return 0;
}