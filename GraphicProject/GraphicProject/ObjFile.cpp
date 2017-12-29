#include "ObjFile.h"

#include<sstream>
#include<fstream>

using namespace std;



ObjFile::ObjFile(string file) {
	string s;
	face* f;
	vertex* v;
	normal* n;
	tex* t;

	ifstream ifs(file);

	while (getline(ifs, s)) {
		if (s.length() < 2)continue;
		if (s[0] == 'v') {
			istringstream in(s);
			string head;
			if (s[1] == 't') {
				t = new tex();
				in >> head >> t->tu >> t->tv;
				this->T.push_back(*t);
			}
			else if (s[1] == 'n') {
				n = new normal();
				in >> head >> n->x >> n->y >> n->z;
				this->N.push_back(*n);
			}
			else {
				v = new vertex();
				in >> head >> v->x >> v->y >> v->z;
				this->V.push_back(*v);
			}
		}
		else if (s[0] == 'f') {
			for (int i = s.size() - 1; i >= 0; i--) {
				if (s[i] == '/')s[i] = ' ';
			}
			istringstream in(s);
			f = new face();
			string head;
			in >> head;
			int j = 0;
			while (j < 3)
			{
				if (this->V.size() != 0)
				{
					in >> f->v[j];
					f->v[j] -= 1;
				}
				if (this->T.size() != 0)
				{
					in >> f->t[j];
					f->t[j] -= 1;
				}
				if (this->N.size() != 0)
				{
					in >> f->n[j];
					f->n[j] -= 1;
				}
				j++;
			}
			this->F.push_back(*f);
		}
	}

}

