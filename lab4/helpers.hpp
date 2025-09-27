#pragma once

#include <string>
#include <iostream>
#include <type_traits>
#include <stack>
#include <queue>
#include <deque>


template <class T>
void pr(T& v, std::string s)
{
	std::cout << "\n\n\t" << s << "  # Sequence:\n";

	typename T::iterator p;

	int i;

	for (p = v.begin(), i = 0; p != v.end(); p++, i++)
		std::cout << '\n' << i + 1 << ". " << *p;
	std::cout << '\n';
}

template<typename Container>
void printContainer(Container c) {
	if constexpr (std::is_same_v<Container, std::stack<typename Container::value_type>>) {
		while (!c.empty()) {
			std:: cout << c.top() << " ";
			c.pop();
		}
	}
	else if constexpr (std::is_same_v<Container, std::queue<typename Container::value_type>>) {
		while (!c.empty()) {
			std::cout << c.front() << " ";
			c.pop();
		}
	}
	else if constexpr (std::is_same_v<Container, std::priority_queue<typename Container::value_type>>) {
		while (!c.empty()) {
			std::cout << c.top() << " ";
			c.pop();
		}
	}
	std::cout << std::endl;
}
