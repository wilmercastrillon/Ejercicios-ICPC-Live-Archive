#include <stdio.h>

using namespace std;

int main(){
    int a, b, c, d, e, f, res;
    while(scanf("%d %d %d", &a, &b, &c) != EOF){
        scanf("%d %d %d", &d, &e, &f);
        res = 0;
        if(d > a) res += d-a;
        if(e > b) res += e-b;
        if(f > c) res += f-c;
        printf("%d\n", res);
    }

    return 0;
}


