#pragma once
#include <vector>
#include <string>
#include <cassert>
#include <iostream>

//Represent a single state in DFA
struct state
{
	//Trasition from current state on input 0
	size_t t_0 = 0;

	//Trasition from current state on input 1
	size_t t_1 = 0;

	int val()
	{
		return t_0 == t_1 ? t_0 : -1;
	}
};


class DFA
{

public:

	//Constructors

	//Default Constructor
	DFA()
	{
		size = 0;
		init_state_x = 0;
		init_state_y = 0;
		final_state_x = 0;
		final_state_y = 0;
		states = std::vector<state>();
	}

	//Constructor that takes in the state number of the DFA
	DFA(size_t n)
	{
		size = n;
		init_state_x = 0;
		init_state_y = 0;
		final_state_x = 0;
		final_state_y = 0;
		for (int i = 0; i < n; i++)
		{
			states.push_back(state());
		}
	}

	DFA(const DFA& D)
	{
		size = D.size;
		init_state_x = D.init_state_x;
		init_state_y = D.init_state_y;
		final_state_x = D.final_state_x;
		final_state_y = D.final_state_y;
		for (int i = 0; i < D.states.size(); i++)
		{
			states.push_back(D.states[i]);
		}
	}

	//Accesors

	//Seperation
	//For a common start state
	//M ends in different states after reading in x and y
	bool seperation(const std::string& x, const std::string& y)
	{
		assert(x.size() == y.size());

		if (x == y)
		{
			return false;
		}

		final_state_x = init_state_x;
		final_state_y = init_state_y;
		for (int i = 0; i < x.size(); i++)
		{
			final_state_x = x[i] == '0' ? states[final_state_x].t_0 : states[final_state_x].t_1;
			final_state_y = y[i] == '0' ? states[final_state_y].t_0 : states[final_state_y].t_1;
		}

		return final_state_x == final_state_y ? false : true;
	}

	//E-Seperation
	//For some common start state
	//M ends in different states after reading in x and y
	bool E_seperation(const std::string& x, const std::string& y)
	{
		bool flag = false;
		for (int i = 0; i < size; i++)
		{
			init_state_x = i;
			init_state_y = i;
			if (seperation(x, y))
			{
				flag = true;
			}
		}

		return flag;
	}

	//A-Seperation
	//For every pair of start states
	//M ends in different states after reading x and y
	bool A_seperation(const std::string& x, const std::string& y)
	{
		bool flag = true;
		for (int i = 0; i < size; i++)
		{
			init_state_x = i;
			init_state_y = i;
			if (!seperation(x, y))
			{
				flag = false;
			}
		}

		return flag;
	}

	//A^2-Seperation
	//For every common start state
	//M ends in different states after reading x and y
	bool A2_seperation(const std::string& x, const std::string& y)
	{

		bool flag = true;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				init_state_x = i;
				init_state_y = j;
				if (!seperation(x, y))
				{
					flag = false;
				}
			}
		}

		return flag;
	}

	//A^2-01-Seperation
	//For every common start state
	//M ends in fixed different states after reading x and y
	bool A2_01_seperation(const std::string& x, const std::string& y)
	{

		bool flag = true;
		size_t fixed_x, fixed_y;

		init_state_x = 0;
		init_state_y = 0;
		seperation(x, y);
		fixed_x = final_state_x;
		fixed_y = final_state_y;

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				init_state_x = i;
				init_state_y = j;
				if (!seperation(x, y) || fixed_x != final_state_x || fixed_y != final_state_y)
				{
					flag = false;
				}
			}
		}

		return flag;
	}

	void print()
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << "State " << i << ": " << states[i].t_0 << " " << states[i].t_1 << std::endl;
		}
	}

	std::string get_DFA()
	{
		std::string s = "";
		for (int i = 0; i < size; i++)
		{
			s += char(states[i].t_0 + '0');
			s += char(states[i].t_1 + '0');
		}
		return s;
	}

	bool contain_loop()
	{
		for (int i = 0; i < size; i++)
		{
			int cur = i;
			int c = 0;
			while (c < size)
			{
				if (states[cur].val() == -1)
				{
					break;
				}
				else
				{
					cur = states[cur].val();
				}

				if (cur == i)
				{
					return true;
				}
				c++;
			}
		}
		return false;
	}

	//Modifier

	//Only used for testing
	//Add a new state to an DFA
	void add_state(state n)
	{
		states.push_back(n);
		size++;
	}

	//Increment the DFA
	DFA& operator++(int)
	{
		size_t carry = 0;
		states[0].t_0++;
		for (int i = 0; i < size; i++)
		{
			states[i].t_0 += carry;
			if (states[i].t_0 == size)
			{
				states[i].t_0 = 0;
				carry = 1;
			}
			else
			{
				carry = 0;
			}

			states[i].t_1 += carry;
			if (states[i].t_1 == size)
			{
				states[i].t_1 = 0;
				carry = 1;
			}
			else
			{
				carry = 0;
			}
		}

		return *this;
	}

public:

	//Number of states
	size_t size;

	//Initial state for x
	size_t init_state_x;

	//Initial state for y
	size_t init_state_y;

	//Final state for x
	size_t final_state_x;

	//Final state for y
	size_t final_state_y;

	//A set of states
	std::vector<state> states;

};