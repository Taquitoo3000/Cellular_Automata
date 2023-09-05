#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void printMatrix(int c, int array[][c]);

int main(){
	int N, num, loops, dynamic, x, y, aux, aux2, aux3, aux4, xobs, yobs;
	int particle=88;
	int wall=9999999;

	printf("\n¿What dimensions you want?: ");
	scanf("%i", &N);
	int array[N+2][N+2];
	int xlebel[N];
    	int xdistro[N];

	//Plot data
	FILE * movement = fopen("Movement.dat","w+");
    	FILE * distribution = fopen("Distribution.dat","w+");
	for(int i=0; i<N; i++){
		xlebel[i]=0;
        xdistro[i]=0;
	}

	//Put walls
	for(int i=0; i<N+2; i++){
		array[i][0]=wall;
		array[0][i]=wall;
		array[i][N+1]=wall;
		array[N+1][i]=wall;
	}
	//Fill matrix
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			array[i+1][j+1]=0;
		}
	}
	//put particle
	x=(N+2)/2;
	y=1;
	array[x][y]=particle;

	//print system
	printf("\n");
	printMatrix(N+2, array);

	//Put obstacle
	printf("\n¿Do you want to put obstacles?\nYes[1]\t No[2]\nAnswer: ");
	scanf("%i", &aux);
	switch(aux){
		case 1:
			do{
				printf("\nColumn of the obstacle (1-%i): ", N);
				scanf("%i", &xobs);
				printf("Row of the obstacle (1-%i): ", N);
				scanf("%i", &yobs);
				array[yobs][xobs]=wall;
				printf("\n");
				printMatrix(N+2, array);
				printf("\nWrite [1] to add another obstacle or [2] to continue: ");
				scanf("%i", &aux2);
			}while(aux2==1);
			break;
		case 2:
			break;
	}

	//loops
	printf("\n¿How many iterations you want?: ");
	scanf("%i", &loops);
	printf("\n¿Dou you want to see step to step or you want to skip?\nStep to step[1]\tSkip[2]\nAnswer: ");
	scanf("%i", &aux3);
    	printf("\n¿How many automatas you want to simulate?: ");
    	scanf("%i", &num);
	printf("\n¿Do you want that it can walk to back and fornt?\nJust to front[1]\tFront and Back[2]\nAnswer: ");
	scanf("%i", &aux4);
	printf("\n  2\n3 x 1\n  0\n\n");
	srand((unsigned)time(NULL));
    for(int w=0; w<num; w++){
        for(int i=0; i<loops; i++){
		    dynamic=rand() % (aux4+2);
		    if(aux3==1){
			    printf("Result=%i\n", dynamic);
		    }
		    switch(dynamic){
			    case 0:
				    if(array[x+1][y]==wall){
					    break;
				    }
				    else{
					    array[x][y]=0;
					    x+=1;
					    array[x][y]=particle;
					    xlebel[y]+=1;
				    }
				    break;
			    case 1:
				    if(array[x][y+1]==wall){
					    break;
				    }
				    else{
					    array[x][y]=0;
					    y+=1;
					    array[x][y]=particle;
					    xlebel[y]+=1;
					    if(y==N){
						    if(aux3==1){
							    printMatrix(N+2, array);
							    printf(" _____________________________________________\n");
							    printf("|                                             |\n");
							    printf("| Winner winner chicken dinner!! You finished |\n");
							    printf("|_____________________________________________|\n\n");
						    }
						    printf("Finished in %i iterations\n\n", i);
						    i=loops-1;
					    }
				    }
				    break;
			    case 2:
				    if(array[x-1][y]==wall){
					    break;
				    }
				    else{
					    array[x][y]=0;
					    x-=1;
					    array[x][y]=particle;
					    xlebel[y]+=1;
				    }
				    break;
			    case 3:
				    if(array[x][y-1]==wall){
					    break;
				    }
				    else{
					    array[x][y]=0;
					    y-=1;
					    array[x][y]=particle;
					    xlebel[y]+=1;
				    }
		    }
		    if(aux3==1){
                printMatrix(N+2, array);
			    printf("\nPress Enter to continue\n");
			    getchar();
		    }
	    }
	    xdistro[y]+=1;
        printf("Stayed at position (%i,%i)\n\n", y, x);
        array[x][y]=0;
        x=(N+2)/2;
	    y=1;
	    array[x][y]=particle;
    }

	//write data
	for(int i=0; i<N; i++){
		fprintf(movement, "%i\t%i\n", i, xlebel[i]);
        fprintf(distribution, "%i\t%i\n", i, xdistro[i]);
	}
	fclose(movement);
    fclose(distribution);

	return 0;
}

void printMatrix(int c, int array[][c]){
	for(int i=0; i<c; i++){
		for(int j=0; j<c; j++){
			printf("%i\t", array[i][j]);
		}
		printf("\n");
	}
}
