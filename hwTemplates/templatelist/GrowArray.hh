/*
	Author: Kyra DiFrancesco
*/
#pragma once

#include <iostream>


template<typename T>
class GrowArray {
private:
	int used;
	int capacity;
	T* data;
	void checkGrow() {
		if(capacity == 1 && used == 0){
			data = new T[capacity];
		}
		if (used < capacity){
			used++;
			return; // don't grow unless you have to
		}
		T* old = data;
		//TODO: every time the list grows, double it!!!
		//data = new T[used+1]; // calls T::T()
		capacity *= 2;
		data = new T[capacity];
		for (int i = 0; i < used; i++)
			data[i] = old[i];
		used++;
	}
public:
	GrowArray() : used(0), capacity(1), data(nullptr) {}
	GrowArray(int  initialCapacity): used(0), capacity(initialCapacity), data(new T[capacity] ) {
			}
	~GrowArray() {
		delete [] data;
	}
	GrowArray(const GrowArray& orig) : used(orig.used), capacity(orig.capacity), data(new T[capacity]){
		// for(int i = 0; i < used; i++)
		// 	data[i] = orig.data[i];
		memcpy(data,orig.data,orig.capacity);
	}
	GrowArray& operator =(const GrowArray& orig) {
		GrowArray copy(orig);
		used = orig.used;
		capacity = orig.capacity;
		swap(data,orig.data);
		return *this;
	}

	void addEnd(const T& v) {
		checkGrow();
		data[used-1] = v;
	}

	T removeEnd() {
    used--;
		return data[used];
	}
	T operator [](int i) const {
		return data[i];
	}

	T& operator [](int i) {
		return data[i];
	}

	friend std::ostream& operator <<(std::ostream& s, const GrowArray<T>& list) {
    for (int i = 0; i < list.used; i++)
			s << list[i] << ' ';
		return s;
	}
};
