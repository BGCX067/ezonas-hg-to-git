// #include "incl.h"
#include <vector>
#include <iostream>
using namespace std;
struct vertex
{
	float x, y, z;
	vertex operator+(vertex v);
	vertex operator-(vertex v);
	vertex(float, float, float);
	// vertex operator*(vertex v);
	// vertex operator/(vertex v);
	void show();

};


struct triangle
{
	vertex v1, v2, v3;
};

struct quad
{
	vertex v1, v2, v3, v4;
};
// vertex-vertex mesh
struct mesh_vv_elem
{
	vertex v; // one vertex is stored
	vertex l[]; // a list of pointer to vertices
	// vertex l[]; // a list of pointer to vertices
};

// face-vertex mesh
struct mesh_fv_face
{
	vertex v1, v2, v3;
};

struct mesh_fv_vertex
{
	vertex v;
	mesh_fv_face l[];
};


class mesh
{


};

