// O( V^2 * E ) V up to 2w
#define SZ( c ) ( (int)( c ).size() )
class MaxFlow {
 public:
  static const int MAXV = 5e3 + 10;
  static const int INF = 1e18;
  struct Edge {
    int v, c, r;
    Edge( int _v, int _c, int _r ) : v( _v ), c( _c ), r( _r ) {}
  };
  int s, t;
  vector< Edge > G[ MAXV * 2 ];
  int iter[ MAXV * 2 ], d[ MAXV * 2 ], gap[ MAXV * 2 ], tot;
  void Init( int x ) {
    tot = x + 2;
    s = x + 1, t = x + 2;
    for ( int i = 0; i <= tot; i++ ) {
      G[ i ].clear();
      iter[ i ] = d[ i ] = gap[ i ] = 0;
    }
  }
  void AddEdge( int u, int v, int c ) {
    G[ u ].push_back( Edge( v, c, SZ( G[ v ] ) ) );
    G[ v ].push_back( Edge( u, 0, SZ( G[ u ] ) - 1 ) );
  }
  int DFS( int p, int flow ) {
    if ( p == t ) return flow;
    for ( int &i = iter[ p ]; i < SZ( G[ p ] ); i++ ) {
      Edge &e = G[ p ][ i ];
      if ( e.c > 0 && d[ p ] == d[ e.v ] + 1 ) {
        int f = DFS( e.v, min( flow, e.c ) );
        if ( f ) {
          e.c -= f;
          G[ e.v ][ e.r ].c += f;
          return f;
        }
      }
    }
    if ( ( --gap[ d[ p ] ] ) == 0 )
      d[ s ] = tot;
    else {
      d[ p ]++;
      iter[ p ] = 0;
      ++gap[ d[ p ] ];
    }
    return 0;
  }
  int Solve() {
    int res = 0;
    gap[ 0 ] = tot;
    for ( res = 0; d[ s ] < tot; res += DFS( s, INF ) )
      ;
    return res;
  }
};
