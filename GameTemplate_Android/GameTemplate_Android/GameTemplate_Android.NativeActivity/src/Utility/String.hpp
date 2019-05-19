#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace Extension
{
	using namespace std; // 名前空間の継承
	namespace std
	{
		//std::stringにsplitがないので拡張してみた
		class String : public string
		{
		public:
			String() : string() {}
			String(const char *str) : string(str) {}
			String(const string &s) : string(s) {}

			String& operator=(const char *str)
			{
				string::operator=(str);
				return *this;
			}
			String& operator=(const string& s)
			{
				string::operator=(s);
				return *this;
			}

			const vector<string> split(char split)
			{
				using namespace std;
				vector<string> elems;
				string item;
				for (char ch : *this)
				{
					if (ch == split)
					{
						if (!item.empty())
						{
							elems.push_back(item);
						}
						item.clear();
					}
					else
					{
						item += ch;
					}
				}
				if (!item.empty())
				{
					elems.push_back(item);
				}
				return elems;
			}
		};

	}
}