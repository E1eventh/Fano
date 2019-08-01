#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

#define ll long long

using namespace std;

class CodeTab 
{
	private:
	   	char symbol;
	   	string code;
	   	double p;
	   
	public:
	   	CodeTab(char symbol, double p);
	   	void addCode(string code);
	   	char getSymbol();
	   	double getFrequency();
	   	string getCode();
};

CodeTab::CodeTab(char symbol, double p) 
{
   	this->symbol = symbol;
   	this->p = p;
   	code = "";
}

char CodeTab::getSymbol() 
{
   	return symbol;
}

double CodeTab::getFrequency() 
{
   	return p;
}

string CodeTab::getCode() 
{
   	return code;
}

void CodeTab::addCode(string code) 
{
   	this->code += code;
}

void printCodeTab(CodeTab tab) {
   cout << "Symbol: " << tab.getSymbol();
   cout << " Freq: " << tab.getFrequency();
   cout << " Code: " << tab.getCode() << endl;
}

vector<CodeTab> Tab;

void fano(int begin, int end, vector<CodeTab> *tab) 
{
   	if (begin >= end) 
	{
      	return;
   	}

   	if (begin == end - 1) 
	{
      	tab->at(begin).addCode("0");
      	tab->at(end).addCode("1");
      	return;
   	}

   	int highPtr = begin; 
   	int lowPtr = end;
   	double highSum = tab->at(highPtr).getFrequency();
   	double lowSum = tab->at(lowPtr).getFrequency();

   	while (highPtr != lowPtr - 1) {
      	if (highSum > lowSum) 
		{
         	lowPtr --;
         	lowSum += tab->at(lowPtr).getFrequency();
      	} 
		else 
		{
         	highPtr ++;
         	highSum += tab->at(highPtr).getFrequency();
      	}
   }

   for (int i = begin; i <= highPtr; i++) 
   {
      	tab->at(i).addCode("0");
   }
   for (int i = lowPtr; i <= end; i++) 
   {
      	tab->at(i).addCode("1");
   }

   fano(begin, highPtr, tab);
   fano(lowPtr, end, tab);
}

void push_to_vector(map<char, int> *frequency, int counter)
{
	map<char,int>::iterator it;
	vector<CodeTab>::iterator jt; 
	double P;
	
	for(it = frequency->begin(); it != frequency->end(); it++)
	{
		P = (double) it->second / (double) counter;
		if(Tab.empty())
		{
			CodeTab newTab(it->first, P);
			Tab.push_back(newTab);
		}
		
		else
		{
			jt = Tab.begin();
			for(int j = 0; j < Tab.size(); j++)
			{
				if(P >= Tab[j].getFrequency())
				{
					CodeTab newTab(it->first, P);
					Tab.insert(jt, newTab);
					break;
				}
				else if(j == Tab.size() - 1)
				{
					CodeTab newTab(it->first, P);
					Tab.push_back(newTab);
					break;
				}
				jt++;
			}
		}
	}
}

string encode(string text)
{
	string code;
    for(int i = 0; i < text.size(); i++)
	{
		for(int j = 0; j < Tab.size(); j++)
		{
			if(Tab[j].getSymbol() == text[i])
			{
				code += Tab[j].getCode();
				j = Tab.size();
			}
		}
	}
	return code;	
}

double getEntropy(string code_text, int symb)
{
	map<string, int> count;
	map<string, int>::iterator it;
	string temp;
	int size = code_text.size();
	double H = 0, P = 0;	
	
	for(int i = 0; i < size; i++)
	{
		temp += code_text[i];
		if(temp.size() < symb)
			continue;
		count.insert(pair<string, int>(temp, 0));
		count.at(temp)++;
		temp = temp.substr(1);
	}
	
	for(it = count.begin(); it != count.end(); it++)
	{
		P = (double) it->second / (double) (code_text.size() - (symb - 1));
		H += P * (log10(1 / P) / log10(2));
	}
	
	H /= symb;
		
	return H;
}
