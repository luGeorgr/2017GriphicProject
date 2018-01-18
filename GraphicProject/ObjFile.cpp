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

	string mtl_path = file + "/" + file + ".mtl";
	string obj_path = file + "/" + file + ".obj";
	int mtl_count;
	int r = file.find('.');
	mtl_count = ReadMTLFile(mtl_path);
	Material* material=new Material[mtl_count];
	ReadMTLData(mtl_path, material);
	for (int i = 0; i < mtl_count; i++) {
		this->M.push_back(material[i]);
	}
	
	int index = 0;

	ifstream ifs(obj_path);

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
		else if (s.substr(0, 2).compare("us") == 0) {
			string l = "usemtl ";
			string m = s.substr(l.size());
			for (int i = 0; i<mtl_count; i++)
			{
				if (m.compare(material[i].name) == 0)
					index = material[i].index;
			}
		}
		else if (s[0] == 'f') {
			int count = 0;
			for (int i = s.size() - 1; i >= 0; i--) {
				if (s[i] == '/') {
					count++;
					s[i] = ' ';
				}
			}
			
			istringstream in(s);
			f = new face();
			string head;
			in >> head;
			int j = 0;
			f->type = count / 2;
			f->v = new int[f->type];
			f->n = new int[f->type];
			f->t = new int[f->type];
			while (j < f->type)
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
			f->m_index = index;
			this->F.push_back(*f);
			
		}

	}
}

int ObjFile::ReadMTLFile(string file) {
	ifstream ifs(file);
	string s;
	int count=0;
	while (getline(ifs, s)) {
		if (s.substr(0, 6).compare("newmtl") == 0) {
			count++;
		}
	}
	return count;
}


void ObjFile::ReadMTLData(string file, Material* material) {
	int m = 0;
	ifstream inMTL;
	inMTL.open(file);
	if (!inMTL.good())
	{
		cout << "ERROR OPENING MTL FILE" << endl;
		exit(1);
	}
	while (!inMTL.eof())
	{
		string line;
		getline(inMTL, line);
		istringstream in(line);
		string type ;
		string type1;
		in >> type;
		type1 = type;
		type = type.substr(0, 2);

;


		if (type.compare("ne") == 0)
		{
			string l = "newmtl ";
			material[m].name = line.substr(l.size());
			material[m].index = m;
			m++;
		}
		else if (type.compare("Ns") == 0) {
			in  >> material[m - 1].Ns;
		}
		else if (type.compare("Ni") == 0) {
			in >> material[m - 1].Ni;
		}
		else if (type.compare("d ") == 0) {
			in >> material[m - 1].d;
		}
		else if (type.compare("Tr") == 0) {
			in >> material[m - 1].Tr;
		}
		else if (type.compare("Tf ") == 0) {
			char* l = new char[line.size() + 1];
			memcpy(l, line.c_str(), line.size() + 1);
			strtok(l, " ");
			for (int i = 0; i<3; i++)
				material[m - 1].Tf[i] = atof(strtok(NULL, " "));
			delete[] l;
		}
		else if (type.compare("il") == 0) {
			in >> material[m - 1].illum;
		}
		else if (type.compare("Ka") == 0)
		{
			char* l = new char[line.size() + 1];
			memcpy(l, line.c_str(), line.size() + 1);

			strtok(l, " ");
			for (int i = 0; i<3; i++)
				material[m - 1].Ka[i] = atof(strtok(NULL, " "));

			delete[] l;
		}
		else if (type.compare("Kd") == 0)
		{
			char* l = new char[line.size() + 1];
			memcpy(l, line.c_str(), line.size() + 1);

			strtok(l, " ");
			for (int i = 0; i<3; i++)
				material[m - 1].Kd[i] = atof(strtok(NULL, " "));

			delete[] l;
		}
		else if (type.compare("Ks") == 0)
		{
			char* l = new char[line.size() + 1];
			memcpy(l, line.c_str(), line.size() + 1);

			strtok(l, " ");
			for (int i = 0; i<3; i++)
				material[m - 1].Ks[i] = atof(strtok(NULL, " "));

			delete[] l;
		}
		else if (type.compare("Ke") == 0)
		{
			char* l = new char[line.size() + 1];
			memcpy(l, line.c_str(), line.size() + 1);

			strtok(l, " ");
			for (int i = 0; i<3; i++)
				material[m - 1].Ke[i] = atof(strtok(NULL, " "));

			delete[] l;
		}
		else if (type1.compare("map_Ka") == 0)
		{
			string l ;
			in >> l;
			string p = file.substr(0, file.find("/"));
			material[m - 1].map_Ka = p+"/"+l;
		}
		else if (type1.compare("map_Kd") == 0)
		{
			string l ;
			in >> l;
			string p = file.substr(0, file.find("/"));
			material[m - 1].map_Kd = p + "/"+l;
		}
		else if (type1.compare("map_Ks") == 0)
		{
			string l;
			in >> l;
			string p = file.substr(0, file.find("/"));
			material[m - 1].map_Ks = p + "/" + l;
		}
		else if (type1.compare("map_Bump") == 0)
		{
			string l;
			in >> l;
			string p = file.substr(0, file.find("/"));
			material[m - 1].map_Bump = p + "/" + l;
		}
		else if (type1.compare("map_d") == 0)
		{
			string l;
			in >> l;
			string p = file.substr(0, file.find("/"));
			material[m - 1].map_d = p + "/" + l;
		}
		else if (type1.compare("Bump") == 0)
		{
			string l;
			in >> l;
			string p = file.substr(0, file.find("/"));
			material[m - 1].Bump = p + "/" + l;
		}
	}

	inMTL.close();
}

