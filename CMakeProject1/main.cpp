#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <list>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
//#include <C:/freeglut-3.2.1/include/GL/glew.h>
//#include <GL/freeglut.h>
#include <GL/freeglut.h>
#include <time.h>
//#include <functional>

#include "of.h"
#include "ofOffPointsReader.h"
#include "Handler.hpp" 
#include "GL_Interactor.h"
#include "ColorRGBA.hpp"
#include "Cores.h"
#include "Point.hpp"
#include "printof.hpp"


#include "CommandComponent.hpp"
#include "MyCommands.hpp"

#include "ofVertexStarIteratorSurfaceVertex.h"
//#include<bits/stdc++.h> 
using namespace std; 



clock_t start_insert;
clock_t end_insert;
clock_t start_print;
clock_t end_print;



using namespace std;
using namespace of;

#define N 3        // Number of unknowns 
#define coisa  
// function to reduce matrix to r.e.f.  Returns a value to  
// indicate whether matrix is singular or not 
int forwardElim(double mat[N][N+1]); 
// function to calculate the values of the unknowns 
double* backSub(double mat[N][N+1]); 
double* gaussianElimination(double mat[N][N+1]);
int* sort(double* array);
bool positive(double* array);
void swap_row(double mat[N][N+1], int i, int j);



//Define o tamanho da tela.
scrInteractor *Interactor = new scrInteractor(600, 500);

//Define a malha a ser usada.
typedef of::MyofDefault2D TTraits;
typedef of::ofMesh<TTraits> TMesh;
TMesh *malha;
Handler<TMesh> meshHandler;

typedef PrintOf<TTraits> TPrintOf;

TPrintOf *Print;

typedef MyCommands<TPrintOf> TMyCommands;
typedef CommandComponent TAllCommands;

ofVtkWriter<TTraits> writer;
TAllCommands *allCommands;

////////////////////////////////////////////////////////////////////////
int type = 3;
//CASO 1 EXECUTA CRUST
//CASO 2 EXECUTA BETA-SKELETON
//CASO 3 EXECUTA ARVORE
////////////////////////////////////////////////////////////////////////

using namespace std;


void pintarTrian(double* point){
	
	ofCell<3, TTraits> *CellAtual = malha->getCell(155);
	double SystemAtual[3][4] = {{malha->getVertex(CellAtual->getVertexId(0))->getCoords()[0], malha->getVertex(CellAtual->getVertexId(1))->getCoords()[0], malha->getVertex(CellAtual->getVertexId(2))->getCoords()[0], point[0]},
					{malha->getVertex(CellAtual->getVertexId(0))->getCoords()[1], malha->getVertex(CellAtual->getVertexId(1))->getCoords()[1], malha->getVertex(CellAtual->getVertexId(2))->getCoords()[1], point[1]},
					{1, 1, 1, 1}};
	double* sol = gaussianElimination(SystemAtual);
	int index = 0;
	int ant = 155;
	while(!positive(sol)){
		index++;
		if(CellAtual->getMateId(sort(sol)[0]) == ant){
			Print->Face(malha->getCell(CellAtual->getMateId(sort(sol)[1])), blue);
			ant = CellAtual->getMateId(sort(sol)[1]);
		}else{
			Print->Face(malha->getCell(CellAtual->getMateId(sort(sol)[0])), blue);
			ant = CellAtual->getMateId(sort(sol)[0]);
		}
		CellAtual = malha->getCell(CellAtual->getMateId(sort(sol)[0]));
		if(CellAtual == NULL) break;
		double SystemProx[3][4] = {{malha->getVertex(CellAtual->getVertexId(0))->getCoords()[0], malha->getVertex(CellAtual->getVertexId(1))->getCoords()[0], malha->getVertex(CellAtual->getVertexId(2))->getCoords()[0], point[0]},
					{malha->getVertex(CellAtual->getVertexId(0))->getCoords()[1], malha->getVertex(CellAtual->getVertexId(1))->getCoords()[1], malha->getVertex(CellAtual->getVertexId(2))->getCoords()[1], point[1]},
					{1, 1, 1, 1}};
		sol = gaussianElimination(SystemProx);
		if(sol == NULL) break;
	}

	Print->Faces(malha, lgrey);

}
//##################################################################//
double* point = (double*) malloc(3*sizeof(double));

void RenderScene(void){ 
	allCommands->Execute();
	Print->Vertices(malha,blue,3);
	Print->FacesWireframe(malha,grey,3);
	double points[300]; 
	if((*Interactor).mousePoint[0] != point[0] || (*Interactor).mousePoint[1] != point[1]){
		point[0] = (*Interactor).mousePoint[0];
		point[1] = (*Interactor).mousePoint[1];
		pintarTrian(point);
		(*Interactor).mouseDown = false;
	}else{
		Print->Faces(malha, lgrey);
	}
	glFinish();
	glutSwapBuffers();
}

bool positive(double* array){
	for(int i = 0; i < 3; i++){
		if(array[i] < 0){
			return false;
		}
	}
	return true;
}

int* sort(double* array){
	int* x= (int*) malloc(3*sizeof(int));
	x[0]= 0;
	x[1]= 1;
	x[2]= 2;
	int i, j, min, temp;
   for (i = 0; i < 2; i++) {
      min = i;
      for (j = i + 1; j < 3; j++)
      if (array[j] < array[min])
      min = j;
      temp = x[i];
      x[i] = x[min];
      x[min] = temp;
   }
	return x;
}

// function to calculate the values of the unknowns 
double* backSub(double mat[N][N+1]) 
{ 
    static double x[N];  // An array to store sol 
  
    /* Start calculating from last equation up to the 
       first */
    for (int i = N-1; i >= 0; i--) 
    { 
        /* start with the RHS of the equation */
        x[i] = mat[i][N]; 
  
        /* Initialize j to i+1 since matrix is upper 
           triangular*/
        for (int j=i+1; j<N; j++) 
        { 
            /* subtract all the lhs values 
             * except the coefficient of the variable 
             * whose value is being calculated */
            x[i] -= mat[i][j]*x[j]; 
        } 
  
        /* divide the RHS by the coefficient of the 
           unknown being calculated */
        x[i] = x[i]/mat[i][i]; 
    } 
  	
  	return x;
    printf("\nsol for the system:\n"); 
    for (int i=0; i<N; i++) 
        printf("%lf\n", x[i]); 
} 

// function to reduce matrix to r.e.f. 
int forwardElim(double mat[N][N+1]) 
{ 
    for (int k=0; k<N; k++) 
    { 
        // Initialize maximum value and index for pivot 
        int i_max = k; 
        int v_max = mat[i_max][k]; 
  
        /* find greater amplitude for pivot if any */
        for (int i = k+1; i < N; i++) 
            if (abs(mat[i][k]) > v_max) 
                v_max = mat[i][k], i_max = i; 
  
        /* if a prinicipal diagonal element  is zero, 
         * it denotes that matrix is singular, and 
         * will lead to a division-by-zero later. */
        if (!mat[k][i_max]) 
            return k; // Matrix is singular 
  
        /* Swap the greatest value row with current row */
        if (i_max != k) 
            swap_row(mat, k, i_max); 
  
  
        for (int i=k+1; i<N; i++) 
        { 
            /* factor f to set current row kth element to 0, 
             * and subsequently remaining kth column to 0 */
            double f = mat[i][k]/mat[k][k]; 
  
            /* subtract fth multiple of corresponding kth 
               row element*/
            for (int j=k+1; j<=N; j++) 
                mat[i][j] -= mat[k][j]*f; 
  
            /* filling lower triangular matrix with zeros*/
            mat[i][k] = 0; 
        } 
  
        //print(mat);        //for matrix state 
    } 
    //print(mat);            //for matrix state 
    return -1; 
} 

// function to print matrix content at any stage 
void print(double mat[N][N+1]) 
{ 
    for (int i=0; i<N; i++, printf("\n")) 
        for (int j=0; j<=N; j++) 
            printf("%lf ", mat[i][j]); 
  
    printf("\n"); 
} 


// function for elementary operation of swapping two rows 
void swap_row(double mat[N][N+1], int i, int j) 
{ 
    //printf("Swapped rows %d and %d\n", i, j); 
  
    for (int k=0; k<=N; k++) 
    { 
        double temp = mat[i][k]; 
        mat[i][k] = mat[j][k]; 
        mat[j][k] = temp; 
    } 
} 

// function to get matrix content 
double* gaussianElimination(double mat[N][N+1]) 
{ 
    /* reduction into r.e.f. */
    int singular_flag = forwardElim(mat); 
  
    /* if matrix is singular */
    if (singular_flag != -1) 
    { 
        printf("Singular Matrix.\n"); 
  
        /* if the RHS of equation corresponding to 
           zero row  is 0, * system has infinitely 
           many sols, else inconsistent*/
        if (mat[singular_flag][N]) 
            printf("Inconsistent System."); 
        else
            printf("May have infinitely many "
                   "sols."); 
  
        return NULL; 
    } 
  
    /* get sol to system and print it using 
       backward substitution */
    return backSub(mat); 
} 


void HandleKeyboard(unsigned char key, int x, int y){	
	
	
	
	double coords[3];
	char *xs[10];
	allCommands->Keyboard(key);
	
	switch (key) {

		case 'e':
			exit(1);
		break;
		case 'v':
			coords[0]=x;
			coords[1]=-y;
			coords[2]=0.0;
			malha->addVertex(coords);
		break;
		case 's':
			
		break;

		case 'd':
			
			
		break;
	

	}
    
	
	Interactor->Refresh_List();
	glutPostRedisplay();

}

int main(int *argc, char **argv)
{


  ofRuppert2D<MyofDefault2D> ruppert;
  ofPoints2DReader<MyofDefault2D> reader;
  ofVtkWriter<MyofDefault2D> writer;
  Interactor->setDraw(RenderScene);
	meshHandler.Set(new TMesh());
      char *fileBrasil = "../Brasil.off";

     
    reader.readOffFile(fileBrasil);
    
    ruppert.execute2D(reader.getLv(),reader.getLids(),true);
    //writer.write(ruppert.getMesh(),"out.vtk",reader.getNorma(),ruppert.getNumberOfInsertedVertices());
  
  meshHandler = ruppert.getMesh();
  malha = ruppert.getMesh();
  
  
  Print = new TPrintOf(meshHandler);

	allCommands = new TMyCommands(Print, Interactor);

	double a,x1,x2,y1,y2,z1,z2; 

	of::ofVerticesIterator<TTraits> iv(&meshHandler);

	iv.initialize();
	x1 = x2 = iv->getCoord(0);
	y1 = y2 = iv->getCoord(1);
	z1 = z2 = iv->getCoord(2);

	for(iv.initialize(); iv.notFinish(); ++iv){
		if(iv->getCoord(0) < x1) x1 = a = iv->getCoord(0);
		if(iv->getCoord(0) > x2) x2 = a = iv->getCoord(0);
		if(iv->getCoord(1) < y1) y1 = a = iv->getCoord(1);
		if(iv->getCoord(1) > y2) y2 = a = iv->getCoord(1);
		if(iv->getCoord(2) < z1) z1 = a = iv->getCoord(2);
		if(iv->getCoord(2) > z2) z2 = a = iv->getCoord(2);
	}

	double maxdim;
	maxdim = fabs(x2 - x1);
	if(maxdim < fabs(y2 - y1)) maxdim = fabs(y2 - y1);
	if(maxdim < fabs(z2 - z1)) maxdim = fabs(z2 - z1);

	maxdim *= 0.6;
	
	Point center((x1+x2)/2.0, (y1+y2)/2.0, (y1+y2)/2.0 );
	Interactor->Init(center[0]-maxdim, center[0]+maxdim,
					center[1]-maxdim, center[1]+maxdim,
					center[2]-maxdim, center[2]+maxdim,argc,argv);

	AddKeyboard(HandleKeyboard);

	allCommands->Help(std::cout);
	std::cout<< std::endl<< "Press \"?\" key for help"<<std::endl<<std::endl;
	double t;
	
	Init_Interactor();
  
  return EXIT_SUCCESS;
}
