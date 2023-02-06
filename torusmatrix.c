/* PROGRAM Matrixmult */
ARCHITECTURE TORUS(7);
#define m 7 /*Torus has m by m processors*/
#define p 5 /*Partition size is p by p*/
#define n 25
typedef float partition[p+1][p+1];
partition A[m][m],B[m][m],C[m][m]; /*master arrays*/
partition stream Achan[m][m], stream Bchan[m][m];
int i,j;
void Multiply(int row, int col, 
 value partition myA, value partition myB,
 partition mainC) {
 int i,j,k,iter,above,left;
 partition myC = {0}; /*fill with 0s*/
 if (row > 0) above = row-1; else above = m-1;
 if (col > 0) left = col-1; else left = m-1;
 for (iter = 1; iter <= m; iter++) {
 send(Achan[row][left], myA); /*Send myA left*/
 send(Bchan[above][col], myB); /*Send myB up*/
 /*Multiply the A and B partitions*/
 for (i = 1; i <= p; i++) 
 for (j = 1; j <= p; j++)
 for (k = 1; k <= p; k++)
 myC[i][j] = myC[i][j] + myA[i][k]*myB[k][j];
 recv(Achan[row][col], myA); /*Receive new myA*/
 recv(Bchan[row][col], myB); /*Receive new myB*/
 }
 mainC = myC; /*Write product back to master C*/
}
main( ) {
 for (i = 1; i <= n; i++){
     for (j = 1; j <=n ;j++)     /*Initialize values for A and B matrices*/
    
   }
         
for (i = 0; i < m; i++)
for (j = 0; j < m; j++)
 fork (@i*m+j)
 Multiply(i,j,A[i][(j+i)%m],B[(i+j)%m][j],C[i][j]);
 
}
