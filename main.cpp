#include <iostream>
#include <vector>
#include <queue>
const int INF = (1<<29);
using namespace std;

class Graf_ponderat {
private:
    vector< pair< int, int> > v[100];                             ///presupun ca am maxim 100 noduri intr-un graf
    void printare_bfs( int drum[], int nod1, int nod2 );         ///le retin ca lista de adiacenta; .first va contine nodul in care mergem, si .second ponderea muchiei
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

    friend ostream &operator <<( ostream& afisare, Graf_ponderat &g );

    void bfs_bellman_ford(int nod1, int nod2);

    void pondere_roy_floyd();
};

Graf_ponderat::Graf_ponderat() {///constructor initializare
    int nod1, nod2, pondere;
    cout<<"introduce o muchie intre doua noduri si ponderea ei, sub forma \"nod1 nod2 pondere\"\n";
    cout<<"pt a termina de introdus graful, introduceti -1 -1 -1\n";
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

ostream &operator <<( ostream& afisare, Graf_ponderat &g ) {
    int i, j;
    for ( i = 0; i < 100; i++ )
        for ( j = 0; j < g.v[i].size(); j++ )
            if ( i < g.v[i][j].first ) ///fiind graf neorientat, voi afisa o singura data muchiile
                afisare<<"Exista drum de la nodul " << i << " la nodul " << g.v[i][j].first <<" cu ponderea " << g.v[i][j].second << "\n";
    return afisare;
}

void Graf_ponderat::bfs_bellman_ford(int nod, int nod2) {
    int nod1 = nod, i, drum[100], cost[100];
    queue < int > bellman;
    for ( i = 0; i < 100; i++ ) {
        drum[i] = cost[i] = INF;
    }
    cost[nod1] = 0;
    for ( i = 0; i < v[nod1].size(); i++ ) {
        bellman.push( v[nod1][i].first );
        cost[ v[nod1][i].first ] = v[nod1][i].second;
        drum[ v[nod1][i].first ] = nod1;
    }
    while ( !bellman.empty() ) {
        nod1 = bellman.front();
        for ( i = 0; i < v[nod1].size(); i++ ) {
            if ( cost[nod1] + v[nod1][i].second < cost[ v[nod1][i].first ] ) {
                bellman.push( v[nod1][i].first );
                cost[ v[nod1][i].first ] = cost[nod1] + v[nod1][i].second;
                drum[ v[nod1][i].first ] = nod1;
            }
        }
        bellman.pop();
    }
    cout << "Drumul de pondere minima intre cele doua noduri este: ";
    printare_bfs( drum, nod, nod2 );
    cout << "\n";
}

void Graf_ponderat::printare_bfs( int drum[], int nod1, int nod2 ) {
    if ( nod2 != nod1 )
        printare_bfs( drum, nod1, drum[nod2] );
    cout << nod2 << " ";
}

void Graf_ponderat::pondere_roy_floyd() {
    int i, maxi, j, k;
    maxi = 0;
    for ( i = 0; i < 100; i++ )
        if ( v[i].size() > 0 )
            maxi = i;
    int matrix[maxi+1][maxi+1];
    for ( i = 0; i <= maxi; i++ )
        for ( j = 0; j <= maxi; j++ ) {
            if ( i == j )
                matrix[i][j] = 0;
            else
                matrix[i][j] = INF;
        }
    for ( i = 0; i <= maxi; i++ ) {
        for ( j = 0; j < v[i].size(); j++ ) {
            matrix[i][v[i][j].first] = v[i][j].second;
        }
    }

    for ( k = 0; k <= maxi; k++  )
        for ( i = 0; i <= maxi; i++ )
            for ( j = 0; j <= maxi; j++ )
                if ( matrix[i][k] + matrix[k][j] < matrix[i][j] )
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
     for ( i = 0; i <= maxi; i++ ) {
         for (j = 0; j <= maxi; j++) {
             if ( matrix[i][j] != INF )
                cout << matrix[i][j] << " ";
             else
                 cout << "NIL ";
         }
         cout << "\n";
     }
}


int main() {
    Graf_ponderat g;
    cout << g;
    g.bfs_bellman_ford( 1, 4 );
    g.pondere_roy_floyd();
    return 0;
}