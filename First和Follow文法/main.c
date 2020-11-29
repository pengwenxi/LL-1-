//
//  main.c
//  First和Follow文法
//
//  Created by 大橘猪猪侠 on 2020/11/27.
//

#include <stdio.h>

/*
 E   ->  TE'
 E'  -> +TE'|e
 T   ->  FT'
 T'  -> *FT'|e
 F   -> (E) |id
 
 E'变为H
 T'变为Y
 
 E  ->  TH
 H  -> +TH|e
 T  ->  FY
 Y  -> *FY|e
 F  -> (E)|id
 
 */
char *str[5][6] = {
    "E","T","H"," "," "," ",
    "H","+","T","H","|","e",
    "T","F","Y"," "," "," ",
    "Y","*","F","Y","|","e",
    "F","(","E",")","|","id",
};



typedef struct{
    char firstData[15];
    char followData[15];
    char equalFirst;
    char equalFollow;
}follow;



follow fE;
follow fH;
follow fT;
follow fY;
follow fF;

//获取找到的相同的在哪一行
int getindex(char c){
    char N[5];
    int num = 0;
    for (int i = 0 ; i<5; i++) {
        N[i] = *str[i][0];
    }
    for (int i = 0; i<5; i++) {
        if(c == N[i]){
            num = i;
        }

    }
    return num;
}
//first文法，第一个参数传入所求的字母，第二个为在该首字母在哪一行，第三个为存储First的数组。
void getFirst(char c,int num,char *x){
    int index = num;
    int m;
    for (int i = num; i<5; i++) {
        for (int j = 1; j<6; j++) {
            m = getindex(*str[i][j]);
            if(m !=0){
                index = m;
                getFirst(*str[i][j], index,x);
            }else{
                m = index;
                x[4] = *str[m][j];
                if(*str[m][4] == '|'){
                    x[5] = ',';
                    x[6] = *str[m][5];
                    x[7] = '}';
                }
            }
            break;
        }
        break;
    }
}
//获取所有first文法，其实就是将代码封装了一下，方便打印输出
void getAllFirst(char c,char *First,int num){
    First[0] = c;
    First[1] = '-';
    First[2] = '>';
    First[3] = '{';
    getFirst(First[0], num, First);
    for (int i = 0; i<10; i++) {
        printf("%c",First[i]);
    }
    printf("\n");
}

int getindex2(char c){
    char N[5];
    int num = 0;
    for (int i = 0 ; i<5; i++) {
        N[i] = *str[i][0];
    }
    for (int i = 0; i<5; i++) {
        if(c == N[i]){
            num = i+1;
        }

    }
    return num;
}

//获取是否有想等的
int getEqual(char c,int index){
    int sum = 0;
    for (int i = 0; i<5; i++) {
        for (int j = 1; j<4; j++) {
            if(c == *str[i][j] && index != i){
                sum = sum*10+i;
                sum = sum*10+j;
            }
        }
    }
    return sum;
}
//前面为非终结符，则添加为first，前面没有，则添加为follow

void getFollow(char c,int num,char *first,follow *f){
    int sum = 0;
    int m,n,x,y;
    for (int i = 0; i<5; i++) {
        for (int j = 1; j<4; j++) {
            sum = getEqual(c, num);
            if(sum<100){
                m = sum/10;
                n = sum%10;
                if(!getindex(*str[m][n-1])&&!getindex(*str[m][n+1])){
                    f->followData[4] = *str[m][n+1];
                    f->followData[5] = ',';
                    f->followData[6] = '$';
                    f->followData[7] = '}';
                }else if (getindex(*str[m][n-1])&&!getindex(*str[m][n+1])){
                    f->equalFollow = *str[m][0];
                }
            }else{
                m = sum/1000;
                n = (sum/100)%10;
                x = (sum/10)%10;
                y = sum%10;
                if(n == 1){
                    if(getindex(*str[m][n+1])){
                        f->equalFollow = *str[m][0];
                    }
                }else{
                    if(!getindex(*str[m][n-1])&&getindex(*str[m][n+1])){
                        f->equalFirst = *str[m][0];
                    }
                }
               if(y == 1){
                   if(getindex(*str[x][y+1])){
                       f->equalFollow = *str[x][0];
                   }
                }else{
                    if(!getindex(*str[x][y-1])&&getindex(*str[x][y+1])){
                        f->equalFirst = *str[x][0];
                    }
                }
            }
            break;
        }
        break;
    }
}

//数组拷贝
void swap(char *m,char n[15]){
    int i = 0;
    while (n[i]!='\0') {
        m[i] = n[i];
        i++;
    }
}
//,char *x,char *y
void getAllFollow(char c,int num,follow *f){
    char x[15],y[15];
    
    f->equalFirst = ' ';
    f->equalFollow = ' ';
    f->followData[0] = c;
    f->followData[1] = '-';
    f->followData[2] = '>';
    f->followData[3] = '{';
    getFollow(c, num, NULL, f);
    
    if(f->equalFirst){
        switch (f->equalFirst) {
            case 'E':
                swap(x, fE.firstData);
                break;
            case 'H':
                swap(x, fH.firstData);
                break;
            case 'T':
                swap(x, fT.firstData);
                break;
            case 'Y':
                swap(x, fY.firstData);
                break;
            case 'F':
                swap(x, fF.firstData);
                break;
        }
    }
    if (f->equalFollow) {
        switch (f->equalFollow) {
            case 'E':
                swap(y, fE.followData);
                break;
            case 'H':
                swap(y, fE.followData);
                break;
            case 'T':
                swap(y, fT.followData);
                break;
            case 'Y':
                swap(y, fY.followData);
                break;
            case 'F':
                swap(y, fF.followData);
                break;
        }
    }
    
    int k = 4;
    int j = 4;
    if(f->equalFirst != ' '){
        while (x[k]!='}') {
            if(x[k] != 'e'){
                f->followData[j] = x[k];
                j++;
            }
            k++;
        }
    }
    int m = 4;
    if(f->equalFollow != ' '){
        while (y[m] != '}') {
            f->followData[j] = y[m];
            j++;
            m++;
        }
    }
    if(j!=4){
        f->followData[j] = '}';
    }
    
    
    int i = 0;
    while (f->followData[i]) {
        printf("%c",f->followData[i]);
        i++;
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    
    printf("公式:\n");
    for (int i = 0; i<5; i++) {
        for (int j = 0; j<6; j++) {
            printf("%c",*str[i][j]);
            if(j == 0){
                printf("->");
            }
            
        }
        printf("\n");
    }
    printf("\n");
    
    printf("First:\n");
    
    

    getAllFirst(*str[0][0], fE.firstData,0);
    getAllFirst(*str[1][0], fH.firstData,1);
    getAllFirst(*str[2][0], fT.firstData,2);
    getAllFirst(*str[3][0], fY.firstData,3);
    getAllFirst(*str[4][0], fF.firstData,4);

    
    printf("\n");

    printf("Follow:\n");

    getAllFollow(*str[0][0], 0, &fE);
    getAllFollow(*str[1][0], 1, &fH);
    getAllFollow(*str[2][0], 2, &fT);
    getAllFollow(*str[3][0], 3, &fY);
    getAllFollow(*str[4][0], 4, &fF);
    
//    getAllFollow(*str[0][0], 0, &fE, fE.firstData, fE.followData);
//    getAllFollow(*str[1][0], 1, &fH, fH.firstData, fE.followData);
//    getAllFollow(*str[2][0], 2, &fT, fH.firstData, fE.followData);
//    getAllFollow(*str[3][0], 3, &fY, fY.firstData, fT.followData);
//    getAllFollow(*str[4][0], 4, &fF, fY.firstData, fT.followData);

    
    
    
    
    return 0;
}
