#include <iostream>
#include <string>
#include <memory>
using namespace std;

class living_things {//������
private:
	string name = "";
	unsigned age = 0;
protected:
	unsigned life_value = 0;
	unsigned attack_value = 0;
	unsigned defend_value = 0;
public:
	living_things() = default;
	living_things(string name_in) : name(name_in) {};
	virtual ~living_things() = default;

	void set_age(unsigned age_in) { this->age = age_in; };
	unsigned get_age() { return this->age; };
	void set_name(string name_in) { this->name = name_in; };
	string get_name() { return this->name; };

	virtual unsigned calculate_lv() const {
		return attack_value + defend_value;
	};
};
class pet : public living_things {//������
private:
	unsigned hunger_value = 0;//����ֵ
	//ÿ����̬��Ա����ֻ����һ������ ����ʵ�����˶��ٸ���Ķ��� ��̬��Ա����������Щ������
	static unsigned count;//����һ����̬��Ա����:��������
public:

	//���ø���Ĺ��캯������ʼ��ĳЩ����Ӹ���̳еĳ�Ա
	//����name��living_things��private��Ա ����ֱ�ӳ�ʼ��name
	//�����ǿ���ͨ������living_things�Ĺ��캯����ӵĳ�ʼ�������name
	pet(string name_in, unsigned life_value_in, unsigned hunger_value_in) : living_things(name_in), hunger_value(hunger_value_in){
		this->life_value = life_value_in;
		this->attack_value = 5;
		this->defend_value = 5;
		count++;//����һ���������͵�����������
	};
	
	unsigned calculate_lv() const override {
		//ͬ���� ��д��в�����㺯��
		return life_value + attack_value + defend_value - hunger_value;
	}
	
	~pet() {
		count--;//����һ���������͵ݼ���������
	}

	//����һ����̬��Ա���� ���ֺ������ܷ���thisָ��
	//��ֻ�ܷ��ʾ�̬��Ա������������̬��Ա���������ⲿ����������
	static unsigned get_count() {
		return count;//count�Ǿ�̬��Ա���� ���Ա���̬��Ա��������
	}
};

unsigned pet::count = 0;//��̬��Ա�����ĳ�ʼ�����ܷ�����Ķ�����

int main() {

	pet mode1 = pet("mode1", 10, 3);
	pet mode2 = pet("mode2", 5, 4);
	pet mode3 = pet("mode3", 15, 9);
	cout << "Name:" << mode1.get_name() << " lv:" << mode1.calculate_lv() << endl;
	cout << "Name:" << mode2.get_name() << " lv:" << mode2.calculate_lv() << endl;
	cout << "Name:" << mode3.get_name() << " lv:" << mode3.calculate_lv() << endl;
	cout << "Pet Count:" << pet::get_count() << endl;
	//��̬��Աͬ����Ȩ������ count��private�� �����ǲ��ܷ��ʵ�
	//��Ҫ֪��count��ֵ ֻ��ͨ�����ṩ��public�ӿ�get_count()��ȡ
	//��̬��Ա�ķ���ֻ��Ҫʹ�� ����+�������(::)+��Ա��

	cout << "=====================" << endl;

	living_things& mode4 = mode1;
	living_things* ptr1 = &mode2;
	cout << "Name:" << mode4.get_name() << " lv:" << mode4.calculate_lv() << endl;
	cout << "Name:" << ptr1->get_name() << " lv:" << ptr1->calculate_lv() << endl;
	//��������ʹ����living_things���͵����ú�ָ��������pet���͵Ķ���
	//ͨ������� ָ������õ����ͱ����������������ͬ
	//�����ڼ̳��������� ����һ��Ҫ������������ͬ
	//���ǿ����ø������͵�ָ������ù����������
	//�������������Թ�����������дӸ���̳е���һ����
	//������и���û�е������ǲ���ͨ���������͵�ָ������ý��й���
	shared_ptr<living_things> ptr2 = make_shared<living_things>(mode3);
	cout << "Name:" << ptr2->get_name() << " lv:" << ptr2->calculate_lv() << endl;
	//Ҳ����ʹ������ָ�������� ͬ����ѭ����������

	cout << "=====================" << endl;

	return 0;
}