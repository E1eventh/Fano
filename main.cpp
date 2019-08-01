#include "Fano.cpp"

int main()
{
	setlocale(LC_ALL, "RUS");
	
	map<char, int> frequency;
	string text, code_text;
	int counter = 0;
	double H;
	char ch;
	
	ifstream in("text_ru.txt", ios::binary);
	int count_t = 0, count_s = 0;
	while(in.get(ch))
	{
		int trust = ch;
		if(trust != 13 && trust != 10)
		{
			text += ch;
			frequency.insert(pair<char, int>(ch, 0));
			frequency.at(ch)++;
			counter++;
		}
	}
	in.close();
	
	push_to_vector(&frequency, counter);
	fano(0, Tab.size() - 1, &Tab);
	for_each(Tab.begin(), Tab.end(), printCodeTab);
	code_text = encode(text);
	
	H = getEntropy(code_text, 1);
	cout << endl << "��� ��������� ��������: " << H << endl << endl;
	
	H = getEntropy(code_text, 2);
	cout << "��� ��� ��������: " << H << endl << endl;
	
	H = getEntropy(code_text, 3);
	cout << "��� ����� ��������: " << H << endl << endl;
	
	H = getEntropy(code_text, 4);
	cout << "��� ������� ��������: " << H << endl;
	
	int len = 0;
	double kraft = 0;
	
	
	for(int i = 0; i < Tab.size(); i++)
	{
		len = Tab[i].getCode().length();
		kraft += pow(2, 0 - len);
	}
	cout << endl << "�����: " << kraft << endl;
	cout << "�������: " << Tab.size() << " ��������" << endl; 
	
	//cout << endl << text << " - " << code_text << endl;
	
	return 0;
}
