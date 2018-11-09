/*
	 Author: Kyra DiFrancesco
*/
#include "String.hh"
#include <iostream>
#include <cstring>
using namespace std;

String::String() : len(0), capacity(0), s(nullptr) {
}

String::String(const char str[]) : len(stringlen(str)), s(new char [len]) {
	for(int i = 0; i < len; i++)
		s[i] = str[i];
}

//try to make this : String (stringlen(str),new char [len])
String::String(const char str[], uint32_t cap) : len(stringlen(str)), capacity(cap), s(new char [cap]) {
	for(int i = 0; i < len; i++)
		s[i] = str[i];
}

// String::String(const char str[], uint32_t mult) : len(strlen(str) * mult) , s(new char [len]){
// 	uint32_t strsize = len / mult;
// 	int c = 0;
// 	for (int j = 0; j < mult; j++)
// 		for (int i = 0; i < strsize; i++,c++)
// 			s[c] = str[i];
// }

String::~String() {
	delete [] s;
	//delete [] sub;
}

	//copy constructor
String::String(const String& orig) : len(orig.len), s(new char[len]) {
	uint64_t* src = (uint64_t*)orig.s; //because s was originally char
	uint64_t* dest = (uint64_t*)s;
	uint32_t count;
	for(count = orig.len; count >= 8; count -= 8)  //count 8 at a time
		*dest++ = *src++; //8 bytes at once (bc 64 bit pointers)
	//handle the rest after divisible by 8
	char* pdest = (char*)dest;
	char* psrc = (char*)src;
	for(; count > 0; count --)
		*pdest++ = *psrc++;
}


void String::operator += (const String& str){
	//write the code to append s to the end of your string
	checkGrow(len + str.len);
	uint32_t oldlen = len;
	len = oldlen + str.len;
	int c  = 0;
	for(int i = oldlen; i < len; i ++,c++) {
		s[i] = str[c];
	}
}


String& String::operator =(const String& orig) {
	String copy(orig); //calling copy constructor, don't need to call the variable copy
	len = orig.len;
	swap(s,copy.s);
	return *this; //return what this is pointing to
}

char String::operator [](const uint32_t pos)const {
	return s[pos];
}
char& String::operator [](uint32_t pos) {
	return s[pos];
}

//can we return by reference? need move constructor?
//String s5 = s2 + s3;
String String::operator +(const String& r){
	uint32_t sumLen = len + r.len;
	char sum[sumLen];
	for(int i = 0; i < len; i++)
		sum[i] = s[i];
	int c = 0;
	for(int j = len; j < sumLen; j++,c++)
		sum[j] = r.s[c];
	String ans(sum);
	return ans;
}

//String s4 = s3.substring(3, 2); // from position 3 length 2
//can't return by reference unless i make a move constructor?
String String::substring(uint32_t p, uint32_t l) {
	char sub[l];
	int c = 0;
	for(int i = p; i < p+l; i++,c++){
		sub[c] = s[i];
	}
	sub[l] = '\0';
	String ans (sub);
	return ans;

}

void String::replace(char a , char b) {
	for(int i = 0; i < len; i++){
		if(s[i] == a)
			s[i] = b;
	}
}

uint32_t String::length() const{
	return len;
}

ostream& operator<<(ostream& s, const String& str) {
	for(uint32_t i = 0; i < str.len; i++)
		s << str[i];
	return s;
}
