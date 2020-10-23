#include <iostream>
#include <cstdlib>
using namespace std;
typedef struct PNode { // PCB
	struct PNode *next; // 定义指向下一个节点的指针
	char name[30]; // 定义进程名，并分配空间
	int All; // 设定总运行时间
	int Now; // 设定当前运行时间
	int insert;//设定进入时间
	char state; // 定义进程状态 Ready / End
}*Proccess; // 指向该 PCB的指针
int length;//时间片的长度
int ProccessNum; // 总进程个数
// 初始化就绪队列
void Create(Proccess &P) {
	cout << "请输入时间片的长度 : " << endl;
	cin >> length;//设置时间片的长度
	cout << "请输入总进程个数 : "<<endl;
	cin >> ProccessNum; // 进程总个数
	P = (Proccess)malloc(sizeof(PNode)); // 建立头节点
	P->next = NULL;
	Proccess I = P; // 定义一个指针
	cout << "总进程个数为 " << ProccessNum << " 个 , 请依次输入相应信息"<<endl;
	for (int i = 1; i <= ProccessNum; i++)
	{
		I = I->next = (Proccess)malloc(sizeof(PNode));
		cout << "请输入进程名  总运行时间  进入时间:"<<endl;
		cin >> I->name >> I->All>>I->insert;
		I->Now = 0;
		if (I->insert == 0){
			I->state = 'R';
		}
		else{
			I->state = 'N';//若初始时间不为0则设置为'N'
		}
		I->next = NULL;
	}
	I->next = P->next;
}
void exchage(Proccess &a, Proccess &b){//交换两个
	char name[30];
	strcpy_s(name, a->name);//先放置到中间变量
	int All = a->All;
	int Now = a->Now;
	int insert = a->insert;
	char state = a->state;
	strcpy_s(a->name, b->name);//进行交换
	a->All = b->All;
	a->Now = b->Now;
	a->insert = b->insert;
	a->state = b->state;
	strcpy_s(b->name, name);//将中间变量放到要交换的地方
	b->All = All;
	b->Now = Now;
	b->insert = insert;
	b->state = state;
}
void order(Proccess &P){//使用类似于冒泡排序法进行排序
	Proccess N = P->next;//排除头结点
	Proccess M = N->next;//M为下一个
	int flag = 1;//用flag来标记某一趟程序是否发生交换
	int num = ProccessNum-1;
	while ((num) && (flag == 1)){
		flag = 0;//若本趟没有排序就执行下一趟
		for (int i = 0; i <num; i++)
		{
			if (N->insert>M->insert)
			{
				flag = 1;
				exchage(N, M);
			}
			M = M->next;//移动
			N = N->next;
		}
		--num;
		M = P->next->next;//各移回原位
		N = P->next;
	}
}
void print(Proccess &P){
	Proccess N = P->next;//排除头结点
	do {
		if ((N->state) != 'C') // 如果该进程的状态不是 End 的话
		{
			cout << " 进程名 :" << N->name << "\t 总运行时间 :" << N->All << "\t 已运行时间 :" << N->Now << "\t 到达时间 :" << N->insert << "\t 状态 :" << N->state << endl;
			N = N->next;
		}
		else N = N->next;
	} while (N != P->next); 
}
void End(Proccess &P){
	Proccess N = P->next;//排除头结点
	do {
		if ((N->state) == 'C') // 如果该进程的状态不是 End 的话
		{
			cout << " 进程名 :" << N->name << "\t 总运行时间 :" << N->All << "\t 已运行时间 :" << N->Now << "\t 到达时间 :" << N->insert << "\t 状态 :" << N->state << endl;
			N = N->next;
		}
		else N = N->next;
	} while (N != P->next);
}
void RR(Proccess &P){
	int number = ProccessNum;//记录剩下的进程数
	int count = 0;//记录次数
	int time=0;//用于记录当前时间
	Proccess N = P->next;
	while (N->All > N->Now){//当进程尚未结束
		count++;
		cout <<"现在是第" << count <<"轮" << endl;
		if (N->state == 'R'){//若当前进程状态为就绪
			if ((N->Now + length) >= N->All){//若此进程在时间片结束后完成就更改其状态
				cout << "现在正在进行" << N->name << "进程" << endl;
				time += (N->All - N->Now);//当前时间为原时间加该进程的剩余时间
				N->Now = N->All;
				print(N);
				N->state = 'C';
				number--;
				cout << N->name << " 进程已运行结束 , 进程被删除 !" << endl;
			}
			else{//否则按顺序进行
				cout << "现在正在进行" << N->name << "进程" << endl;
				N->Now += length;
				time += length;
				print(N);
			}
		}
		if (N->state == 'N'){//若此状态为未进入，则进行判断
			if (N->insert >= (time+length))
			{//这一轮时间片过后该进程仍未进入
				cout <<  "此进程尚未到达!到下一个可执行的进程" << endl;
				print(N);
				int num = number;
				do{
					N = N->next;//测试下一个进程
					num--;
				} while ((N->insert >=(time + length)) || num > 0);//当此时有进程能进入或轮转过所有进程
				if (N->insert < (time + length))
				{//有进程能进入的情况
					cout << "此进程已到达!" << endl;
					N->state = 'R'; //让当前进程状态为就绪
					if ((N->Now + length) >= N->All){//若此进程在时间片结束后完成就更改其状态
						cout << "现在正在进行" << N->name << "进程" << endl;
						time += (N->All - N->Now);//当前时间为原时间加该进程的剩余时间
						N->Now = N->All;
						print(N);
						N->state = 'C';
						number--;
						cout << N->name << " 进程已运行结束 , 进程被删除 !" << endl;
					}
					else{//否则按顺序进行
						cout << "现在正在进行" << N->name << "进程" << endl;
						if ((length+time) - N->insert > length){//若在之前的时间片，由于顺序问题无法进入，让运行时间变为这一轮的时间片长度
							N->Now = N->Now+length;
							time += length;
							print(N);
						}
						else{//直接进入
							N->Now = N->Now + ((length+time) - N->insert);
							time += length;//无论此进程在该时间片的哪里进入，时间都是增加一个时间片
							print(N);
						}
					}
				}
			}
			else{//有进程能进入的情况
				cout << "此进程已到达!" << endl;
				N->state = 'R';//让当前进程状态为就绪
				if ((N->Now + length) >= N->All){//若此进程在时间片结束后完成就更改其状态
					cout << "现在正在进行" << N->name << "进程" << endl;
					time += (N->All - N->Now);//当前时间为原时间加该进程的剩余时间
					N->Now = N->All;
					print(N);
					N->state = 'C';
					number--;
					cout << N->name << " 进程已运行结束 , 进程被删除 !" << endl;
				}
				else{//否则按顺序进行
					cout << "现在正在进行" << N->name <<"进程"<< endl;
					if ((length*count) - N->insert > length){//若在之前的时间片，由于顺序问题无法进入，让运行时间变为这一轮的时间片长度
						N->Now=N->Now+length;
						time += length;
						print(N);
					}
					else{//直接进入
						N->Now = N->Now + ((length*count) - N->insert);//让当前时间减去进入时间为运行时间
						time += length;
						print(N);
					}
				}
			}
		}
		N = N->next;//到下一进程
		while (number&& N->All == N->Now)//若状态为已完成就跳过该进程
		{
			N = N->next;
		}
	}
}
void main() {
	Proccess H;//建立结构
	Create(H); // 初始化数据
	order(H);//将数据按到达时间排序
	print(H);//打印初始数据
	cout << "时间片轮转法开始" << endl;
	RR(H);//使用调度RR函数
	cout << "时间片轮转法结束" << endl;
	End(H);
}
