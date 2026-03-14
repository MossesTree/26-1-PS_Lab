#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "userClasses.h"

int applyMyClasses(int my[], int msize, struct st_class* c[], int csize){
    int c_code, addMore;
    if(msize>=10)
        return msize;

    printf(">> Enter a class code > ");
    scanf("%d",&c_code);

    for(int i=0;i<csize;i++){
        if(c_code == c[i]->code){
            printf("[%d] %s [credit %d - %s]\n",c[i]->code,c[i]->name,c[i]->unit,kname[c[i]->grading-1]);
            for(int j=0;j<msize;j++){
                if(c_code == my[j]){
                    printf("You already have this class.\n");
                    break;
                }
            }
            my[msize] = c_code;
            msize = msize + 1;
            break;
        }
        if(i==csize-1)
            printf("No such code of class.\n");
    }

    printf("Add more? 1:Yes 2: No > ");
    scanf("%d",&addMore);

    if(addMore==1){
        return applyMyClasses(my,msize,c,csize);
    }
    else return msize;
}

void printMyClasses(int my[], int msize, struct st_class* c[], int csize){
    if(msize==0){
        printf("no class\n");
    }
    for(int i=0; i<msize; i++){
        for(int j=0; j<csize; j++){
            if(c[j]->code==my[i])
                printf("[%d] %s [credit %d - %s]\n",c[j]->code, c[j]->name, c[j]->unit, kname[c[j]->grading-1]);
        }
	}
}

void saveMyClass(int my[], int msize, struct st_class* c[], int csize){
    FILE* file = fopen("my_classes.txt", "w");

    int classes=0;
    int credit[]={0,0};
    
    if(file == NULL){
        printf("> Error: Cannot open my_classes.txt to save.\n");
        return;
    }

    // 내가 신청한 과목의 코드번호들을 텍스트 파일에 저장
    for(int i=0; i<msize; i++){
        for(int j=0; j<csize; j++){
            if(c[j]->code==my[i]){
                fprintf(file, "%d. [%d] %s [credit %d - %s]\n",i+1,c[j]->code, c[j]->name, c[j]->unit, kname[c[j]->grading-1]);
                classes++;
                if(c[j]->grading == 1)
                    credit[0] += c[j]->unit;
                else
                    credit[1] += c[j]->unit;
            }
        }
    }
    fprintf(file,"All: %d classes, %d credits(A+~F %d credits, P/F %d credits)\n",classes,credit[0]+credit[1],credit[0],credit[1]);
    fclose(file);
}
	