#include<iostream>
#include<fstream>
#define tovaras friend
using namespace std;

template<class T>
class Graf
{
protected:
	int **mat_adiac;
	T* eticheta;
	int n;
	void DF(int, int*,int nr=1,int af=1);
	void BF(int, int*,int nr = 1, int af = 1);
public:
	int size(){ return n; }
	Graf()
	{

	}
	Graf(int n)
	{
		this->n = n;
		mat_adiac= new int*[n];
		for (int i = 0; i < n; i++)
		{
			mat_adiac[i] = new int[n];
		}
		eticheta=new T[n];
	}
	Graf(int, int**);
	void print()
	{
		for (int i = 0; i < n; i++){
			cout<<eticheta[i]<<": ";
			for (int j = 0; j < n; j++)
			{
				cout << mat_adiac[i][j] << " ";

			}
			cout << endl;
		}
	}
	void add_muchie(int, int);
	void remove_muchie(int, int);
	void BF(int,int af=1);
	void DF(int,int af=1);
	void DrumConexe();
	int** MatDrumConexe(int af=1);
	int is_conex();
	template<typename T> tovaras ostream &operator<<(ostream &os, Graf<T> g);
	template<typename T> tovaras istream &operator>>(istream &is, Graf<T> &g);
	Graf<T> operator+(Graf<T> param);
	void stergeNod(int);
};
template<class T>
Graf<T> Graf<T>::operator+(Graf<T> param)
{

	Graf<T> rez(n);

	for (int i = 0; i < n;i++)
	for (int j = 0; j < n; j++)
		rez.mat_adiac[i][j] = (mat_adiac[i][j] == 1 || param.mat_adiac[i][j] == 1);

	
	for(int i=0;i<n;i++)
		rez.eticheta[i]=eticheta[i];

	return rez;
}
template<typename T>
istream &operator>>(istream &is, Graf<T> &g)
{
	is >> g.n;
	g.mat_adiac = new int*[g.n];
	for (int i = 0; i < g.n; i++)
	{
		g.mat_adiac[i] = new int[g.n];
	}
	for (int i = 0; i < g.n; i++)
		for (int j = 0; j < g.n; j++)
			is >> g.mat_adiac[i][j];

	g.eticheta=new T[g.n];
	for(int i=0;i<g.n;i++)
		is>>g.eticheta[i];
	return is;
}
template<typename T>
ostream &operator<<(ostream &os, Graf<T> g)
{
	for (int i = 0; i < g.n; i++)
	{
		os<<g.eticheta[i]<<": ";
		for (int j = 0; j < g.n; j++)
		{
			os << g.mat_adiac[i][j] << " ";

		}
		os << endl;
	}
	return os;
}
template<class T>
Graf<T>::Graf(int n, int **a)
{
	this->n = n;
	mat_adiac = new int*[n];
	for (int i = 0; i < n; i++)
	{
		mat_adiac[i] = new int[n];
	}
	for (int i = 0; i < n;i++)
	for (int j = 0; j < n; j++)
		mat_adiac[i][j] = a[i][j];

	eticheta=new T[n];
}
template<class T>
void Graf<T>::add_muchie(int i, int j)
{
	mat_adiac[i][j] = mat_adiac[j][i] = 1;
}
template<class T>
void Graf<T>::remove_muchie(int i, int j)
{
	mat_adiac[i][j] = mat_adiac[j][i] = 0;
}
template<class T>
void Graf<T>::DF(int ind, int af)
{
	int *viz = new int[n];
	for (int i = 0; i < n; i++)
		viz[i] = 0;
	if (af){
		cout << endl;
		cout << "Parcurgerea in adancime din " << eticheta[ind] << " e: ";
	}
	DF(ind,viz,1,af);
	if (af)
	cout << endl;
	delete[]viz;
}
template<class T>
void Graf<T>::DF(int ind, int *viz, int nr,int af)
{
	if (af)
	cout << eticheta[ind] << " ";
	viz[ind] = nr;
	for (int i = 0; i < n;i++)
	if (mat_adiac[ind][i] == 1 && ind != i&&viz[i] == 0)
		DF(i,viz,nr,af);
}
template<class T>
void Graf<T>::BF(int ind,int af)
{
	int *viz = new int[n];
	for (int i = 0; i < n; i++)
		viz[i] = 0;
	if (af){
		cout << endl;
		cout << "Parcurgerea in latime din " << eticheta[ind] << " e: ";
	}
	BF(ind, viz,1,af);
	if (af)
	cout << endl;

	delete[]viz;
}
template<class T>
void Graf<T>::BF(int ind, int *viz,int nr, int af)
{
	int *que = new int[n];
	que[0] = ind;
	int p=0,u=0;
	viz[que[0]] = nr;
	while (p <= u)
	{
		if (af)
		cout << eticheta[que[p]]<<" ";
		for (int i = 0; i < n;i++)
		if (mat_adiac[que[p]][i] == 1 && que[p] != i && viz[i] == 0){
			que[++u] = i;
			viz[i] = nr;
		}
		p++;
	}
}
int checkfull(int n,int *a,int &c)
{
	for (int i = 0; i < n; i++)
	if (a[i] == 0){
		c = i;
		return 0;
	}
	return 1;
}
template<class T>
void Graf<T>::DrumConexe()
{
	int *viz = new int[n];
	for (int i = 0; i < n; i++)
		viz[i] = 0;

	cout << endl;
	int c;
	int nr = 1;
	while (!checkfull(n, viz,c))
	{
		cout << "Drumul " << nr << " este:";
		DF(c, viz,nr,1);
		cout << endl;
		nr++;
	}
	
	delete[]viz;
}
template<class T>
int** Graf<T>::MatDrumConexe(int af)
{
	int **drum = new int*[n];
	for (int i = 0; i < n; i++)
		drum[i] = new int[n];
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
		drum[i][j] = mat_adiac[i][j];

	for (int i = 0; i < n;i++)
	for (int j = 0; j < n;j++)
	for (int k = 0; k < n; k++)
	if (!drum[i][j])
		drum[i][j] = drum[i][k] * drum[k][j];

	if (af)
	{
		cout << endl;
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++)
				cout << drum[i][j]<<" ";
			cout << endl;
		}
		
	}
	return drum;
}
template<class T>
int Graf<T>::is_conex()
{
	int **d = this->MatDrumConexe(0);
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n;j++)
	if (d[i][j] == 0) return 0;

	return 1;
}
template<class T>
void Graf<T>::stergeNod(int nod)
{
	for(int i=0;i<n;i++)
	{
		for(int j=nod;j<n-1;j++)
			mat_adiac[i][j]=mat_adiac[i][j+1];
	}
	for(int i=0;i<n;i++)
	{
		for(int j=nod;j<n-1;j++)
			mat_adiac[j][i]=mat_adiac[j+1][i];
	}
	n--;
}
template<class T>
class Arbore:public Graf<T>
{
private:
	int radacina;
	int* tati;
	int** getMatArray()
	{
		return mat_adiac;
	}

public:
	Arbore()
	{ }
	Arbore(int n,int rad):Graf<T>(n)
	{
		radacina=rad;
		tati=new int[n];
		for(int i=0;i<n;i++)
			tati[i]=0;
	}
	Arbore(int n,int **mat,int rad):Graf<T>(n,mat)
	{
		radacina=rad;
		tati=new int[n];
	}
	void parinti()
	{
		cout<<"Parinti: ";
		for(int i=0;i<n;i++)
			if(tati[i]!=-1)
				cout<<eticheta[tati[i]]<<" ";
			else
				cout<<"R ";
	}
	template<typename T> tovaras ostream &operator<<(ostream &os, Arbore<T> g);
	template<typename T> tovaras istream &operator>>(istream &is, Arbore<T> &g);
};
template<typename T>
istream &operator>>(istream &is, Arbore<T> &g)
{
	is >> g.n;
	is >> g.radacina;
	g.tati=new int[g.n];

	for(int i=0;i<g.n;i++)
		g.tati[i]=-2;
	g.mat_adiac = new int*[g.n];
	for (int i = 0; i < g.n; i++)
	{
		g.mat_adiac[i] = new int[g.n];
	}
	for (int i = 0; i < g.n; i++)
		for (int j = 0; j < g.n; j++)
			is >> g.mat_adiac[i][j];

	g.tati[g.radacina]=-1;
	int *v=new int[g.n];
	for(int i=0;i<g.n;i++)
		v[i]=0;
	bool done=false;
	while(!done)
	{
		done=true;
		for(int i=0;i<g.n;i++)
			if(g.tati[i]!=-2&&v[i]==0)
			{
				v[i]=1;
				for(int j=0;j<g.n;j++)
					if(g.mat_adiac[i][j]!=0&&v[j]==0)
					{
						done=false;
						g.tati[j]=i;
					}
			}
					

	}

	g.eticheta=new T[g.n];
	for(int i=0;i<g.n;i++)
		is>>g.eticheta[i];
	
	delete[]v;
	return is;
}
template<typename T>
ostream &operator<<(ostream &os, Arbore<T> g)
{
	for (int i = 0; i < g.n; i++)
	{
		os<<g.eticheta[i]<<": ";
		for (int j = 0; j < g.n; j++)
		{
			os << g.mat_adiac[i][j] << " ";

		}
		os << endl;
	}
	g.parinti();
	return os;
}
int main()
{
	ifstream f("graf.txt");
	/*int n,x;
	int **a;
	f >> n;
	a = new int*[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new int[n];
	}
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
	{
		f >> x;
		a[i][j] = x;
	}*/
	cout << "GRAF 1\n";
	Graf<char>g;
	f >> g;
	g.print();
	cout << endl;
	cout << g;
	g.DF(0,1);
	g.BF(0,1);
	g.DrumConexe();
	int **d=g.MatDrumConexe(0);
	for (int i = 0; i < g.size(); i++){
		for (int j = 0; j < g.size(); j++)
			cout << d[i][j]<<" ";
		cout << endl;
	}
	cout << g.is_conex();
	cout <<"--------------------------------------"<< endl;

	cout << "GRAF 2\n";
	Graf<char>g2;
	f >> g2;
	g2.print();
	cout << endl;
	cout << g2;
	g2.DF(0, 1);
	g2.BF(0, 1);
	g2.DrumConexe();
	int **d2 = g2.MatDrumConexe(0);
	for (int i = 0; i < g2.size(); i++){
		for (int j = 0; j < g2.size(); j++)
			cout << d2[i][j] << " ";
		cout << endl;
	}
	cout << g.is_conex();
	cout << endl;
	cout << "--------------------------------------" << endl;

	cout << "GRAF 3\n";
	Graf<char>g3=g+g2;
	g3.print();
	cout << endl;
	cout << g3;
	g3.DF(0, 1);
	g3.BF(0, 1);
	g3.DrumConexe();
	int **d3 = g3.MatDrumConexe(0);
	for (int i = 0; i < g3.size(); i++){
		for (int j = 0; j < g3.size(); j++)
			cout << d3[i][j] << " ";
		cout << endl;
	}
	cout << g3.is_conex();
	Arbore<char>arbore;
	f>>arbore;
	arbore.DF(0,1);
	cout<<arbore;
	system("pause");
	return 0;
}
