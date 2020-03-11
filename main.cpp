#include <iostream>
#include <vector>
#include <queue>
#include <functional>

const int INF = (1<<29);
using namespace std;

int mini( int a, int b ) {
    return ( a < b ) ? a : b;
}

class Graf_ponderat {
private:
    static const int maxNod = 100;
    vector< pair< int, int> > v[maxNod];                             ///presupun ca am maxim maxNod noduri intr-un graf
    void printare_bfs( int drum[], int nod1, int nod2 );         ///le retin ca lista de adiacenta; .first va contine nodul in care mergem, si .second ponderea muchiei
    void dfs_conex( bool nod[], int poz );
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

    friend ostream &operator <<( ostream& afisare, const Graf_ponderat &g );

    void bfs_bellman_ford(int nod1, int nod2);

    void pondere_roy_floyd();

    bool conex();

    Graf_ponderat &operator *(const Graf_ponderat & g2 );
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
    for ( i = 0; i < maxNod; i++ )
        for ( j = 0; j < g.get_v_size( i ); j++ )
            v[i].push_back( g.get_nod( i, j ) );
}

Graf_ponderat::~Graf_ponderat() {///destructor
    for( int i = 0; i < maxNod; i++ )
        v[i].clear();
}

ostream &operator <<( ostream& afisare, const Graf_ponderat &g ) {
    int i, j;
    for ( i = 0; i < Graf_ponderat::maxNod; i++ )
        for ( j = 0; j < g.v[i].size(); j++ )
            if ( i < g.v[i][j].first ) ///fiind graf neorientat, voi afisa o singura data muchiile
                afisare<<"Exista drum de la nodul " << i << " la nodul " << g.v[i][j].first <<" cu ponderea " << g.v[i][j].second << "\n";
    return afisare;
}

void Graf_ponderat::bfs_bellman_ford(int nod, int nod2) {
    int nod1 = nod, i, drum[maxNod], cost[maxNod];
    queue < int > bellman;
    for ( i = 0; i < maxNod; i++ ) {
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
    for ( i = 0; i < maxNod; i++ )
        if ( v[i].empty() == 0 )
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

void Graf_ponderat::dfs_conex(bool *nod, int poz) {
    int i;
    nod[poz] = true;
    for ( i = 0; i < v[poz].size(); i++ )
        if ( nod[v[poz][i].first] == false )
            dfs_conex( nod, v[poz][i].first );
}

bool Graf_ponderat::conex() {
    bool vizitat[maxNod] = {false};
    int i = 0;
    while ( v[i].empty() )
        i++;
    dfs_conex( vizitat, i );
    for ( i = 0; i < maxNod; i++ )
        if ( v[i].empty() == 0 && vizitat[i] == false )
            return false;
    return true;
}

Graf_ponderat& Graf_ponderat::operator *(const Graf_ponderat &g2) {
    int i, j, k;
    bool ok = true, gasit;
    try {
        for ( i = 0; i < maxNod; i++ )
            if ( this->v[i].empty() != g2.v[i].empty() )
               __throw_invalid_argument( "Grafurile nu au aceeasi multime de muchii. ");
    }
    catch ( const invalid_argument &e ){
        cout << e.what();
        ok = false;
    }

    if ( ok == true ) {
        for ( i = 0; i < maxNod; i++ ) {
            for ( j = 0; j < v[i].size(); j++ ) {
                gasit = false;
                for ( k = 0; k < g2.v[i].size() && gasit == false; k++ ) {
                    if ( v[i][j].first == g2.v[i][j].first ) {
                        gasit = true;
                        v[i][j].second = mini( v[i][j].second, g2.v[i][j].second );
                    }
                }
                if ( gasit == false ) {
                    v[i].erase( v[i].begin() + j, v[i].begin() + j + 1 );
                }
            }
        }
        return *this;
    }
    else
        __throw_bad_function_call();
}

int main() {
    try {
        Graf_ponderat g;
        cout << g;
        g.bfs_bellman_ford(1, 2);
        g.pondere_roy_floyd();
        cout << ((g.conex() == true) ? "Graful este conex\n" : "Graful nu este conex\n");
        Graf_ponderat g2;
        cout << g * g2;
        Graf_ponderat g3;       ///TODO
        cout << g * g2 * g;
    }
    catch (const bad_function_call &e){
        cout << "\"Alta-ntrebare?!\"\n";
    }
    return 0;
}