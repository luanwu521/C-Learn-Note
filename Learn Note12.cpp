#include <iostream>
using namespace std;

class A {//定义一个基类A
	friend class E;//定义友元
public:
	int a1;
protected:
	int a2;
private:
	int a3;
};

class B : public A{//B以public方式继承A A中的成员访问权限都不变
public:
	int f1() {
		return a1;
	}
	int f2() {
		return a2;
	}
	int f3() {
		//return a3;
		//不能访问a3 因为a3是private的
	}
};

class C : protected A {//C以protected方式继承A 那么A中除了private的成员 其他成员都是protected的
public:
	int f1() {
		return a1;
	}
	int f2() {
		return a2;
	}
};

class D : private A {//D以private方式继承A 那么A的所有成员在D中都是private的
public:
	int f1() {
		return a1;
	}
	int f2() {
		return a2;
	}
	
	using A::a2;//改变a2访问权限 将a2从private改成public
	
	//using A::a3;
	//无法改变访问权限 因为连D都没有权限访问A的a3
	//一个类只能改变自己有权限访问的成员的访问权限
};

class E : public A {
public:
	//E是A的友元 A中的所有成员E都可以访问
	int f1() {
		return a1;
	}
	int f2() {
		return a2;
	}
	int f3() {
		return a3;
		//即便a3在A中是private的 也可以访问
	}
};

class F : public D {
public:
	//D的a1和a3都是private的 只有a2是public的 所以只能访问a2
	int f1() {
		//return a1;
		//a1在A中是public的 但是在D中就变成了private
		//a1在D中变成private的原因是:D以private方式继承A
		//所以a1在F中是无法访问的 因为F是直接继承D而不是直接继承A
	}
	int f2() {
		return a2;
		//在D中a2是public的 所以可以访问
	}
	
};

class G : public E {//G以public继承E
public:
	int f1() {
		return a1;
	}
	int f2() {
		return a2;
	}
	int f3() {
		//return a3;
		//无法访问a3 因为a3在A中是private的
		//E可以访问a3是因为E是A的友元
		//但G不是A的友元 所以不能访问A的private成员
		//这也说明 友元是不可继承的 
		//尽管G继承自E E是A的友元不代表G(继承自E)就也是A的友元
	}
};

int main()
{

	return 0;
}