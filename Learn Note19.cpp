#include <iostream>
using namespace std;

//����ڵ�
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


//˫��ѭ������
template <typename T = int>
class List_ovo {
public:
	class List_iterator;
	typedef List_iterator iterator;

	List_ovo<T>() = default;
	List_ovo<T>(const List_ovo<T>& t) {//�������캯��
		if (t.size != 0) {
			List_Node<T>* cur = t.begin;
			while (size != t.size) {
				add_node(cur->data);
				cur = cur->next;
			}
		}
		
	};
	~List_ovo<T>() = default;

	void add_node(const T&);//��������������һ���½ڵ�
	bool remove_node(const T&);//ɾ��ָ��ֵ�Ľڵ�
	void insert_node(const T&, const int);//��ָ��λ�ò���һ���ڵ�
	int search_node(const T&);//��Ѱָ��ֵ�Ľڵ������λ�� �����±�

	int get_size() const { return size; }//��ȡ�����е�ǰ�ڵ����

	iterator get_begin_iter() {//��ȡͷ������
		return List_ovo<T>::iterator(begin);
	}
	iterator get_end_iter() {//��ȡβ�������
		return List_ovo<T>::iterator(end);
	}

	T& operator[] (int n) {

		List_Node<T>* p = begin ? begin : 0;
		if (n < size && n >= 0) {
			int cur = 0;
			while (p && p->next) {
				if (cur == n) break;
				cur++;
				p = p->next;
			}
		}
		if(p)return p->data;
		
	}

private:
	int size = 0;//�����нڵ����
	List_Node<T>* begin = NULL;//ͷ�ڵ�
	List_Node<T>* end = new List_Node<T>(-1);//β��ڵ�
	
};

//���������
template <typename T>
class List_ovo<T>::List_iterator {
public:
	List_ovo<T>::List_iterator() = default;
	List_ovo<T>::List_iterator(List_Node<T>* p) : cur(p) {};

	T& operator*() { return cur->data; }
	
	List_ovo<T>::List_iterator& operator++() {//ǰ�õ���
		this->cur = this->cur->next;
		return *this;
	}
	List_ovo<T>::List_iterator operator++(int) {//���õ���
		List_ovo<T>::List_iterator p = *this;
		++*this;
		return p;
	}
	
	bool equal(const List_ovo<T>::List_iterator& it) const {return this->cur == it.cur;}

private:
	List_Node<T>* cur = NULL;
};

//=================================================================

template <typename T>
void List_ovo<T>::add_node(const T& value_in) {
	List_Node<T>* add_node = new List_Node<T>(value_in);
	if (size == 0) {
		begin = add_node;
		end->next = add_node;
		add_node->next = end;
		end->back = add_node;
		add_node->back = end;
	}
	else {
		List_Node<T>* end_back = end->back;
		end_back->next = add_node;
		add_node->back = end_back;

		add_node->next = end;
		end->back = add_node;
	}

	end->next = begin;
	begin->back = end;
	size++;
}

template <typename T>
int List_ovo<T>::search_node(const T& value_in) {
	int i = 0;
	for (; i < this->size; i++) {
		if ((*this)[i] == value_in) break;
	}
	return i < this->size ? i : -1;
}

template <typename T>
bool List_ovo<T>::remove_node(const T& value_in) {
	
	List_Node<T>* cur = begin;
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
			if (del == begin) begin = del_next;

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
void List_ovo<T>::insert_node(const T& value_in, int pos) {
	
	//��������λ���жϴ�ͷ���������Ǵ�β��ǰ����
	List_Node<T>* cur = ((pos <= (size / 2 - 1) && pos < size) && pos >= 0 ? begin : end->back);
	List_Node<T>* add_node = new List_Node<T>(value_in);
	if (pos == 0) {
		
		begin->back = add_node;
		end->next = add_node;
		add_node->next = begin;
		add_node->back = end;
		begin = add_node;
		size++;
	}
	else {

		if (cur == begin) {
			for (int i = 0; i != pos - 1; i++) {
				cur = cur->next;
			}
		}
		else {
			for (int i = size - 1; i != pos - 1; i--) {
				cur = cur->back;
			}
		}

		List_Node<T>* cur_next = cur->next;
		cur->next = add_node;
		add_node->back = cur;
		add_node->next = cur_next;
		cur_next->back = add_node;
		size++;
	}
	
}


int main() {
	
	cout << "sizeof:" << sizeof(List_ovo<int>) << endl;
	List_ovo<int> ls;
	
	for (int i = 0; i < 10; i++) {
		ls.add_node(i * 100);
	}

	List_ovo<int> ls2(ls);

	cout << "size:" << ls.get_size() << endl;
	for (int i = 0; i < ls.get_size(); i++) {
		cout << ls[i] << " ";
	}
	cout << endl;

	ls.remove_node(0);
	ls.remove_node(600);
	ls.remove_node(900);

	cout << "size:" << ls.get_size() << endl;
	for (int i = 0; i < ls.get_size(); i++) {
		cout << ls[i] << " ";
	}
	cout << endl;

	ls.insert_node(0, 5);

	cout << "����������ls:" << endl;
	List_ovo<int>::iterator it;
	for (it = ls.get_begin_iter(); !it.equal(ls.get_end_iter()); it++) {
		cout << *it << " ";
	}
	cout << endl;

	cout << "size:" << ls2.get_size() << endl;
	for (int i = 0; i < ls2.get_size(); i++) {
		cout << ls2[i] << " ";
	}
	cout << endl;

	cout << "����������ls2:" << endl;
	List_ovo<int>::iterator it2;
	for (it2 = ls2.get_begin_iter(); !it2.equal(ls2.get_end_iter()); it2++) {
		cout << *it2 << " ";
	}
	cout << endl;

	return 0;
}