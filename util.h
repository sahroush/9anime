#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define and &&
#define or ||
#define endl printf("\n");

void swap(int* a, int* b){
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void shuffle_card(int card[][11]) {
    int r;
    for (int i = 0; i < 44; i++)
        card[i/11][i%11] = i;
    srand(time(NULL));
    for (int i = 43; i > 0; i--) {
        r = rand() % i;
        swap(&card[i/11][i%11], &card[r/11][r%11]);
    }
}

void flush(){
    while(getchar() != '\n')
        continue;
}

void print(char c, int n){
    for(int i = 0 ; i < n ; i ++)
        printf("%c", c);
}


int askbot(int x){
    printf("Is player %x human? (y/n)\n", x);
    char res = getchar();
    flush();
    while(res != 'y' and res != 'n'){
        printf("Invalid input, choose between y and n\n");
        res = getchar();
        flush();
    }
    return (res == 'n');
}

void printjadval(int sz, int n, char* c, int* x){
    print('-', sz);
    printf("\n|");
    for(int i = 0 ; i < n ; i ++){
        printf("%c%d|", *(c+i), *(x+i));
    }
    printf("\n");
    print('-', sz);
    printf("\n|");
    for(int i = 0 ; i < n ; i ++){
        int len = 2;
        if(*(x + i) > 9)len ++;
        len --;
        if(i > 9)len --;
        print(' ', len);
        printf("%d|", i);
    }
    printf("\n");
    print('-', sz);
    printf("\n");
}

int gethokm(int a[11]){
    printf("Your cards are:\n");
    char c[5];
    int x[5];
    int sz = 1;
    int has[4] = {0,0,0,0};
    for(int i = 0 ; i < 5 ; i ++){
        c[i] = (a[i]/11)+'A';
        x[i] = a[i]%11;
        sz += 2 + (x[i] > 9);
        sz ++;
        has[c[i] - 'A'] = 1;
    }
    printjadval(sz, 5, &(c[0]), &(x[0]));
    printf("Choose your hokm, your options are: (");
    for(int i = 0,  j = 0 ; i < 4 ; i ++)if(has[i]){
        if(j)printf("/");
        else j = 1;
        printf("%c", (char)(i + 'A'));
    }
    printf(")\n");
    char res = getchar();
    flush();
    while(res - 'A' < 0 or res - 'A' > 3 or !has[res - 'A']){
        printf("Invalid input, your choices are: (");
        for(int i = 0,  j = 0 ; i < 4 ; i ++)if(has[i]){
            if(j)printf("/");
            else j = 1;
            printf("%c", (char)(i + 'A'));
        }
        printf(")\n");
        res = getchar();
        flush();
    }
    return res - 'A';
}

int botstart(int a[11], int hokm){ //returns index in arr
    int allhokm = 1;
    for(int i = 0 ; i < 11 ; i ++){
        if(a[i] == -1)
            continue;
        if(a[i]/11 != hokm)
            allhokm = 0;
    }
    if(allhokm){
        int mx = 0;
        for(int i = 0 ; i < 11 ; i ++)
            if(a[i] > a[mx])
                mx = i;
        return mx;
    }
    else{
        int mx = 100;
        for(int i = 0 ; i < 11 ; i ++)if(a[i]/11 != hokm){
            if(mx == 100)
                mx = i;
            if(a[i]%11 > a[mx]%11)
                mx = i;
        }
        return mx;
    }
}

void fill(int a[], int sz, int val){
    for(int i = 0 ; i < sz ; i ++)
        a[i] = val;
}

int num(char c){
    return (c >= '0' and c <= '9');
}

int getint(int mx){
    int x = 0;
    int ok = 0;
    //printf("%d\n", mx);
    while(1){
        char c = getchar();
        //  \n!!!
        if(c == '\n'){
            if(ok){
                return x;
            }
            printf("Invalid input!\n");
            flush();
            x = 0;
            ok = 0;
            continue;
        }
        if(!num(c)){
            printf("Invalid input!\n");
            flush();
            x = 0;
            ok = 0;
            continue;
        }
        else{
            x = x * 10 + (c - '0');
            ok = 1;
            if(x >= mx){
                printf("Invalid input!\n");
                flush();
                x = 0;
                ok = 0;
                continue;
            }
        }
    }
    return 0;
}

int botplay(int a[11], int hokm, int zamin){
    int res = -1;
    for(int i = 0 ; i < 11 ; i ++)if(a[i] != -1){
        if(a[i] / 11 == zamin){
            res = i;
        }
    }
    if(res != -1){//has zamin -> max
        for(int i = 0 ; i < 11 ; i ++)if(a[i] != -1){
            if(a[i] / 11 == zamin and a[i] > a[res])
                res = i;
        }
        return res;
    }
    else{//hokm?
        for(int i = 0 ; i < 11 ; i ++)if(a[i] != -1){
            if(a[i] / 11 != hokm){
                res = i;
            }
        }
        if(res == -1){//hokm.
            for(int i = 0 ; i < 11 ; i ++)if(a[i] != -1 and a[i]/11 == hokm){
                res = i;
            }
            for(int i = 0 ; i < 11 ; i ++)if(a[i] != -1 and a[i]/11 == hokm){
                if(a[i] > a[res])
                    res = i;
            }
            return res;
        }
        else{//!hokm.
            for(int i = 0 ; i < 11 ; i ++)if(a[i] != -1 and a[i]/11 != hokm){
                res = i;
            }
            for(int i = 0 ; i < 11 ; i ++)if(a[i] != -1 and a[i]/11 != hokm){
                if(a[i] > a[res])
                    res = i;
            }   
            return res;
        }
    }
}

int playerstart(int a[11]){
    int n = 0;
    for(int i = 0 ; i < 11 ; i ++)
        n += (a[i] != -1);
    char c[11];
    int x[11];
    int isok[11];
    fill(isok, 11, 0);
    int sz = 1, j = 0;
    for(int i = 0 ; i < 11 ; i ++)if(a[i] != -1){
        c[j] = a[i]/11 + 'A';
        x[j] = a[i] % 11;
        sz += 2 + (x[i] > 9);
        sz ++;
        j ++;
        isok[i] = 1;
    }
    printf("Starting a new round, your options are:\n");
    printjadval(sz, j, &(c[0]), &(x[0]));
    int res = getint(j);
    res = (c[res] - 'A') * 11 +  x[res];
    for(int i = 0 ; i < 11 ; i ++)if(a[i] == res){
        return i;
    }
    return -1111110; //wtf?
}


int playerplay(int a[11], int zamin){
    int n = 0;
    for(int i = 0 ; i < 11 ; i ++)
        n += (a[i] != -1);
    char c[11];
    int x[11];
    int isok[11];
    fill(isok, 11, 0);
    int sz = 1, j = 0;
    for(int i = 0 ; i < 11 ; i ++)if(a[i] != -1){
        c[j] = a[i]/11 + 'A';
        x[j] = a[i] % 11;
        sz += 2 + (x[j] > 9);
        sz ++;
        j ++;
        isok[i] = 1;
    }
    printf("Your cards are:\n");
    printjadval(sz, j, &(c[0]), &(x[0]));
    printf("Your options are:\n");
    int haszamin = 0;
    for(int i = 0 ; i < j ; i ++){
        if(c[i] - 'A' == zamin)
            haszamin = 1;
    }
    if(haszamin){
        for(int i = 0 ; i < 11 ; i ++)if(isok[i]){
            if(a[i] / 11 != zamin)
                isok[i] = 0;
        }
    }
    sz = 1, j = 0;
    for(int i = 0 ; i < 11 ; i ++)if(isok[i]){
        c[j] = a[i]/11 + 'A';
        x[j] = a[i] % 11;
        sz += 2 + (x[j] > 9);
        sz ++;
        j ++;
    }
    printjadval(sz, j, &(c[0]), &(x[0]));
    int res = getint(j);
    res = (c[res] - 'A') * 11 +  x[res];
    for(int i = 0 ; i < 11 ; i ++)if(a[i] == res){
        return i;
    }
    return -1111110; //wtf?
}

void draw(int ra, int rb, int seta, int setb, int pl[4], int hokm, int zamin){
    printf("First Team:\t Sets won: %d\t Rounds won: %d\n", seta, ra);
    printf("Second Team:\t Sets won: %d\t Rounds won: %d\n", setb, rb);
    printf("Bakhsh name: %c\n", hokm + 'A');
    if(zamin != -1){
        printf("Karte zamine: %c\n", zamin + 'A');
    }
    print(' ', 49);
    printf("P3");
    endl
    print(' ', 2);
    print('-', 100);
    endl
    const int h = 30;
    const int boz = 50;
    const int khar = boz*2 - 6;
    for(int i = 0 ; i < h ; i ++){
        if(i == 0){
            print(' ', 2);
            print('|', 1);
            print(' ', 46);
            if(pl[2] == -1){
                print('?', 2);
                print(' ', boz);
                print('|', 1);
            }
            else{
                printf("%c%d", 'A' + (pl[2] / 11),  pl[2]%11);
                print(' ', boz - ((pl[2]%11) > 9));
                print('|', 1);
            }
        }
        else if(i == h/2){
            printf("P2");
            print('|', 1);
            if(pl[1] == -1){
                print('?', 2);
                print(' ', khar);
            }
            else{
                printf("%c%d", 'A' + (pl[1] / 11),  pl[1]%11);
                int len = khar - ((pl[1]%11) > 9);
                if(pl[3] != -1){
                    len -= (pl[3] % 11) > 9;
                }
                print(' ', len);
            }
            if(pl[3] == -1){
                print('?', 2);
                print('|', 1);
            }
            else{
                printf("%c%d", 'A' + (pl[3] / 11),  pl[3]%11);
                print('|', 1);
            }
            printf("P4");
        }
        else{
            print(' ', 2);
            print('|', 1);
            print(' ', 98);
            print('|', 1);
        }
        endl
    }
    print(' ', 2);
    print('|', 1);
    print(' ', 46);
    if(pl[0] == -1){
        print('?', 2);
        print(' ', boz);
        print('|', 1);
    }
    else{
        printf("%c%d", 'A' + (pl[0] / 11),  pl[0]%11);
        print(' ', boz - ((pl[0]%11) > 9));
        print('|', 1);
    }
    endl
    print(' ', 2);
    print('-', 100);
    endl
    print(' ', 49);
    printf("P1");
    endl
}