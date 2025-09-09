#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include "DFA.h"

/*std::vector<std::string> N_list(int n)
{
	std::string num = "";
	std::vector<std::string> result;
	for (int i = 0; i < n; i++)
	{
		num += "0";
	}
	result.push_back(num);
	for (int i = 0; i < pow(2, n) - 1; i++)
	{
		int carry = 1;
		int index = n - 1;
		while (carry != 0)
		{
			if (num[index] == '0')
			{
				num[index] = '1';
				carry = 0;
			}
			else
			{
				num[index] = '0';
				carry = 1;
			}
			result.push_back(num);
			index--;
		}

	}
	return result;
}*/

DFA find_result(const std::string& str1, const std::string& str2, const std::string& str3, size_t& val)
{
	size_t n = 3;
	while (true)
	{
		DFA m(n);
		//std::cout << "number of states: " << n << std::endl;
		for (int i = 0; i < pow(n, 2 * n) - 1; i++)
		{
			if (m.E_seperation(str1, str2, str3))
			{
				val = i;
				return m;
			}
			m++;
			//std::cout << m.get_DFA() << std::endl;
		}
		n++;
	}
}

int main()
{
	/*DFA m;
	m.add_state({ 2,1 });
	m.add_state({ 1,0 });
	m.add_state({ 2,1 });
	m.print();
	if (m.E_seperation("00", "01", "10"))
	{
		std::cout << "yes" << std::endl;
	}*/
	DFA m;
	size_t val;
	std::ofstream ofs;
	ofs.open("N6_Result.txt");
	std::vector<std::string> N = { "000000","000001","000010","000011","000100","000101","000110","000111",
								   "001000","001001","001010","001011","001100","001101","001110","001111",
								   "010000","010001","010010","010011","010100","010101","010110","010111",
								   "011000","011001","011010","011011","011100","011101","011110","011111", 
								   "100000","100001","100010","100011","100100","100101","100110","100111",
								   "101000","101001","101010","101011","101100","101101","101110","101111",
								   "110000","110001","110010","110011","110100","110101","110110","110111",
								   "111000","111001","111010","111011","111100","111101","111110","111111", };
	for (auto e : N)
	{
		std::cout << e << std::endl;
	}

	ofs << "str1" << '\t' << '\t' << "str2" << '\t' << '\t' << "str3" << '\t' << '\t' << "val1" << '\t' << "val2" << '\t' << "val3" << '\t' << "dist" << '\t' << "result" << '\t' << '\t' << "val" << std::endl;

	for (int i = 0; i < N.size(); i++)
	{
		for (int j = i + 1; j < N.size(); j++)
		{
			for (int k = j + 1; k < N.size(); k++)
			{
				//std::cout << N[i] << '\t' << N[j] << '\t' << N[k] << '\t' << i << '\t' << j << '\t' << k << std::endl;
				m = find_result(N[i], N[j], N[k], val);
				ofs << N[i] << '\t' << N[j] << '\t' << N[k] << '\t' << i << '\t' << j << '\t' << k << '\t' << m.size << '\t';
				for (int l = m.states.size() - 1; l >= 0; l--)
				{
					ofs << m.states[l].t_1 << m.states[l].t_0;
				}
				ofs << '\t' << '\t' << val << std::endl;
			}
			
		}
	}
	
	return 0;
}