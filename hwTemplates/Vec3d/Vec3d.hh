/*
Author: Kyra DiFrancesco
*/
#pragma once
#include <iostream>
using namespace std;

template <typename Precision>
class Vec3d {
private:
  Precision x,y,z;
public:
  Vec3d(Precision x, Precision y, Precision z) : x(x), y(y), z(z) {}
  friend Vec3d operator +(const Vec3d& a, const Vec3d& b){
    return Vec3d(a.x+b.x, a.y+b.y, a.z+b.z);
  }
  friend ostream& operator <<(ostream&s, const Vec3d& v) {
    return s << "(" << v.x << ", " << v.y << ", " << v.z << ")" << '\n';
  }

};
