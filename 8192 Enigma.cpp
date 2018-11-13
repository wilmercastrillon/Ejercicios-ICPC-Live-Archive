#include <cstdio>
#include <string.h>

using namespace std;

char num[1010];
int memo[1010][1010];
int n, pot[1010], len;

void pre(int n){
    pot[0] = 1 % n;
    for(int i = 1; i < len; i++){
        pot[i] = (pot[i-1] * 10) % n;
        //printf("10^%d mod %d = %d\n", i, n, pot[i]);
    }
}

int modulo(int a, int b, int pos){
    return ((a * pot[(len-pos)-1]) + b) % n;
}

bool dp(int pos, int mod){
    if(pos >= len) return (mod == 0)? 1: 0;
    if(memo[pos][mod] != -1) return memo[pos][mod];

    if(num[pos] == '?'){
        int con = 0;
        for(int i = 0; i < 10; i++){
            if(dp(pos+1, modulo(i, mod, pos))) con++;
        }
        memo[pos][mod] = (int)(con > 0);
    }else{
        memo[pos][mod] = dp(pos+1, modulo(num[pos]-'0', mod, pos));
    }
    return memo[pos][mod];
}

int main(){

    while(scanf("%s %d", &num, &n) != EOF){
        len = strlen(num);
        pre(n);
        memset(memo, -1, sizeof(memo));
        int mod = 0, con;

        for(int i = 0; i < len; i++){
            if(num[i] == '?'){
                con = 0;
                for(int j = (i)? 0: 1; j < 10; j++){
                    num[i] = '0' + j;
                    if(dp(i+1, modulo(j, mod, i))){
                        mod = modulo(j, mod, i);
                        break;
                    }else{
                        con++;
                    }
                }
                if(con == 10){
                    i = len;
                    mod = -1;
                }
            }else{
                mod = modulo(num[i]-'0', mod, i);
            }
        }

        if(mod == -1){
            printf("*\n");
        }else{
            printf("%s\n" , num);
        }
    }

    return 0;
}


