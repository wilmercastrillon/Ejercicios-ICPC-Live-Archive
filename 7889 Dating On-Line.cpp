#include <stdio.h>
#include <math.h>
#include <algorithm>

using namespace std;

double ar[100010], ar2[100010];
double ang, pi = acos(-1);

int main(){
    int n, pos1, pos2;
    double res, res2;

    while(scanf("%d", &n) != EOF){
        for(int i = 0; i < n; i++){
            scanf("%lf", &ar[i]);
        }

        sort(ar, ar+n);
        pos1 = 0;
        pos2 = n-1;
        for(int i = n-1; i >= 0; i-=2){
            ar2[pos1++] = ar[i];
        }
        pos1 = 0;
        for(int i = n-2; i >= 0; i-=2){
            ar2[(n-pos1)-1] = ar[i];
            pos1++;
        }

        ang = (360.0/n)*(pi/180.0);//convertir a radianes
        res = 0.5*ar2[0]*ar2[n-1]*sin(ang);
        for(int i = 1; i < n; i++){
            res += 0.5*ar2[i]*ar2[i-1]*sin(ang);
        }

        printf("%.3f\n", res);
    }

    return 0;
}


