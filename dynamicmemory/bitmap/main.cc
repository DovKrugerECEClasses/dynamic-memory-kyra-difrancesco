/*
	 Author: Kyra DiFrancesco
*/
#include <iostream>
//#include "Color.hh"
#include <iomanip>
using namespace std;

class Color {
private:
  uint32_t rgba;
public:
	Color(){
    rgba = 0;
  }
	Color(uint8_t r, uint8_t g, uint8_t b) {
		if (r == 255 && g == 0 && b == 0)
      rgba = 1;
    else if (r == 0 && g == 0 && b == 255)
      rgba = 2;
    else if (r == 0 && g == 255 && b == 0)
      rgba = 3;
    else if (r == 255 && g == 255 && b == 255)
      rgba = 4;
    else if (r == 0 && g == 0 && b == 0)
      rgba = 5;
  }

  friend ostream& operator << (ostream& s, Color c){
    if(c.rgba == 0)
      return s << " ";
    if(c.rgba == 1)
      return s << "R";
    if(c.rgba == 2)
      return s << "B";
    if(c.rgba == 3)
      return s << "G";
    if(c.rgba == 4)
      return s << "W";
    if(c.rgba == 5)
      return s << "Bl";
  }


	//TODO:	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) {}

};

class Bitmap{
private:
	uint32_t width;
	uint32_t height;
	Color** p;
public:
	Bitmap(uint32_t w, uint32_t h) : width(w), height(h), p(new Color*[width]) {
		for(int i = 0; i < width; i++)
			p[i] = new Color [height];
	}

	~Bitmap(){
		delete [] p;
	}

	void line (uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Color& c) {
		double slope = 0;
		slope = (y1-y0)/(x1-x0);
		if(slope == 1 || slope == -1){
			for(int i = x0; i <= x1; i++)
				for(int j = y0; j <= y1; j++){
					if(i==j)
						p[i][j] = c;
				}
		}
		else {
			int m_new = 2 * (y1 - y0);
			int slopeErr = m_new - (x1 - x0);
			for (int x = x0, y = y0; x <= x1; x++){
			 	p[x][y] = c;
				slopeErr += m_new;
				if (slopeErr >= 0) {
					y++;
					slopeErr  -= 2 * (x1 - x0);
			 	}
		 }
		}
	} //end of line

  void horizLine(uint32_t x0, uint32_t x1, uint32_t y, Color& c){
    for(int i = x0; i <= x1; i++)
      p[i][y] = c;
  }

  void vertLine(uint32_t x, uint32_t y0, uint32_t y1, Color& c){
    for(int i = y0; i <= y1; i++)
      p[x][i] = c;
  }

  //assume x and y given are coordinates of upper left corner of rectangle
  void fillRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, Color& c){
    for(int i = x; i <= x+w; i++)
      for(int j = y; j <= y+h; j++)
        p[i][j] = c;
  }

  void drawRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, Color& c){
    for(int i = x; i <= x+w; i++)
      for(int j = y; j <= y+h; j++){
        if(i == x || j == y || i == x+w || j == y+h)
          p[i][j] = c;
      }
  }

  void ellipse(uint32_t x, uint32_t y, uint32_t w, uint32_t h, Color& c){
    for(int i = x-(w/4)+1; i < x+(w/4); i++){
      p[i][y-(h/2)] = c;
      p[i][y+(h/2)] = c;
    }
    for(int j = y-(h/4)+1; j < y+(h/4); j++){
      p[x-(w/4)][j] = c;
      p[x+(w/4)][j] = c;
    }

  }


	friend ostream& operator <<(ostream& s, Bitmap b){
		for(int i = 0; i < b.height; i++){
			s << endl;
			for(int j = 0; j < b.width; j++){
				s << setw(2) << b.p[j][i];
			}
		}
		return s;
	}

};



int main() {
	Bitmap b(30,20); // 30 pixels across, 20 pixels high, each pixel RGBA
	// top left pixel = (0,0)
	Color RED(255,0,0); // all red, no green, no blue (fully opaque)
	Color BLUE(0,0,255);
	Color GREEN(0,255,0);
  Color WHITE(255,255,255);
  Color BLACK(0,0,0);

  b.line(0,0,   19,19, RED);
	b.line(0,5,   29,10, BLUE); //Bresenham algorithm
	//https://en.wikipedia.org/wiki/Bresenham's_line_algorithm

	// https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
	//TODO: b.line(0,100, 100,50, BLUE); //Wu algorithm
	b.horizLine(0, 20, 19, GREEN); // from x=0 to x=20 at y=19
	b.vertLine(5, 0,19, GREEN); // from y = 0 to y=19 at x = 5
	b.fillRect(10,10, 4, 3,BLACK); // x = 10, y =10 w=4, h=3
	b.drawRect(10,10, 4, 3,WHITE); // x = 10, y =10 w=4, h=3
  //change y coordinate to 3 so that ellipse is not cut off
  b.ellipse(15,3, 8, 5, RED);    // ellipse centered at (15,0) w= 8, h=5
	cout << b;

	/*
R
 R
  R
   R
    R
BBB
   BBBBB
        BBBBBB


	 */
}
