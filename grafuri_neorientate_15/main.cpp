#include<iostream>
#include<fstream>
#define tovaras friend
using namespace std;

class Graf
{
private:
	int **mat_adiac;
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
		for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			mat_adiac[i][j] = 0;
	}
	Graf(int, int**);
	void print()
	{
		for (int i = 0; i < n; i++){
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
	tovaras ostream &operator<<(ostream &os, Graf g);
	tovaras istream &operator>>(istream &is, Graf &g);
	Graf operator+(Graf param);
};
Graf Graf::operator+(Graf param)
{
	Graf rez(n);

	for (int i = 0; i < n;i++)
	for (int j = 0; j < n; j++)
		rez.mat_adiac[i][j] = (mat_adiac[i][j] == 1 || param.mat_adiac[i][j] == 1);

	return rez;
}
istream &operator>>(istream &is, Graf &g)
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

	return is;
}
ostream &operator<<(ostream &os, Graf g)
{
	for (int i = 0; i < g.n; i++)
	{
		for (int j = 0; j < g.n; j++)
		{
			os << g.mat_adiac[i][j] << " ";

		}
		os << endl;
	}
	return os;
}
Graf::Graf(int n, int **a)
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
}
void Graf::add_muchie(int i, int j)
{
	mat_adiac[i][j] = mat_adiac[j][i] = 1;
}
void Graf::remove_muchie(int i, int j)
{
	mat_adiac[i][j] = mat_adiac[j][i] = 0;
}
void Graf::DF(int ind, int af)
{
	int *viz = new int[n];
	for (int i = 0; i < n; i++)
		viz[i] = 0;
	if (af){
		cout << endl;
		cout << "Parcurgerea in adancime din " << ind << " e: ";
	}
	DF(ind,viz,1,af);
	if (af)
	cout << endl;
	delete[]viz;
}
void Graf::DF(int ind, int *viz, int nr,int af)
{
	if (af)
	cout << ind << " ";
	viz[ind] = nr;
	for (int i = 0; i < n;i++)
	if (mat_adiac[ind][i] == 1 && ind != i&&viz[i] == 0)
		DF(i,viz,nr,af);
}
void Graf::BF(int ind,int af)
{
	int *viz = new int[n];
	for (int i = 0; i < n; i++)
		viz[i] = 0;
	if (af){
		cout << endl;
		cout << "Parcurgerea in latime din " << ind << " e: ";
	}
	BF(ind, viz,1,af);
	if (af)
	cout << endl;

	delete[]viz;
}
void Graf::BF(int ind, int *viz,int nr, int af)
{
	int *que = new int[n];
	que[0] = ind;
	int p=0,u=0;
	viz[que[0]] = nr;
	while (p <= u)
	{
		if (af)
		cout << que[p]<<" ";
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
void Graf::DrumConexe()
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
int **Graf::MatDrumConexe(int af)
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
int Graf::is_conex()
{
	int **d = this->MatDrumConexe(0);
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n;j++)
	if (d[i][j] == 0) return 0;

	return 1;
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
	Graf g;
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
	Graf g2;
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
	Graf g3=g+g2;
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
	cout << endl;
	cout << endl;

	system("pause");
	return 0;
}