#include <list>
using std::list;
#include <iostream>
#include <fstream>
using std::ofstream; using std::ifstream;
#include <functional>
using std::function;
#include <iterator>
void print(list<int>const& list, std::ostream& out = std::cout);

list<int>InsertionInListSort(std::string filename, int n, function<int(int)>rule = [](int n) {return n / 10; })
{
	ifstream file(filename);

	list<int> *range = new list<int>[n];
	
	int elem;

	auto emplace_by_order = [](list<int>& l, int elem, function<bool(int, int)>comp = [](int n, int m)->bool {return n < m; })
	{	
			list<int>::iterator p = l.begin();

			while (p != l.end() &&
				comp(*p, elem))
			++p;

			l.emplace(p, elem);

	};

	while (!file.eof())
	{
		file>>elem;
		emplace_by_order(range[rule(elem)], elem);
	}

	list<int>result;
	for (int i = 0; i<n; ++i)//for (int i = n-1; i>=0; --i)
	{
		
		std::cout << '[' << i << ']'; print(range[i]);

		if (range[i].size() > 0)
			result.insert(result.end(), range[i].begin(), range[i].end());
	}

	return result;
};

void print(list<int>const&list, std::ostream& out)
{
	for (int i : list)
		out << i << ' ';
	out << std::endl;
};
int main()
{
	bool IsExit(false);
	while (!IsExit)
	{
		std::cout << "Input from: ";
		std::string filename;
		std::cin >> filename;

		list<int> p = InsertionInListSort(filename,10);

		ofstream ofile("out.txt");
		std::cout << "Result: \n";
		print(p);
		std::cout << "Exit? y/n:";
		char ans; std::cin >> ans;
		IsExit = ans == 'Y' || ans == 'y' || ans == '�' || ans == '�';
	}
}