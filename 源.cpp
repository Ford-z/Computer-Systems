#include <iostream>
#include <cstdlib>
using namespace std;
typedef struct PNode { // PCB
	struct PNode *next; // ����ָ����һ���ڵ��ָ��
	char name[30]; // �����������������ռ�
	int All; // �趨������ʱ��
	int Now; // �趨��ǰ����ʱ��
	int insert;//�趨����ʱ��
	char state; // �������״̬ Ready / End
}*Proccess; // ָ��� PCB��ָ��
int length;//ʱ��Ƭ�ĳ���
int ProccessNum; // �ܽ��̸���
// ��ʼ����������
void Create(Proccess &P) {
	cout << "������ʱ��Ƭ�ĳ��� : " << endl;
	cin >> length;//����ʱ��Ƭ�ĳ���
	cout << "�������ܽ��̸��� : "<<endl;
	cin >> ProccessNum; // �����ܸ���
	P = (Proccess)malloc(sizeof(PNode)); // ����ͷ�ڵ�
	P->next = NULL;
	Proccess I = P; // ����һ��ָ��
	cout << "�ܽ��̸���Ϊ " << ProccessNum << " �� , ������������Ӧ��Ϣ"<<endl;
	for (int i = 1; i <= ProccessNum; i++)
	{
		I = I->next = (Proccess)malloc(sizeof(PNode));
		cout << "�����������  ������ʱ��  ����ʱ��:"<<endl;
		cin >> I->name >> I->All>>I->insert;
		I->Now = 0;
		if (I->insert == 0){
			I->state = 'R';
		}
		else{
			I->state = 'N';//����ʼʱ�䲻Ϊ0������Ϊ'N'
		}
		I->next = NULL;
	}
	I->next = P->next;
}
void exchage(Proccess &a, Proccess &b){//��������
	char name[30];
	strcpy_s(name, a->name);//�ȷ��õ��м����
	int All = a->All;
	int Now = a->Now;
	int insert = a->insert;
	char state = a->state;
	strcpy_s(a->name, b->name);//���н���
	a->All = b->All;
	a->Now = b->Now;
	a->insert = b->insert;
	a->state = b->state;
	strcpy_s(b->name, name);//���м�����ŵ�Ҫ�����ĵط�
	b->All = All;
	b->Now = Now;
	b->insert = insert;
	b->state = state;
}
void order(Proccess &P){//ʹ��������ð�����򷨽�������
	Proccess N = P->next;//�ų�ͷ���
	Proccess M = N->next;//MΪ��һ��
	int flag = 1;//��flag�����ĳһ�˳����Ƿ�������
	int num = ProccessNum-1;
	while ((num) && (flag == 1)){
		flag = 0;//������û�������ִ����һ��
		for (int i = 0; i <num; i++)
		{
			if (N->insert>M->insert)
			{
				flag = 1;
				exchage(N, M);
			}
			M = M->next;//�ƶ�
			N = N->next;
		}
		--num;
		M = P->next->next;//���ƻ�ԭλ
		N = P->next;
	}
}
void print(Proccess &P){
	Proccess N = P->next;//�ų�ͷ���
	do {
		if ((N->state) != 'C') // ����ý��̵�״̬���� End �Ļ�
		{
			cout << " ������ :" << N->name << "\t ������ʱ�� :" << N->All << "\t ������ʱ�� :" << N->Now << "\t ����ʱ�� :" << N->insert << "\t ״̬ :" << N->state << endl;
			N = N->next;
		}
		else N = N->next;
	} while (N != P->next); 
}
void End(Proccess &P){
	Proccess N = P->next;//�ų�ͷ���
	do {
		if ((N->state) == 'C') // ����ý��̵�״̬���� End �Ļ�
		{
			cout << " ������ :" << N->name << "\t ������ʱ�� :" << N->All << "\t ������ʱ�� :" << N->Now << "\t ����ʱ�� :" << N->insert << "\t ״̬ :" << N->state << endl;
			N = N->next;
		}
		else N = N->next;
	} while (N != P->next);
}
void RR(Proccess &P){
	int number = ProccessNum;//��¼ʣ�µĽ�����
	int count = 0;//��¼����
	int time=0;//���ڼ�¼��ǰʱ��
	Proccess N = P->next;
	while (N->All > N->Now){//��������δ����
		count++;
		cout <<"�����ǵ�" << count <<"��" << endl;
		if (N->state == 'R'){//����ǰ����״̬Ϊ����
			if ((N->Now + length) >= N->All){//���˽�����ʱ��Ƭ��������ɾ͸�����״̬
				cout << "�������ڽ���" << N->name << "����" << endl;
				time += (N->All - N->Now);//��ǰʱ��Ϊԭʱ��Ӹý��̵�ʣ��ʱ��
				N->Now = N->All;
				print(N);
				N->state = 'C';
				number--;
				cout << N->name << " ���������н��� , ���̱�ɾ�� !" << endl;
			}
			else{//����˳�����
				cout << "�������ڽ���" << N->name << "����" << endl;
				N->Now += length;
				time += length;
				print(N);
			}
		}
		if (N->state == 'N'){//����״̬Ϊδ���룬������ж�
			if (N->insert >= (time+length))
			{//��һ��ʱ��Ƭ����ý�����δ����
				cout <<  "�˽�����δ����!����һ����ִ�еĽ���" << endl;
				print(N);
				int num = number;
				do{
					N = N->next;//������һ������
					num--;
				} while ((N->insert >=(time + length)) || num > 0);//����ʱ�н����ܽ������ת�����н���
				if (N->insert < (time + length))
				{//�н����ܽ�������
					cout << "�˽����ѵ���!" << endl;
					N->state = 'R'; //�õ�ǰ����״̬Ϊ����
					if ((N->Now + length) >= N->All){//���˽�����ʱ��Ƭ��������ɾ͸�����״̬
						cout << "�������ڽ���" << N->name << "����" << endl;
						time += (N->All - N->Now);//��ǰʱ��Ϊԭʱ��Ӹý��̵�ʣ��ʱ��
						N->Now = N->All;
						print(N);
						N->state = 'C';
						number--;
						cout << N->name << " ���������н��� , ���̱�ɾ�� !" << endl;
					}
					else{//����˳�����
						cout << "�������ڽ���" << N->name << "����" << endl;
						if ((length+time) - N->insert > length){//����֮ǰ��ʱ��Ƭ������˳�������޷����룬������ʱ���Ϊ��һ�ֵ�ʱ��Ƭ����
							N->Now = N->Now+length;
							time += length;
							print(N);
						}
						else{//ֱ�ӽ���
							N->Now = N->Now + ((length+time) - N->insert);
							time += length;//���۴˽����ڸ�ʱ��Ƭ��������룬ʱ�䶼������һ��ʱ��Ƭ
							print(N);
						}
					}
				}
			}
			else{//�н����ܽ�������
				cout << "�˽����ѵ���!" << endl;
				N->state = 'R';//�õ�ǰ����״̬Ϊ����
				if ((N->Now + length) >= N->All){//���˽�����ʱ��Ƭ��������ɾ͸�����״̬
					cout << "�������ڽ���" << N->name << "����" << endl;
					time += (N->All - N->Now);//��ǰʱ��Ϊԭʱ��Ӹý��̵�ʣ��ʱ��
					N->Now = N->All;
					print(N);
					N->state = 'C';
					number--;
					cout << N->name << " ���������н��� , ���̱�ɾ�� !" << endl;
				}
				else{//����˳�����
					cout << "�������ڽ���" << N->name <<"����"<< endl;
					if ((length*count) - N->insert > length){//����֮ǰ��ʱ��Ƭ������˳�������޷����룬������ʱ���Ϊ��һ�ֵ�ʱ��Ƭ����
						N->Now=N->Now+length;
						time += length;
						print(N);
					}
					else{//ֱ�ӽ���
						N->Now = N->Now + ((length*count) - N->insert);//�õ�ǰʱ���ȥ����ʱ��Ϊ����ʱ��
						time += length;
						print(N);
					}
				}
			}
		}
		N = N->next;//����һ����
		while (number&& N->All == N->Now)//��״̬Ϊ����ɾ������ý���
		{
			N = N->next;
		}
	}
}
void main() {
	Proccess H;//�����ṹ
	Create(H); // ��ʼ������
	order(H);//�����ݰ�����ʱ������
	print(H);//��ӡ��ʼ����
	cout << "ʱ��Ƭ��ת����ʼ" << endl;
	RR(H);//ʹ�õ���RR����
	cout << "ʱ��Ƭ��ת������" << endl;
	End(H);
}