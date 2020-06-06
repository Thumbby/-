#include<iostream>
#include<time.h>
using namespace std;
int task[320];//所有指令
int pageNum = 0;//内存块被填满情况
int interrupt = 0;//缺页中断次数
int page_view = 0;//访问次数
int now_time = 0;//运行时间
typedef struct block {//内存块
	int page;
	int inTime;
	int unUsedTime;
	block* next;
}* blockList;

void arrangeTask() {//随机产生320条指令
	int flag = 0;
	srand((unsigned)time(NULL));
	int m = rand() % 320;
	for (int i = 0; i < 320; i++)
	{
		task[i] = m;
		if (flag % 2 == 0) m = m+1;
		if (flag == 1) m = rand() % (m - 1);
		if (flag == 3) m = m + 1 + (rand() % (320 - (m + 1)));
		flag = (flag++)% 4;
	}
}

int blockNum(blockList head, int page) {//当前内存块编号
	int ans = 0;
	blockList p = head;
	while (p->next != nullptr) {
		ans++;
		if (p->next->page == page) {
			break;
		}
		p = p->next;
	}
	return ans;
}

blockList WHETHER_DEFICIENCY(blockList head, int page) {//是否存在缺页中断
	blockList p;
	p = head->next;
	while(p!=nullptr){
		if (p->page == page) {//不存在缺页中断
			break;
		}
		p = p->next;
	}
	return p;
}

void print(blockList head) {//显示内存块界面
	cout << "【内存块状态】" << endl;
	cout << "----------------------------------------------" << endl;
	cout << "页码	进入时间	未使用时间" << endl;
	block* p = head->next;
	while (p!=nullptr)
	{
		cout << (p->page)+1<< "	" <<p->inTime << "		" <<p->unUsedTime<< endl;
		p = p->next;
	}
	cout << "----------------------------------------------" << endl<<endl;
}

void FIFO(blockList head, blockList temp) {//先进先出置换算法
	int min_inTime = 100000;//指令最先进入时间
	blockList p=head;
	blockList q=head;
	while (q->next != nullptr) {
		if (q->next->inTime < min_inTime) {
			min_inTime = q->next->inTime;
			p = q;
		}
		q = q->next;
	}
	temp->next = p->next->next;
	int old_page = p->next->page;
	delete p->next;
	p->next = temp;
	cout << "调用新页：第【" << (temp->page)+1 << "】页，替换第【" << old_page+1 << "】页" << endl<<endl;
}

void LRU(blockList head, blockList temp) {//最近最久未使用算法
	int max_unUsedTime = 0;//指令最大未使用时间
	blockList p = head;
	blockList q = head;
	while (q->next != nullptr) {
		if (q->next->unUsedTime > max_unUsedTime) {
			max_unUsedTime = q->next->unUsedTime;
			p = q;
		}
		q = q->next;
	}
	temp->next = p->next->next;
	int old_page = p->next->page;
	delete p->next;
	p->next = temp;
	cout << "调用新页：第【" << (temp->page) + 1 << "】页，替换第【" << old_page + 1 << "】页" << endl << endl;
}

void runOrder(blockList head, int task, int type) {//执行指令
	blockList p;
	p = WHETHER_DEFICIENCY(head, task / 10);
	if (p == nullptr) {
		cout << "发生缺页" << endl<<endl;
		interrupt++;
		p = new block;
		p->page = task / 10;
		p->inTime = now_time;
		p->unUsedTime = 0;
		if (pageNum < 4) {//内存块未被塞满
			p->next = head->next;
			head->next = p;
			pageNum++;
			cout << "调用新页：第【" << (p->page) + 1 << "】页" << endl<<endl;
		}
		else {//内存块已被塞满
			p->next = nullptr;
			if (type == 0) {
				FIFO(head, p);
			}
			if (type == 1) {
				LRU(head, p);
			}
		}
	}
	else {
		cout << "正常执行" << endl<<endl;
		cout << "该页物理地址为" << blockNum(head, p->page) << "号内存" << endl << endl;;
	}
	p->unUsedTime = 0;//内存块未使用时间重新开始计时
	p = head;
	while (p->next != nullptr) {
		p->next->unUsedTime++;
		p = p->next;
	}
}


int main() {
	arrangeTask();
	int type = 0;
	cout << "输入置换算法(0为FIFO，1为LRU)：";
	cin >> type;
	if (type != 0&&type != 1) {
		cout << "请重新输入"<<endl;
		main();
	}
	else {
		blockList head=new block;
		head->next = nullptr;
		if (type == 0) {
			cout << "使用FIFO置换算法。" << endl;
			for (int i = 0; i < 320; i++) {
				page_view++;
				now_time++;
				cout << "执行第【" << task[i] / 10 + 1 << "】页指令:" << task[i] << "		";
				runOrder(head, task[i], 0);
				print(head);
			}
			cout<< "全部指令执行完毕";
		}
		else {
			cout << "使用LRU置换算法。" << endl;
			for (int i = 0; i < 320; i++) {
				page_view++;
				now_time++;
				cout << "执行第【" << task[i] / 10 + 1 << "】页指令:" << task[i] << "		";
				runOrder(head, task[i], 1);
				print(head);
			}
			cout << "全部指令执行完毕"<<endl;
		}
	}
	double INTERRUPT = (double)interrupt / (double)page_view;
	cout << endl<<"缺页次数为：" << interrupt << endl;
	cout << "缺页率为：" << INTERRUPT<<endl;
	system("pause");
}