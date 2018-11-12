/*
	 Author: Kyra DiFrancesco
*/
/*
PRORGRAM PRINTS TO OUT.STL
 */
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
using namespace std;

const double PI = 3.14159265358979;

class Design {
private:

public:

};

class Cube {
private:
	double side, x, y, z;
public:
	Cube(double s = 0, double x = 0, double y = 0, double z = 0) : side(s), x(x), y(y), z(z) {}
	void write(const string& fileName) const {
		ofstream myFile (fileName);
	//myFile.open(fileName, ios::app);
		if (myFile.is_open()) {
			cout <<"writing to file" << endl;

			myFile << "solid Cube\n facet normal -0 0 1\n outer loop\n vertex " << x+0 << " " << y+side
			<< " " << z+side << "\n vertex " << x+side << " " << y+0 << " " << z+side << "\n vertex "
			 << x+side << " " << y+side << " " << z+side << "\n endloop\n endfacet\n"

			 << "facet normal 0 0 1\n outer loop\n vertex " << x+side << " " << y+0
 			<< " " << z+side << "\n vertex " << x+0 << " " << y+side << " " << z+side << "\n vertex "
 			 << x+0 << " " << y+0 << " " << z+side << "\n endloop\n endfacet\n"

			 << "facet normal 0 0 -1\n outer loop\n vertex " << x+0 << " " << y+0
				<< " " << z+0 << "\n vertex " << x+side << " " << y+side << " " << z+0 << "\n vertex "
				 << x+side << " " << y+0 << " " << z+0 << "\n endloop\n endfacet\n"

			 << "facet normal -0 0 -1\n outer loop\n vertex " << x+side << " " << y+side
				<< " " << z+0 << "\n vertex " << x+0 << " " << y+0 << " " << z+0 << "\n vertex "
				 << x+0 << " " << y+side << " " << z+0 << "\n endloop\n endfacet\n"

			 << "facet normal 0 -1 0\n outer loop\n vertex " << x+0 << " " << y+0
				<< " " << z+0 << "\n vertex " << x+side << " " << y+0 << " " << z+side << "\n vertex "
				 << x+0 << " " << y+0 << " " << z+side << "\n endloop\n endfacet\n"

			 << "facet normal 0 -1 -0\n outer loop\n vertex " << x+side << " " << y+0
				<< " " << z+side << "\n vertex " << x+0 << " " << y+0 << " " << z+0 << "\n vertex "
				 << x+side << " " << y+0 << " " << z+0 << "\n endloop\n endfacet\n"

				 << "facet normal 1 -0 0\n outer loop\n vertex " << x+side << " " << y+0
	 			<< " " << z+side << "\n vertex " << x+side << " " << y+side << " " << z+0 << "\n vertex "
	 			 << x+side << " " << y+side << " " << z+side << "\n endloop\n endfacet\n"

				 << "facet normal 1 0 0\n outer loop\n vertex " << x+side << " " << y+side
				<< " " << z+0 << "\n vertex " << x+side << " " << y+0 << " " << z+side << "\n vertex "
				 << x+side << " " << y+0 << " " << z+0 << "\n endloop\n endfacet\n"

				 << "facet normal 0 1 -0\n outer loop\n vertex " << x+side << " " << y+side
				<< " " << z+0 << "\n vertex " << x+0 << " " << y+side << " " << z+side << "\n vertex "
				 << x+side << " " << y+side << " " << z+side << "\n endloop\n endfacet\n"

				 << "facet normal 0 1 0\n outer loop\n vertex " << x+0 << " " << y+side
				<< " " << z+side << "\n vertex " << x+side << " " << y+side << " " << z+0 << "\n vertex "
				 << x+0 << " " << y+side << " " << z+0 << "\n endloop\n endfacet\n"

				 << "facet normal -1 0 0\n outer loop\n vertex " << x+0 << " " << y+0
				<< " " << z+0 << "\n vertex " << x+0 << " " << y+side << " " << z+side << "\n vertex "
				 << x+0 << " " << y+side << " " << z+0 << "\n endloop\n endfacet\n"

				 << "facet normal -1 -0 0\n outer loop\n vertex " << x+0 << " " << y+side
				<< " " << z+side << "\n vertex " << x+0 << " " << y+0 << " " << z+0 << "\n vertex "
				 << x+0 << " " << y+0 << " " << z+side << "\n endloop\n endfacet\n"

				 << "endsolid cube\n \n";



			myFile.close();
		}
		else cout << "Unable to open file";
	}
	void translate(int dx, int dy, int dz) {
		x += dx;
		y += dy;
		z += dz;
	}

	double volume() {
		return side*side*side;
	}
};

class Cylinder {
//cylinder with 8 facets, so sides are 8 rectangles(16 triangles), and the
//top and bottom faces are octogons (6 triangles each)
private:
	double r, height;
public:
	Cylinder(double r, double h) : r(r), height(h) {}
	void write(const string& fileName) {
		double bottomVertices[8][3] = {-10,0,0,
																	-r*cos(PI/4),-r*cos(PI/4),0,
																	-r*cos(PI/4),r*cos(PI/4),0,
																	0,-10,0,
																	0,10,0,
																	r*cos(PI/4),-r*cos(PI/4),0,
																	r*cos(PI/4),r*cos(PI/4),0,
																	10,0,0};
		double topVertices[8][3];
		for(int i = 0; i < 8; i++)
			for(int j = 0; j < 3; j++) {
				if(j==2)
					topVertices[i][j] = bottomVertices[i][j] + 10;
				else topVertices[i][j] = bottomVertices[i][j];
			}
		double normals[10][3] = {0.92388,0.382683,0, //normals for each facet
															0.382683,0.92388,0,
															-0.382683,0.92388,0,
															-0.92388,0.382683,0,
															-0.92388,-0.382683,0,
															-0.382683,-0.92388,0,
															 0.382683,-0.92388,0,
															 0.92388,-0.382683,0,
															 0,0,-1, //normal vectors for top and bottom face
															 0,0,1};
	 ofstream myFile(fileName,ios::app);
		if (myFile.is_open()) {
			myFile << "solid Cylinder\n";
			//write bottom face
			int n1 = 0;
			int n2 = 3;
			for(int i = 0; i < 6; i++){ //6 triangles
				myFile << "facet normal 0 0 -1\n outer loop\n";
				for(int j = n1; j < n2; j++){ //3 vertices in a triangle
					if(j==n1){
						myFile << "vertex " << bottomVertices[n1][0] << " " << bottomVertices[n1][1] << " " << bottomVertices[n1][2] << '\n';
					}
					else if(j==(n1+1)){
						myFile << "vertex " << bottomVertices[n1+1][0] << " " << bottomVertices[n1+1][1] << " " << bottomVertices[n1+1][2] << '\n';
					}
					else if(j==(n1+2)){
						myFile << "vertex " << bottomVertices[n1+2][0] << " " << bottomVertices[n1+2][1] << " " << bottomVertices[n1+2][2] << "\n endloop\n endfacet\n";
					}

				}
				n1++;
				n2++;
			}
			//code top face
			n1 = 0;
			n2 = 3;
			for(int i = 0; i < 6; i++){ //6 triangles
				myFile << "facet normal 0 0 1\n outer loop\n";
				for(int j = n1; j < n2; j++){ //3 vertices in a triangle
					if(j==n1){
						myFile << "vertex " << topVertices[n1][0] << " " << topVertices[n1][1] << " " << topVertices[n1][2] << '\n';
					}
					else if(j==(n1+1)){
						myFile << "vertex " << topVertices[n1+1][0] << " " << topVertices[n1+1][1] << " " << topVertices[n1+1][2] << '\n';
					}
					else if(j==(n1+2)){
						myFile << "vertex " << topVertices[n1+2][0] << " " << topVertices[n1+2][1] << " " << topVertices[n1+2][2] << "\n endloop\n endfacet\n";
					}

				}
				n1++;
				n2++;
			}

			//code half of the sides
			//reorder vertices to make coding sides easier
			double rbottomVertices[9][3] = {-10,0,0,
															-r*cos(PI/4),-r*cos(PI/4),0,
															0,-10,0,
															r*cos(PI/4),-r*cos(PI/4),0,
															10,0,0,
															r*cos(PI/4),r*cos(PI/4),0,
															0,10,0,
															-r*cos(PI/4),r*cos(PI/4),0,
															-10,0,0}; //wrap around at the end

			n1 = 0;
			n2 = 3;
			for(int i = 0; i < 8; i++){ //8 triangles
				if(i==0) myFile << "facet normal -0.92388 -0.382683 0\n outer loop\n";
				if(i==1) myFile << "facet normal -0.382683 -0.92388 0\n outer loop\n";
				if(i==2) myFile << "facet normal 0.382683 -0.92388 0\n outer loop\n";
				if(i==3) myFile << "facet normal 0.92388 -0.382683 0\n outer loop\n";
				if(i==4) myFile << "facet normal 0.92388 0.382683 0\n outer loop\n";
				if(i==5) myFile << "facet normal 0.382683 0.92388 0\n outer loop\n";
				if(i==6) myFile << "facet normal -0.382683 0.92388 0\n outer loop\n";
				if(i==7) myFile << "facet normal -0.92388 0.382683 0\n outer loop\n";//ISSUE HERE
				for(int j = n1; j < n2; j++){ //3 vertices in a triangle
					if(j==n1){
						myFile << "vertex " << rbottomVertices[n1][0] << " " << rbottomVertices[n1][1] << " " << rbottomVertices[n1][2] << '\n';
					}
					else if(j==(n1+1)){
						myFile << "vertex " << rbottomVertices[n1+1][0] << " " << rbottomVertices[n1+1][1] << " " << rbottomVertices[n1+1][2] << '\n';
					}
					else if(j==(n1+2)){
						myFile << "vertex " << rbottomVertices[n1][0] << " " << rbottomVertices[n1][1] << " " << rbottomVertices[n1][2] + 10 << "\n endloop\n endfacet\n";
					}
				}
				n1++;
				n2++;
			}

			double rtopVertices[9][3] = {
																-r*cos(PI/4),r*cos(PI/4),10,
																0,10,10,
																r*cos(PI/4),r*cos(PI/4),10,
																10,0,10,
																r*cos(PI/4),-r*cos(PI/4),10,
																0,-10,10,
																-r*cos(PI/4),-r*cos(PI/4),10,
																-10,0,10,
																-r*cos(PI/4),r*cos(PI/4),10
																};  //wrap around at the end

			n1 = 0;
			n2 = 3;
			for(int i = 0; i < 8; i++){ //8 triangles
				if(i==0) myFile << "facet normal -0.92388 -0.382683 0\n outer loop\n";
				if(i==1) myFile << "facet normal -0.382683 -0.92388 0\n outer loop\n";
				if(i==2) myFile << "facet normal 0.382683 -0.92388 0\n outer loop\n";
				if(i==3) myFile << "facet normal 0.92388 -0.382683 0\n outer loop\n";
				if(i==4) myFile << "facet normal 0.92388 0.382683 0\n outer loop\n";
				if(i==5) myFile << "facet normal 0.382683 0.92388 0\n outer loop\n";
				if(i==6) myFile << "facet normal -0.382683 0.92388 0\n outer loop\n";
				if(i==7) myFile << "facet normal -0.92388 0.382683 0\n outer loop\n";//ISSUE HERE
				for(int j = n1; j < n2; j++){ //3 vertices in a triangle
					if(j==n1){
						myFile << "vertex " << rtopVertices[n1][0] << " " << rtopVertices[n1][1] << " " << rtopVertices[n1][2] << '\n';
					}
					else if(j==(n1+1)){
						myFile << "vertex " << rtopVertices[n1+1][0] << " " << rtopVertices[n1+1][1] << " " << rtopVertices[n1+1][2] << '\n';
					}
					else if(j==(n1+2)){
						myFile << "vertex " << rtopVertices[n1][0] << " " << rtopVertices[n1][1] << " " << rtopVertices[n1][2] - 10 << "\n endloop\n endfacet\n";
					}
				}
				n1++;
				n2++;
			}
			myFile << "endsolid Cylinder";
			myFile.close();
		}
		else cout << "Unable to open file";


	 }//end of write
};

int main() {
//	Design d("test.stl"); //design file contains a list of shape stars
	double s = 10;
	Cube c(s); //0,0,0 corner at the origin
	double x = 3, y = 4, z = 5; //I MADE THESE MYSELF
	c.translate(x,y,z);
	cout << c.volume() << '\n';
	c.write("out.stl"); // how to get all my shapes into the same file
  // d.add(c);
	double r = 10, height  = 20;
	Cylinder cyl(r, height); //need trig, approximated by rectangles
	cyl.write("out.stl"); //I MDAE THIS MYSELF
	// d.add(c);
	// d.write();

}
