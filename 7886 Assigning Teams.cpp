#include <stdio.h>
#include <algorithm>

using namespace std;

int main(){
    int ar[4];
    while(scanf("%d %d %d %d", &ar[0], &ar[1], &ar[2], &ar[3]) == 4){
        sort(ar, ar+4);
        printf("%d\n", abs((ar[0]+ar[3])-(ar[1] + ar[2])));
    }
}


