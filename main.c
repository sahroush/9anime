#include "util.h"

int main(){
    int cards[4][11];
    int isbot[4] = {0};
    for(int i = 1 ; i <= 4 ; i ++){
        isbot[i-1] = askbot(i);
    }
    int seta = 0, setb = 0;
    //7 sets, 11 rounds each
    while(seta < 7 and setb < 7){
        shuffle_card(cards);
        int hokm;
        if(isbot[0]){
            hokm = cards[0][0]/11;
        }
        else{
            hokm = gethokm(cards[0]);
        }
        int cur = 0;
        int ra = 0, rb = 0;
        for(int round = 0; round < 11 ; round ++){
            int plays[4];
            fill(plays, 4, -1);
            int zamin = -1;
            int win = cur;
            for(int i = 0 ; i < 4 ; i ++, cur ++, cur %= 4){
                system("clear");
                draw(ra, rb, seta, setb, plays, hokm, zamin);
                if(isbot[cur]){
                    printf("Bot %d's turn\n", cur+1);
                    if(zamin == -1){
                        plays[cur] = botstart(cards[cur], hokm);
                        int x = plays[cur];
                        zamin = cards[cur][x]/11;
                        plays[cur] = cards[cur][x];
                        cards[cur][x] = -1;
                    }
                    else{
                        plays[cur] = botplay(cards[cur], hokm, zamin);
                        int x = plays[cur];
                        plays[cur] = cards[cur][x];
                        cards[cur][x] = -1;
                    }
                    sleep(1);
                }
                else{
                    printf("Player %d's turn\n", cur+1);
                    if(zamin == -1){
                        plays[cur] = playerstart(cards[cur]);
                        int x = plays[cur];
                        zamin = cards[cur][x]/11;
                        plays[cur] = cards[cur][x];
                        cards[cur][x] = -1;
                    }
                    else{
                        plays[cur] = playerplay(cards[cur], zamin);
                        int x = plays[cur];
                        plays[cur] = cards[cur][x];
                        cards[cur][x] = -1;
                    }
                    sleep(1);
                }
                system("clear");
                draw(ra, rb, seta, setb, plays, hokm, zamin);
                sleep(1);
            }
            //winner?
            int x = win;
            for(int i = 0 ; i < 4 ; i ++){
                if(plays[win]/11 == hokm){
                    if(plays[x]/11 == hokm and plays[x] > plays[win]){
                        win = x;
                    }
                }
                else{
                    if(plays[x]/11 == hokm){
                        win = x;
                    }
                    else if(plays[x]%11 > plays[win]%11)
                        win = x;
                }  
                x += 1;
                x %= 4;
            }
            if(win%2){
                rb ++;
                printf("Second team won the round!\n");
            }
            else{
                ra ++;
                printf("First team won the round!\n");
            }
            cur = win;
            sleep(3);
        }
        if(ra > rb){
            seta ++;
            printf("First team won the set!\n");
        }
        else{
            setb ++;
            printf("Second team won the set!\n");
        }
        sleep(3);
    }
    return 0;
}
