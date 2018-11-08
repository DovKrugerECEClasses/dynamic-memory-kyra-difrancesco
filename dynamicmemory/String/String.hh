#include<cstdint>
#include <iostream>
using namespace std;


class String {
private:
	uint32_t capacity;
	uint32_t len;
	char* s;
	uint32_t stringlen(const char* str) {
		uint32_t count = 0;
		while (*str++ != '\0')
			count++;
		return count;
	}
	void checkGrow (uint32_t newLen) {
		if(newLen > capacity){
			const char* old = s;
			s = new char[2*capacity];
			for(int i = 0; i < len; i ++){
				s[i] = old[i];
			}
		}
	}
			//grow double the size of capacity--that's the efficient way
			//if new Len is even bigger than that, then you have to more than double
			//make the new s point at a chuck of memory big enough



public:
  String();
	String(const char str[]);
	String(const char str[], uint32_t cap);
	//String(const char str[], uint32_t mult);
	~String();

	//copy constructor
	String(const String& orig);
	String& operator =(const String& orig);
	char  operator [](const uint32_t pos)const;
  char& operator [](uint32_t pos);
	String operator +(const String& r);
	void operator += (const String& s);
	String substring(uint32_t p, uint32_t l);
	void replace(char a , char b);
	uint32_t length()const;
  friend ostream& operator<<(ostream& s, const String& str);

};
