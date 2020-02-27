#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graf_ponderat {
vector< pair< int, int> > v[100];  ///presupun ca am maxim 100 noduri intr-un graf
                                  ///le retin ca lista de adiacenta; .first va contine nodul in care mergem, si .second ponderea muchiei
public:
  Graf_ponderat();  ///constructor initializare


  int get_v_size( int x ) const{
    return v[x].size();
  }
  pair<int,int> get_nod( int x, int y ) const {
    return v[x][y];
  }
  Graf_ponderat( const Graf_ponderat &g );  ///constructor copiere


  ~Graf_ponderat();    ///destructor

};

Graf_ponderat::Graf_ponderat() {///constructor initializare
  int nod1, nod2, pondere;
  cout<<"introduce o muchie intre doua noduri si ponderea ei, sub forma \"nod1 nod2 pondere\"\n";
  cout<<"pt a termina de introdus graful, introduceti -1 -1 -1";
  cin >> nod1 >> nod2 >> pondere;
  while ( nod1 > -1 ) {
    v[nod1].push_back( make_pair(nod2, pondere ) );
    v[nod2].push_back( make_pair(nod1, pondere ) );
    cin >> nod1 >> nod2 >> pondere;
  }
}

Graf_ponderat::Graf_ponderat( const Graf_ponderat &g ) {///constructor copiere
  int i, j;
  for ( i = 0; i < 100; i++ )
    for ( j = 0; j < g.get_v_size( i ); j++ )
      v[i].push_back( g.get_nod( i, j ) );
}

Graf_ponderat::~Graf_ponderat() {///destructor
  for( int i = 0; i < 100; i++ )
    v[i].clear();
}
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
