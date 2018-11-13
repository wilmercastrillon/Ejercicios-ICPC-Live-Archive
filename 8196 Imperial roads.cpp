#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <queue>
#include <map>

using namespace std;

int padre[100010];
void iniciar(int n){
    for (int i = 0; i < n; i++) padre[i] = i;
}
int raiz(int x){
    if(x == padre[x]) return x;
    else return padre[x] = raiz(padre[x]);
}

typedef pair<int, int> ii;
typedef pair<int, ii> piii;//peso, origen y destino
typedef vector<ii> vii;
typedef vector<vii> vvii;//peso, destino
#define mpiii(a, b, c) piii(a, ii(b, c))
#define MAX 100010

int p[MAX], d[MAX], peso[MAX], spt[MAX][17], mayor[MAX][17];//padre, deep, table
vector<piii> listaInc;//lista de incidencia
vvii grafo;

int kruskal(int nodos){
	sort(listaInc.begin(), listaInc.end());
	iniciar(nodos+1);
	int acum = 0, ejes = 0, n = nodos - 1;
	ii par;

	for (int i = 0; i < listaInc.size(); i++) {
        par = listaInc[i].second;
		if (raiz(par.first) != raiz(par.second)) {
			ejes++;
			padre[raiz(par.first)] = raiz(par.second);
			grafo[par.first].push_back(ii(listaInc[i].first, par.second));
			grafo[par.second].push_back(ii(listaInc[i].first, par.first));
			//printf("conexion %d a %d con peso %d\n", par.first, par.second, listaInc[i].first);
			acum += listaInc[i].first;
			if(ejes == n) return acum;
		}
	}
	return -1;
}

void dfs(int nodo, int deep, int ant){
    d[nodo] = deep;
    p[nodo] = ant;
    ii par;

    for(int i = 0; i < grafo[nodo].size(); i++){
        par = grafo[nodo][i];
        if(d[par.second] != -1) continue;
        peso[par.second] = par.first;
        dfs(par.second, deep+1, nodo);
    }
}

void proceso(int n){//spt[i][j] = (2^j)-th ancestro de i
    memset(d, -1, sizeof(d));
    memset(mayor, 0, sizeof(mayor));
    memset(peso, 0, sizeof(peso));
    dfs(0, 0, -1);
    memset(spt, -1, sizeof(spt));

    for(int i = 0; i < n; i++){
        spt[i][0] = p[i];
        mayor[i][0] = peso[i];
    }

    for(int j = 1; 1 << j < n; j++)
    for(int i = 0; i < n; i++)
        if(spt[i][j-1] != -1){
            spt[i][j] = spt[spt[i][j-1]][j-1];
            mayor[i][j] = max(mayor[i][j-1], mayor[spt[i][j-1]][j-1]);
        }
}

int LCA(int u, int v){
    if(d[u] < d[v]) swap(u, v);//v debe estar arriba de u

    for(int i = 16; i >= 0; i--)//subimos a u
        if(d[u] - (1<<i) >= d[v])
            u = spt[u][i];

    if(u == v) return u;

    for(int i = 16; i >= 0; i--)
        if(spt[u][i] != spt[v][i]){//spt[u][i] != -1 &&
            u = spt[u][i];
            v = spt[v][i];
        }

    return p[v];
}

int maxEdge(int u, int v){
    if(d[u] < d[v]) swap(u, v);//v debe estar arriba de u
    int may = 0;

    for(int i = 16; i >= 0; i--)//subimos a u
        if(d[u] - (1<<i) >= d[v]){
            may = max(may, mayor[u][i]);
            u = spt[u][i];
        }
    return may;
}

int main(){
    int n, m, x, y, z, q, u, v, lca;

    while(scanf("%d %d", &n, &m) != EOF){
        listaInc.clear();
        grafo.assign(n+1, vii(0));
        map<ii, int> mapa;

        for(int i = 0; i < m; i++){
            scanf("%d %d %d", &x, &y, &z);
            x--;
            y--;
            listaInc.push_back(mpiii(z, x, y));
            mapa[ii(min(x, y), max(x, y))] = z;
        }

        int MST = kruskal(n);
        //printf("MST = %d\n", MST);
        proceso(n);

        scanf("%d", &q);
        int peso, mayorArista;
        ii par;
        while(q--){
            scanf("%d %d", &u, &v);
            u--;
            v--;
            lca = LCA(u, v);
            //printf("LCA = %d\n", lca+1);
            mayorArista = max(maxEdge(u, lca), maxEdge(v, lca));
            //printf("maxEdge: %d\n", mayorArista);
            peso = mapa[ii(min(u, v), max(u, v))];
            //printf("pesa %d\n", peso);
            printf("%d\n", MST + peso - mayorArista);
        }
    }

	return 0;
}


