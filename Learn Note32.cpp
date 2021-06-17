#include <iostream>
#include <vector>
#include <functional>
using namespace std;

template<class _KeyType, class _ValueType>
class HashTable {

public:
	HashTable() : len(0) {for (size_t i = 0; i < count_bukkit; i++) { table.emplace_back(std::move(vector<pair<_KeyType, _ValueType>>())); }};
	HashTable(size_t count_bukkit_in, std::function<unsigned(_KeyType)> HashFunction_in) : count_bukkit(count_bukkit_in), HashFunction(HashFunction_in), len(0){for (size_t i = 0; i < count_bukkit; i++) { table.emplace_back(vector<pair<_KeyType, _ValueType>>()); }};
	~HashTable() {};
	
	bool empty() { return len == 0; };
	size_t size() const { return len; };
	pair<_KeyType, _ValueType> find(const _KeyType& key) const {
		if (len != 0) {
			unsigned bukkit = HashFunction(key);
			for (pair<_KeyType, _ValueType> n : table[bukkit]) {
				if (n.first == key) { return n; }
			}
		}
		return make_pair(_KeyType(), _ValueType());
	};
	void erase(_KeyType key) {
		if (len != 0) {
			unsigned bukkit = HashFunction(key);
			for (auto it = table[bukkit].begin(); it != table[bukkit].end(); it++) {
				if (it->first == key) {
					table[bukkit].erase(it);
					len--;
					break;
				}
			}
		}
	};
	void insert(pair<_KeyType, _ValueType> add_node) {
		unsigned bukkit = HashFunction(add_node.first);
		if (this->empty()) {
			table[bukkit].emplace_back(add_node);
			len++;
		}
		else {
			bool is_exist = false;
			for (pair<_KeyType, _ValueType> n : table[bukkit]) {
				if (n.first == add_node.first) {
					n.second = add_node.second;
					is_exist = true;
				}
			}
			if (!is_exist) {
				table[bukkit].emplace_back(add_node);
				len++;
			}
		}
	};

private:
	size_t len = 0;
	size_t count_bukkit = 31;
	vector<vector<pair<_KeyType, _ValueType>>> table = {};
	std::function<unsigned(_KeyType)> HashFunction = [&](const _KeyType key) {return key / count_bukkit;};
};

struct node { 
	node() = default;
	node(int data_in) : data(data_in) {}
	int data = 0; 
	bool operator==(const node& rhs) { return data == rhs.data; }
};

int main() {
	
	HashTable<node, string> table1(31, [](const node n) {return n.data / 31; });
	cout << table1.size() << endl;

	table1.insert(make_pair(node(76), "test1"));
	table1.insert(make_pair(node(34), "test2"));
	table1.insert(make_pair(node(98), "test3"));
	table1.insert(make_pair(node(84), "test4"));
	cout << table1.size() << endl;

	cout << table1.find(node(76)).second << endl;
	cout << table1.find(node(34)).second << endl;
	cout << table1.find(node(98)).second << endl;
	cout << table1.find(node(84)).second << endl;

	return 0;
}