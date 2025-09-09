#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <unordered_map>
#include <map>
#include "DFA.h"
using namespace std;

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




void str_generator(int len,int target,std::string&path,std::vector<std::string>& ans)
{
    if(len==target)
    {
        ans.push_back(path);
        return;
    }
    path+='0';
    str_generator(1+len,target,path,ans);
    path.pop_back();
    path+='1';
    str_generator(1+len,target,path,ans);
    path.pop_back();
}

void str_generator_2_one(int len,int count,int target,std::string&path,std::vector<std::string>& ans)
{
    if(len==target)
    {
        ans.push_back(path);
        return;
    }
    path+='0';
    str_generator_2_one(1+len,count,target,path,ans);
    path.pop_back();
    if(count!=0)
	{
		path+='1';
		str_generator_2_one(1+len,count-1,target,path,ans);
		path.pop_back();
	}
}

void str_generator_exactly_N_one(int len,int count,int target,std::string&path,std::vector<std::string>& ans)
{
    if(len==target)
    {
        if(count==0)ans.push_back(path);
        return;
    }
    path+='0';
    str_generator_exactly_N_one(1+len,count,target,path,ans);
    path.pop_back();
    if(count!=0)
	{
		path+='1';
		str_generator_exactly_N_one(1+len,count-1,target,path,ans);
		path.pop_back();
	}
}

int get0num(string&s)
{
	int sum=0;
	int i=0;
	while(s[i++]!='1') sum++;
	return sum;
}






int max_state_estimate(int len,int statenum)
{
	std::ofstream ofs;
	ofs.open("N"+to_string(len)+" "+to_string(statenum)+"state Mod_Result.txt"); 
	ofs<<"The following tuples need to be separated by "<<statenum<<" states according to mod, but some of them can be separated by fewer states"<<endl;
	vector<int> nums;
	for(int i=0;i<len;i++) nums.push_back(i);
	int res=0;
	for(int i=0;i<nums.size();i++)
	{
		for(int j=i+1;j<nums.size();j++)
		{
			for(int k=j+1;k<nums.size();k++)
			{
				int temp=1;
				int n1=nums[i],n2=nums[j],n3=nums[k];
				while(n1%temp==n2%temp||n1%temp==n3%temp||n2%temp==n3%temp)
				{
					temp++;
				}
				if(temp==statenum) ofs<<n1<<" "<<n2<<" "<<n3<<endl;

				res=max(res,temp);
			}
		}
	}
	cout<<"The estiamted max state for length "<<len<<" is: "<<res<<endl;
	return res;
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

	// max_state_estimate(12,7);
	// return 0;


	
	cout<<"Enter string length"<<endl;
	int str_len=14;
	
	DFA m;
	size_t val;
	std::ofstream ofs;
	ofs.open("N"+to_string(str_len)+"_Result.txt"); 
	vector<string> N;
	
	//  N.push_back("00000000000000000000000000000010000");
	//  N.push_back("00000000000000000000100000000000000");
	//  N.push_back("00100000000000000000000000000000000");
	// N.push_back("10000");
	// N.push_back("01000");
	// N.push_back("00010");


	std::string path="";
	//str_generator(0,str_len,path,N);
	str_generator_exactly_N_one(0,1,str_len,path,N);
	int maxstate=-1;
	cout<<N.size()<<endl;
	
	
	// for (auto e : N)
	// {
	// 	std::cout << e << std::endl;
	// }

	ofs << "str1" << '\t' << '\t' << "str2" << '\t' << '\t' << "str3" << '\t' << '\t' << "val1" << '\t' << "val2" << '\t' << "val3" << '\t' << "dist" << '\t' << "result" << '\t' << '\t' << "val" << std::endl;
	int count=0;
	int countof5=0;

	unordered_map<std::string,int> worstcase_counter;

	//int totalpair=0;
	for (int i = 0; i < N.size(); i++)
	{
		for (int j = i + 1; j < N.size(); j++)
		{
			for (int k = j + 1; k < N.size(); k++)
			{
				//totalpair++;
				//std::cout << N[i] << '\t' << N[j] << '\t' << N[k] << '\t' << i << '\t' << j << '\t' << k << std::endl;
				m = find_result(N[i], N[j], N[k], val);

				maxstate=max(maxstate,(int)m.size);
				if(m.size==5)
				{
					//cout<<N[i] << '\t' << N[j] << '\t' << N[k] << '\t' << i << '\t' << j << '\t' << k << '\t' << m.size << '\t'<<endl;
					count++;

					// int x=0,y=0,z=0;
					// for(int q=0;q<str_len;q++)
					// {
					// 	if(N[i][q]=='1')x++;
					// 	if(N[j][q]=='1')y++;
					// 	if(N[k][q]=='1')z++;
					// }
					// int maximum = std::max(std::max(x, y), z);
    				// int minimum = std::min(std::min(x, y), z);
					// int middle = x + y + z - maximum - minimum;
					// std::string temp=to_string(minimum)+'*'+to_string(middle)+'*'+to_string(maximum);
					//string temp="1*1*1";
					// worstcase_counter[temp]++;

					ofs << N[i] << '\t' << N[j] << '\t' << N[k] << '\t' << i << '\t' << j << '\t' << k << '\t' << m.size << '\t';
					for (int l = m.states.size() - 1; l >= 0; l--)
					{
						ofs << m.states[l].t_1 << m.states[l].t_0;
					}
					ofs << '\t' << '\t' << val <<"----------- "<<get0num(N[i])<<"  "<<get0num(N[j])<<"  "<<get0num(N[k])<<"  "<<std::endl;
					// ofs << '\t' << '\t' << val << std::endl;
				}
			}
			
		}
	}

	

	map<int,vector<string> > mp;
	for(auto it:worstcase_counter)
	{
		mp[it.second].push_back(it.first);
	}

	for(auto it:mp)
	{
		cout<<it.first<<" : ";
		for(auto it2:it.second) cout<<it2<<" ";
		cout<<endl;
	}
	

	cout<<"The maxium state for length "<<str_len<<" is: "<<maxstate<<endl;
	cout<<"Total number of worst case is: "<<count<<endl;
	//cout<<"Total number of 5 state is:"<<countof5<<endl;
	
	return 0;
}