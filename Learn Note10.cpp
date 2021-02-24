#include <iostream>
#include <string>
using namespace std;

class living_things {//������
private://ֻ����ǰ�����
	string name = "";//����
	unsigned age = 0;//����
protected://ֻ����ǰ����������
	unsigned life_value = 0;//����ֵ
	unsigned attack_value = 0;//������
	unsigned defend_value = 0;//������
public://û������ �����Է���
	living_things() = default;//default��ʾ����Ĭ�ϵĹ��캯��
	living_things(string name_in) : name(name_in) {};
	virtual ~living_things() = default;//default��ʾ����Ĭ�ϵ���������
	//һ��ɼ̳��������������������麯��

	//���û��������
	void set_age(unsigned age_in) { this->age = age_in; };
	//��ȡ���������
	unsigned get_age() { return this->age; };
	//���û��������
	void set_name(string name_in) { this->name = name_in; };
	//��ȡ���������
	string get_name() { return this->name; };

	//����û������в��
	//��ͬ�������в����ͬ Ҳ������в����С������й� ���Զ�����麯��
	//��Ϊ����ϣ��ÿ���̳��ڻ���������������д�����в�����㺯��
	virtual unsigned calculate_lv() const {
		return attack_value + defend_value;
	};
};

class people : public living_things {//���� �̳��� ������
public:
	
	people(string name_in, unsigned life_value_in) { 
		this->set_name(name_in); 
		//����ֱ�ӷ���name��Ա���� ��Ϊ����private��
		//���ǿ��Է���set_name()��Ա���� ��Ϊ����public��
		this->life_value = life_value_in;
		this->attack_value = 10;
		this->defend_value = 5;
		//people�̳���living_things ��people��living_things������
		//��ôpeople���Է���living_things��public protected��Ա
	};
	
	//��д����в�����㺯��
	//���������const��ʾ �����thisָ����const��
	//Ҳ����˵ ���ڵĳ�Աֵ���������޸�
	//override��ʾϣ��������ǿ�Ƽ��ú�����û�б���д
	unsigned calculate_lv() const override{
		return life_value + attack_value + defend_value;
	};
};

int main() 
{
	living_things mode1 = living_things("mode1");
	people mode2 = people("mode2", 10);
	people mode3 = people("mode3", 20);
	cout << "Name:" << mode1.get_name() << " lv:" << mode1.calculate_lv() << endl;
	cout << "Name:" << mode2.get_name() << " lv:" << mode2.calculate_lv() << endl;
	cout << "Name:" << mode3.get_name() << " lv:" << mode3.calculate_lv() << endl;
	//get_name() �� calculate_lv() ����public�� �������������
	
	return 0;
}
