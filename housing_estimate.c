#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

void multiply (double ** result, double** A, double** B, int r, int r1, int c) {
double answer = 0;
for (int i=0; i < r; i++ ){
  for (int j =0; j < c; j++) {
    answer =0;
    for (int k =0; k < r1; k ++) {

  answer+= A[i][k] * B [k][j];

        }
    result [i][j] = answer;

     }

  }


}

void transpose (double ** result, double** A, int r, int c) {


for (int x =0; x < c; x++) {

for (int y =0; y < r; y++) {


result [x][y] = A[y][x];

}


}
}

void invert (double**mat, double** identity,  int r ) 
{
  double f;
  for (int i =0; i < r; i++)
  {
    if (mat[i][i] != 1.0)
    {
      f = (1.0/mat [i][i]);
      for (int x =0; x < r; x++) 
      {
        mat [i][x] = (mat[i][x]*f);
        identity [i][x] = (identity[i][x]*f);
       // if (mat[i][x] == -0) mat[i][x] =0;  
       // if (identity[i][x]== -0) identity[i][x] =0;
      }
    }   
 
    double f1; 
    for(int j= i+1; j < r; j++)  
    {
      if (mat[j][i]!=0) 
      {
        f1 = mat[j][i] *-1 ;
        for (int y=0; y < r; y++) 
        {
          mat[j][y] += (f1*mat[i][y]);
          identity[j][y] += (f1*identity[i][y]); 
       // if (mat[j][y] == -0) mat[j][y] = 0;  
       // if (identity[j][y]== -0) identity[j][y] =0;

        }
      }
    }
  }

  double fac;
  for (int k = r-1; k >=0; k--) 
  {
    if (mat[k][k] !=1 ) {
    fac = (1/mat [k][k]);
    for (int h =0; h< r; h++) 
    {
      mat [k][k] = (mat [k][k]*fac);
      identity[k][k] = (identity[k][k]*fac);  
   
       // if (mat[k][h] == -0) mat[k][h] =0;  
       // if (identity[k][h]== -0) identity[k][h] =0;

    }
   
    }
    
    double fac1;
    for (int w= k-1; w >=0; w-- ) 
    {
      if (mat[w][k] !=0) 
      {
        fac1 = mat[w][k]*-1;
        
        for (int p =0; p < r; p++) 
        {
          mat [w][p] += (mat[k][p]*fac1);
          identity [w][p] += (identity[k][p]*fac1);
       
       //if (mat[w][p] == -0) mat[w][p] = 0;  
       // if (identity[w][p]== -0) identity[w][p] =0;

        }
      }
    }
  }
}

void multiarray (double * result, double * one , double ** two, int r, int c) {

for (int i=0; i < r; i++) {
double sum =0;
for (int j =0; j<c; j++ ) {

sum += two[i][j]*one[j];
  }
  result[i] = sum;
 }
}



int main (int argc, char ** argv) {
FILE * fp;
FILE * fp1;
FILE * trfile;
 FILE *datfile; 
int trow;
int tcolumn;
int drow;
int dcolumn;
 
   if (argc != 3) {

      printf("Please insert only two files");
  return EXIT_FAILURE;
  }

    fp =fopen (argv[1], "r"); 
        if (fp == NULL) {
    printf ("Error, file unable to open");
       return EXIT_FAILURE;
}

   fp1 = fopen(argv[2], "r");
  if (fp1 == NULL) {
      printf ("Error, file unable to open");
  return EXIT_FAILURE;
  }

char word [100];
char word1 [100];

fscanf(fp,"%s",word);
fscanf(fp1,"%s",word1);

  if (strlen(word) == 5) {
trfile = fp;
  datfile = fp1;
 }
  else {
  trfile = fp1;
  datfile = fp;
  }

fscanf (trfile, "%d", &tcolumn);
fscanf (trfile, "%d", &trow);
tcolumn = tcolumn +1;

 fscanf(datfile, "%d",&dcolumn );
 dcolumn= dcolumn +1;
 fscanf(datfile, "%d", &drow );

// storage of all the arrays used 
double ** X = (double**)malloc(trow *sizeof(double*));
double ** Train = (double**)malloc(trow *sizeof(double*));
double ** xtr = (double **)malloc(tcolumn*sizeof(double*));
double * Y = (double *)malloc(trow* sizeof(double*));
double ** XTX = (double **)malloc(tcolumn *sizeof(double*));
double ** XTXXT = (double **)malloc(tcolumn *sizeof(double*));
double ** iden = (double **)malloc(tcolumn *sizeof(double*));
double ** XPrime = (double **)malloc( drow*sizeof(double*));
double * YPrime = (double *)malloc( drow*sizeof(double));
double * W = (double*)malloc(trow*sizeof(double));
double ** inversion = (double**)malloc(tcolumn* sizeof(double*));
// train part 
for (int i =0; i < trow; i++) {
X[i] = (double*)malloc(tcolumn*sizeof(double));
Train[i] = (double*)malloc(tcolumn*sizeof(double)); 
 }

for (int i =0; i < tcolumn; i++) {
 xtr[i] = (double*)malloc(trow*sizeof(double));
 XTX [i]= (double*) malloc(tcolumn*sizeof(double));
inversion[i] = (double*)malloc(tcolumn*sizeof(double));
iden[i] = (double*)malloc(tcolumn*sizeof(double));
 XTXXT [i]= (double*) malloc(trow*sizeof(double));

}

for (int j =0; j < drow; j++) {
XPrime[j] = (double*)malloc(dcolumn*sizeof(double));

}

 for (int i =0; i < trow; i++) {
    X[i][0] = 1.0;
     for (int j =0; j < tcolumn; j ++) {
      fscanf(trfile,"%lf", &Train[i][j]);
}
 }

for (int i =0; i < trow; i++) {
  for (int j =1; j < tcolumn; j ++) {
X[i][j] = Train[i][j-1];
 }
 Y[i] = Train[i][tcolumn-1];
 }
 
 for (int x =0; x< tcolumn ; x++) {
   for (int y =0; y< tcolumn; y++)  {
    
    if (x==y) {
iden[x][y] =1;

    }
else {
    iden[x][y]=0;
      }
   }
}


    transpose(xtr,X, trow, tcolumn);
//  for (int i =0; i < tcolumn; i++) {
//        for (int j =0; j < trow; j ++) {
//      printf ("%f ", xtr[i][j]);
//    }
//   printf ("\n");
//    }

//   printf ("\n");

    multiply(XTX, xtr, X, tcolumn, trow, tcolumn);
    
//      for (int i =0; i < tcolumn; i++) {
//        for (int j =0; j < tcolumn; j ++) {
//      printf ("%f ", XTX[i][j]);
//    }
//  printf ("\n");
//    }

//    printf ("\n");
    invert(XTX, iden, tcolumn);
     multiply(XTXXT,iden, xtr, tcolumn,tcolumn,trow);
    //price * xtxxt to get W;

    multiarray(W, Y,XTXXT, tcolumn, trow);
    if (dcolumn != tcolumn) {
      printf("k values must match");
      return EXIT_FAILURE;
    }

//   for (int i =0; i < tcolumn; i++) {
//        for (int j =0; j < tcolumn; j ++) {
//      printf ("%f ", iden[i][j]);
//    }
//   printf ("\n");
//   }

//  printf ("\n");

// data part 

  // for (int i =0; i < tcolumn; i++) {
  //      for (int j =0; j < trow; j ++) {
  //    printf ("%f ", XTXXT[i][j]);
  //  }
  // printf ("\n");
  //  }

  // printf ("\n");


//  for (int i=0; i < trow; i++) {
//  printf ("%f \n", W[i]); 

//  }
//  printf("\n");
//  printf("\n");
 
 for (int i =0; i < drow; i++) {
     XPrime[i][0] = 1.0;
      for (int j =1; j < dcolumn; j ++) {
       fscanf(datfile,"%lf", &XPrime[i][j]);
 }
  }


// for (int i =0; i < drow; i++) {
  
//       for (int j =0; j < dcolumn; j ++) {
//        fscanf(datfile,"%lf", &XPrime[i][j]);
//  printf ("%f ", XPrime[i][j]);
//  }
//  printf("\n");
//   }

 


    multiarray(YPrime,W,XPrime, drow, dcolumn);
        // xprime * W = YPrime;

  for (int i =0; i < drow; i++) {
         // print YPrime; 
    printf("%0.lf\n", YPrime[i]); 
 }



//Manually freeing all of the arrays

for (int i =0; i < trow; i++) {
free(X[i]);
free(Train[i]);
 }
free(X);
free(Train);

for (int i =0; i < tcolumn; i++) {
free (xtr[i]);
free(XTX[i]);
free(XTXXT[i]);
free(inversion[i]);
free(iden[i]);
}


free (xtr);
free(XTX);
free(XTXXT);
free(inversion);
free(iden);
for (int i=0; i<drow; i++) {
free(XPrime[i]);
}
free(XPrime);
// one dimensional freeing
free(YPrime);
free (Y);
free (W);



    return EXIT_SUCCESS;
}
