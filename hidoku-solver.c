#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int prcross(int cross[],int x,int y);
int cparr(int *arr1, int *arr2,int size);
int go(int cross[],int x,int y,int finish,int number ,int point[],int index, int points[][3],int lastindex);
int *find(int cross[],int y,int point[],int num);
int fsteps(int x1,int y1,int x2,int y2);
int max(int m,int n);


int pad=1; // 2 --> for hex and 1 -- > for rect
int sort(int arr[][3],int arr2[][3],int size);


int main(){

// Reading file section starts here .

FILE *fp = fopen("matrix.dat","r"); //creating file pointer

char type[10]; int n , m = 0 , x , y,counter , i , p =0 , help , help2 , finish;
int points[100][3],sortedpoints[100][3];


fscanf(fp,"%s\n%d",type,&n);

if (strcmp("rect",type) == 0) {fscanf(fp,"%d",&m); x = m+2;y=n+2; finish = n*m;}
else {x = (4*n - 1);y =(2*n + 1);pad=2;finish=(3*n*n-3*n+1);} // for hex input

int inp[x*y];

for(m = 0;m < x;m++)inp[m]= -1;counter = m;

if(pad == 1){
    for(n=1;n < (y-1);n++){

        inp[counter++]= -1;
        for(m=1;m < (x - 1);m++){
                fscanf(fp,"%d",&inp[counter++]);
                if(inp[counter - 1] != 0) {

                    points[p][0]= inp[counter - 1];

                    points[p][1]= n;

                    points[p++][2]= m;
                }


        }
        inp[counter++]= -1;
    }

}


else{
    help = 0;
    for(m=1;m<(y-1);m++){

        for(i=0;i< (x - (2*(n + help)-1));i+=2) inp[counter++]= -1;
        help2 = i / 2;
        for(i = 0;i<(2*(n + help) - 1);i+=2){
            fscanf(fp,"%d",&inp[counter++]);
            if(inp[counter - 1] != 0){
                    points[p][0] = inp[counter - 1];
                    points[p][1] = m;
                    points[p++][2] = i + help2;
            }
            inp[counter++]= -1;
        }

        for(i=0;i < (x - (2*(n + help +1)-1));i+=2) inp[counter++]= -1;

        if(m > (n - 1) ) help--; else help++;

    }
}


for(m = 0;m < x;m++)inp[counter++]= -1;


sort(points,sortedpoints,p);

fclose(fp);

// file reading finished

int point[2]={sortedpoints[0][1],sortedpoints[0][2]};

go(inp,x,y,finish,sortedpoints[0][0],point,0,sortedpoints,p-1);



return 0;
}







int sort(int arr[][3],int arr2[][3],int size){

int i , j ,counter;
for(i = 0; i < size;i++)
{

    counter = 0;
    for(j = 0;j<size;j++) if (arr[i][0] > arr[j][0]) counter++;

    arr2[counter][0] = arr[i][0];
    arr2[counter][1] = arr[i][1];
    arr2[counter][2] = arr[i][2];
}
return 0;
}

int go(int cross[],int x,int y,int finish,int number ,int point[],int index , int points[][3],int lastindex){

int i = -1 , j = -1,*point2 = (int*)malloc(2*sizeof(int));

if(index <= lastindex){
int dnum = abs(points[index][0] - number); //printf("%d",dnum);
int steps = fsteps(point[1],point[0],points[index][2],points[index][1]); //printf("  %d",steps);
if (steps > dnum) return 0;
if (dnum == 0) index++;}

int  *crossc =(int *) malloc(x*y*sizeof(int));


cparr(crossc,cross,x*y);

if(crossc[(point[0]*x) + point[1]] != number && crossc[(point[0]*x) + point[1]] != 0 ) {/*printf("X%i",crossc[(point[0]*x) + point[1]]);*/return 0;}  //** it means this cell of cross is -1 or predefined cell

if (number == finish && crossc[(point[0]*x) + point[1]] == number ){ prcross(crossc,x,y);/*puts("y");*/ return 0;} // means we have reached to the end of cross and we solved it
if (number == finish && crossc[(point[0]*x) + point[1]] == 0){crossc[point[0]*x + point[1]] = number ;prcross(crossc,x,y);return 0;} // same as upper condition
crossc[point[0]*x + point[1]] = number ; // assigning new cell of the cross to number
//printf("\r %i",number);

//if(point2 = find(crossc,y,point,number + 1 ) != NULL) go(crossc,x,y,finish,number+1,point2); // if the next number is predefined in the nearby , just go for it !

//else we have to go for the next number in every nearby cell
for(;i<2;i++)
    for(j = -1;j<2;j++){
        if (i == 0 && j == 0){continue;}
        if (j == 0) point2[1] = point[1] + i * pad;
        else point2[1] = point[1] + i;

        point2[0] = point[0] + j;
        go(crossc,x,y,finish,number + 1,point2,index,points,lastindex);
    }
    free(crossc);

}


int prcross(int cross[],int x ,int y){

FILE *fp = fopen("answer.dat","w");
int i = 0 , j = 0 ;
 //printf("%i %i \n",x ,y);

for(;j < y;j++){
    for(i = 0;i<x;i++) if ( cross[(j* x )+ i] != -1)fprintf(fp,"%d ",cross[(j* x )+ i]);/*printf("%02i ",cross[(j * x )+ i]);*/ //else printf("  ");
    //printf("\n");
    fprintf(fp,"\n");
    }
}

int cparr(int *arr1, int *arr2,int size){
int i = 0;
for(;i < size; i++)
    arr1[i] = arr2[i];
}




int fsteps(int x1,int y1,int x2,int y2){

int r , dy = abs(y2 - y1),dx = abs(x2-x1) ;
if (pad == 2){
    if (dy >= dx) r = dy;
    else  r = (dx - dy)/2 + dy;

}
else r = max(dy,dx) ;

return r;

}
int max(int m,int n){
if (m > n) return m;
else return n;
}
