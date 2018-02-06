#include <iostream>
#include <cstdlib>
#include <map>
#include <ctime>
#include <cstring>
#include <sstream>
#include <vector>


using namespace std;

stringstream OK;

/**
 *
 * @param velikost
 * @param ary
 * @param Bary
 * @return
 */



int Maze(const int& velikost, int** ary, bool** Bary)
{

    int hodnota=0;
    srand(time(NULL));
    if(velikost<=8)
    {
        hodnota=4;
    }
    if(velikost>9 && velikost<=14)
    {
        hodnota=6;
    }
    if(velikost>14)
    {
        hodnota=9;
    }
    for(int i = 0; i < velikost; ++i)
    {
        ary[i] = new int[velikost];
    }
    for(int i=0;i<velikost;i++)
    {    cout<<endl;
        for(int j=0;j<velikost;j++)
        {
            ary[i][j]=rand()%hodnota+1;
            cout<<ary[i][j]<<" ";
        }
    }


    for(int i = 0; i < velikost; ++i)
    {
        Bary[i] = new bool[velikost];
    }
    for(int i=0;i<velikost;i++)
    {
        memset(Bary[i], 1, velikost * sizeof (bool));
    }
    return 0;
}
/**
 * Pomocna funkce ukazujici cestu panacka.
 * @param Bary - pole Bool, uklada cestu panacka pomoci "true se meni na false"
 * @param velikost - Velikost pole
 */

void print(bool **Bary, int velikost)
{ cout<<endl;
    for(int i=0;i<velikost;++i)
    {   cout<<endl;
        for(int j=0;j<velikost;++j)
            cout<<Bary[i][j]<<" ";
    }

}

/**
 * Funkce kontrolujici pohyb panacka, zda nevyjde z pole.
 * @param velikost - Velikost pole
 * @param step - hodnota pole kde stoji panacek
 * @param way -
 * @param asdf
 * @return
 */
bool InAry(const int velikost, const int step, const int way, const int asdf )
{
    if(way+step<velikost && asdf)return true;
    if(way-step>0 && asdf==0)return true;
    return false;
}
/**
 *
 * @param ary
 * @param i
 * @param j
 * @param velikost
 * @param Bary
 * @param posI
 * @param posJ
 * @return
 */

int go(int** ary, int i,int j,  const int velikost, bool** Bary, vector<int> &posI, std::vector<int> &posJ)
{
    int step;
    step=ary[i][j];
    //cout    <<  step;
    if(i==velikost-1 && j==velikost-1)                          ///
    {
        posI.push_back(i);
        posJ.push_back(j);
        return 2;
    }
    if (InAry(velikost, step, i, 1) && Bary[i+step][j]==1)
    {
        posI.push_back(i);
        posJ.push_back(j);
        Bary[i+step][j]=false;
        go(ary, i+step, j, velikost, Bary, posI, posJ);
    }
    else if (InAry(velikost, step, j, 1) && Bary[i][j+step]==1)
    {
        posI.push_back(i);
        posJ.push_back(j);
        Bary[i][j+step]=false;
        go(ary, i, j+step, velikost, Bary, posI, posJ);
    }
    else if (InAry(velikost, step, i, 0) && Bary[i-step][j]==1)
    {
        posI.push_back(i);
        posJ.push_back(j);
        Bary[i-step][j]=false;
        go(ary, i-step, j, velikost, Bary,posI, posJ);
    }
    else if (InAry(velikost, step, j, 0) && Bary[i][j-step]==1)
    {
        posI.push_back(i);
        posJ.push_back(j);
        Bary[i][j-step]=false;
        go(ary, i, j-step, velikost, Bary, posI, posJ);
    }
    else{
        if (posI.size()==1){
            cout    <<endl<<  "Bludiste nema reseni";
            return 1;
        }
        posI.pop_back();
        posJ.pop_back();
        go(ary, posI[posI.size()], posJ[posJ.size()], velikost, Bary, posI, posJ);
    }

}

/**
 *
 * @param posI zaznam cesty X-ove souradnice
 * @param posJ zaznam cesty Y-ove souradnice
 * @return Vrati zapis cesty do
 */

string trackWay(const std::vector<int> &posI, const std::vector<int> &posJ){
    int a;
    char b;


    for (int i = 0; i < (int)posI.size(); ++i) {
        a=('a'+posJ[i]);
        b=(char)a;
        if (posI.size()-1==i)
        {
            OK<<(posI[i]+1)<<b<<".";
        }
        else
        {
            OK<<(posI[i]+1)<<b<<", ";
        }

    }
    return OK.str();

}

int main()
{
    int velikost;
    string track;
    cout<<"Zadej velikost bludiste:"<<endl;
    cin>>velikost;
    auto **ary=new int*[velikost];
    auto **Bary=new bool*[velikost];
    std::vector<int> posI;
    std::vector<int> posJ;

    Maze(velikost, ary, Bary);
    go(ary, 0, 0, velikost, Bary, posI, posJ);
    print(Bary, velikost);

    cout<<endl<<endl<<endl;

    if (posI.size()!=1)
    {
        track=trackWay(posI, posJ);
        cout << track << endl;
    }

    for (int i = 0; i < velikost; ++i) {
        delete[] ary[i];
        delete[] Bary[i];
    }
    return 0;
}