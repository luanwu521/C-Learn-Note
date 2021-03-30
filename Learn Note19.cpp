#include <iostream>
using namespace std;

#ifndef LISTOVO
#define LISTOVO
#define NULL 0

//链表节点
template <typename T = int>
class List_Node {
public:
	List_Node<T>() = default;
	List_Node<T>(const T& t) : data(t) {};

	List_Node<T>* next = NULL;
	List_Node<T>* back = NULL;
	T data = NULL;

	bool operator!=(const List_Node<T>& node) const {
		return this->data != node.data || this->back != node.back || this->next != node.next;
	}
	bool operator==(const List_Node<T>& node) const {
		return this->data == node.data && this->back == node.back && this->next == node.next;
	}

};

//迭代器类型
enum iterator_type : unsigned {
	od = 0u,//顺序
	rd = 1u//逆序
};

//双向循环链表
template <typename T = int>
class List_ovo {
public:
	class List_iterator;
	typedef List_iterator iterator;
	
	List_ovo<T>() = default;
	List_ovo<T>(initializer_list<T> list_) { for (auto n : list_) { add_node(n); } }//支持列表初始化
	List_ovo<T>(const List_ovo<T>& rhs) {copy(rhs);};//拷贝构造函数
	~List_ovo<T>() {for (long i = 0; i < size; i++) this->remove_node((*this)[0]);}//析构函数
	List_ovo<T>& operator=(const List_ovo<T>& rhs) {  copy(rhs); return *this;}//重载赋值运算符

	void add_node(const T);//在链表最后端连接一个新节点
	bool remove_node(const T&);//删除指定值的节点
	void insert_node(const T, const long);//在指定位置插入一个节点
	long search_node(const T&);//搜寻指定值的节点的所在位置 返回下标
	long get_size() const { return size; }//获取链表中当前节点个数

	iterator get_begin_iter() {return List_ovo<T>::iterator(begin_node);}
	iterator get_end_iter() {return List_ovo<T>::iterator(end_node);}
	iterator get_res_begin_iter() {return List_ovo<T>::iterator(end_node->back, iterator_type::rd);}

	//下标访问
	T& operator[] (int n) {

		List_Node<T>* p = begin_node ? begin_node : 0;
		if (n < size && n >= 0) {
			int cur = 0;
			while (p && p->next) {
				if (cur == n) break;
				cur++;
				p = p->next;
			}
		}
		if(p)return p->data;
		return (*(T*)0);
		
	}

	//支持范围for
	iterator begin() const { return List_ovo<T>::iterator(begin_node); }
	iterator end() const { return List_ovo<T>::iterator(end_node); }

private:
	long size = 0;//链表中节点个数
	List_Node<T>* begin_node = NULL;//头节点
	List_Node<T>* end_node = new List_Node<T>(-1);//尾后节点
	
	void copy(const List_ovo<T>& t) {
		//考虑自赋值的情况 将数据放到一个临时链表
		
		if (size == 0) {
			if (t.size != 0) {
				List_Node<T>* cur = t.begin_node;
				while (size != t.size) {
					add_node(cur->data);
					cur = cur->next;
				}
			}
		}
		else {
			List_Node<T>* head = new List_Node<T>(t.begin_node->data);
			List_Node<T>* cur_h = head;//临时链表
			List_Node<T>* cur = t.begin_node->next;
			while(cur != t.end_node) {
				List_Node<T>* add_node = new List_Node<T>(cur->data);
				cur_h->next = add_node;
				cur_h = cur_h->next;
				cur = cur->next;
			}
			
			//删除原数据
			int k = size;
			for (long i = 0; i < k; i++) {
				this->remove_node((*this)[0]);
			} 
			
			//将临时链表中的节点加入现在链表
			cur_h = head;
			while (cur_h && cur_h->next) {
				add_node(cur_h->data);
				cur_h = cur_h->next;
			}

			//回收临时链表的内存
			cur_h = head;
			while (cur_h && cur_h->next) {
				List_Node<T>* p = cur_h;
				cur_h = cur_h->next;
				delete p;
			}

		}
		
	}

};

//链表迭代器
template <typename T>
class List_ovo<T>::List_iterator {
public:
	List_iterator() = default;
	List_iterator(List_Node<T>* p, iterator_type type_in = iterator_type::od) : cur(p), type(type_in) {};

	T& operator*() { return cur->data; }
	
	List_ovo<T>::List_iterator& operator++() {//前置递增
		this->cur = (type ? this->cur->back : this->cur->next);
		return *this;
	}
	List_ovo<T>::List_iterator operator++(int) {//后置递增
		List_ovo<T>::List_iterator p = *this;
		++*this;
		return p;
	}
	
	//迭代器的比较 实际上是比较List_Node 请查看List_Node的比较函数
	bool operator!= (List_iterator it) { return this->cur != it.cur; }
	bool equal(const List_ovo<T>::List_iterator& it) const {return this->cur == it.cur;}

private:
	List_Node<T>* cur = NULL;
	iterator_type type = iterator_type::od;
};

//=================================================================

template <typename T>
void List_ovo<T>::add_node(const T value_in) {
	//分配内存
	List_Node<T>* add_node = new List_Node<T>(value_in);
	if (size == 0) {
		begin_node = add_node;
		end_node->next = add_node;
		add_node->next = end_node;
		end_node->back = add_node;
		add_node->back = end_node;
	}
	else {
		List_Node<T>* end_back = end_node->back;
		end_back->next = add_node;
		add_node->back = end_back;

		add_node->next = end_node;
		end_node->back = add_node;
	}

	end_node->next = begin_node;
	begin_node->back = end_node;
	size++;
}

template <typename T>
long List_ovo<T>::search_node(const T& value_in) {
	long i = 0;
	for (; i < this->size; i++) {
		if ((*this)[i] == value_in) break;
	}
	return i < this->size ? i : -1;
}

template <typename T>
bool List_ovo<T>::remove_node(const T& value_in) {
	
	List_Node<T>* cur = begin_node;
	bool ret_val = false;

	List_Node<T>* del_back = NULL;
	List_Node<T>* del = NULL;
	List_Node<T>* del_next = NULL;

	while (cur && cur->next) {
		if (cur->data == value_in) {
			del_back = cur->back;
			del = cur;
			del_next = cur->next;

			del_back->next = del_next;
			del_next->back = del_back;
			if (del == begin_node) begin_node = del_next;

			delete del;
			size--;
			ret_val = true;
			break;
		}
		cur = cur->next;
	}
	return ret_val;
}

template <typename T>
void List_ovo<T>::insert_node(const T value_in, const long pos) {
	
	//根据所给位置判断从头向后遍历还是从尾向前遍历
	List_Node<T>* cur = (pos <= (size / 2 - 1) && pos < size && pos >= 0 ? begin_node : end_node->back);
	List_Node<T>* add_node = new List_Node<T>(value_in);
	if (pos == 0) {
		
		begin_node->back = add_node;
		end_node->next = add_node;
		add_node->next = begin_node;
		add_node->back = end_node;
		begin_node = add_node;
		size++;
	}
	else {

		if (cur == begin_node) {
			for (long i = 0; i != pos - 1; i++) cur = cur->next;
		}
		else {
			for (long i = size - 1; i != pos - 1; i--) cur = cur->back;
		}

		List_Node<T>* cur_next = cur->next;
		cur->next = add_node;
		add_node->back = cur;
		add_node->next = cur_next;
		cur_next->back = add_node;
		size++;
	}
	
}

template <typename U>
using List = List_ovo<U>;

#endif

int main() {
	
	cout << "sizeof:" << sizeof(List_ovo<int>) << endl;
	List_ovo<int> ls = {111, 222, 333};//使用列表初始化
	
	for (int i = 0; i < 10; i++) {
		ls.add_node(i * 100);
	}

	List_ovo<int> ls2(ls);//调用拷贝构造函数

	cout << "ls size:" << ls.get_size() << endl;
	for (int i = 0; i < ls.get_size(); i++) {
		cout << ls[i] << " ";
	}
	cout << endl;

	ls.remove_node(0);
	ls.remove_node(600);
	ls.remove_node(900);

	cout << "ls size:" << ls.get_size() << endl;
	for (int i = 0; i < ls.get_size(); i++) {
		cout << ls[i] << " ";
	}
	cout << endl;

	ls.insert_node(0, 5);

	cout << "迭代器遍历ls:" << endl;
	List_ovo<int>::iterator it;
	for (it = ls.get_begin_iter(); !it.equal(ls.get_end_iter()); it++) {
		cout << *it << " ";
	}
	cout << endl;

	cout << "迭代器遍历ls2:" << endl;
	auto it2 = ls2.get_begin_iter();
	for (; !it2.equal(ls2.get_end_iter()); it2++) {
		cout << *it2 << " ";
	}
	cout << endl;

	cout << "迭代器逆序遍历ls2:" << endl;
	auto it3 = ls2.get_res_begin_iter();
	for (; !it3.equal(ls2.get_end_iter()); it3++) {
		cout << *it3 << " ";
	}
	cout << endl;

	List_ovo<int> ls3 = ls2;//使用重载的赋值运算符
	cout << "迭代器遍历ls3:" << endl;
	auto it4 = ls3.get_begin_iter();
	for (; it4 != ls3.get_end_iter(); it4++) {
		cout << *it4 << " ";
	}
	cout << endl;


	cout << "范围for遍历ls3:" << endl;
	for (auto v : ls3) {
		cout << v << " ";
	}
	cout << endl;


	List_ovo<long> ls4;
	for (long g = 0; g < 1000000; g++) {//数据量足够大时
		ls4.add_node(g);
	}
	clock_t start, finish;
	long pos = 400000;//插入位置
	start = clock();
	ls4.insert_node(666, pos);
	finish = clock();
	cout << "time:" << finish - start << endl;//计算优化方案的插入时间
	cout << "node:" << ls4[pos] << endl;
	cout << "ls4 size:" << ls4.get_size() << endl;

	List_ovo<int> ls5 = {213, 3435, 56856, 1242, 34534};
	ls2 = ls5;
	cout << "范围for遍历ls2:" << endl;
	for (auto v : ls2) {
		cout << v << " ";
	}
	cout << endl;
	return 0;
}