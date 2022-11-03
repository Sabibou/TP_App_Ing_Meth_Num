#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double fonc_card(double * X, int n, double x, int i){
    double l = 1;
    double res = 1;
    for(int j=0;j<n;j++){
        if(j!=i){
            //printf("%f , %f\n",X[i],X[j]);
            res = (x-X[j])/(X[i]-X[j]);
            l *= res;
        }        
    }
    return l;
}

double lagrange(double** XY, int n, double x){
    double p = 0;
    double res = 0;
    for(int i=0;i<n;i++){
        res = XY[1][i]*fonc_card(XY[0],n,x,i);
        p += res; 
    }
    return p;
}

double neville(double** XY, double x, int i, int deg){
    //double* P = malloc(n*sizeof(double));
    if(deg==0){
        return XY[1][i];
    }
    else{
        return ((x-XY[0][i+deg])*neville(XY,x,i,deg-1)-(x-XY[0][i])*neville(XY,x,i+1,deg-1))/(XY[0][i]-XY[0][i+deg]);
    }  
}


struct coefficients{
    double a0;
    double a1;
};
typedef struct coefficients coeff;

coeff regression(double **XY, int n){
	coeff c;
	double x_barre=0,y_barre=0,xy_barre=0,x_barre_au_carre=0;
	for(int i=0;i<n;i++){
		x_barre_au_carre+=powf(XY[0][i],2);
		y_barre+=XY[1][i];
		x_barre+=XY[0][i];
		xy_barre+=XY[0][i]*XY[1][i];
	}
	
	y_barre=y_barre/n;
	x_barre_au_carre=x_barre_au_carre/n;
	x_barre=x_barre/n;
	xy_barre=xy_barre/n;
	
	c.a1=(xy_barre - x_barre*y_barre)/(x_barre_au_carre-powf(x_barre,2));
	c.a0=(y_barre*x_barre_au_carre-x_barre*xy_barre)/(x_barre_au_carre-powf(x_barre,2));

return c;
}

coeff ajust_puiss(double **XY, int n){
	coeff c;
	double x_barre=0,y_barre=0,xy_barre=0,x_barre_au_carre=0;
	for(int i=0;i<n;i++){
		x_barre_au_carre+=powf(XY[0][i],2);
		y_barre+=XY[1][i];
		x_barre+=XY[0][i];
		xy_barre+=XY[0][i]*XY[1][i];
	}
	
	y_barre=y_barre/n;
	x_barre_au_carre=x_barre_au_carre/n;
	x_barre=x_barre/n;
	xy_barre=xy_barre/n;
	
	c.a1=(xy_barre - x_barre*y_barre)/(x_barre_au_carre-powf(x_barre,2));
	c.a0=(y_barre*x_barre_au_carre-x_barre*xy_barre)/(x_barre_au_carre-powf(x_barre,2));

return c;
}

int main(){
   /*  double ** d= malloc(2*sizeof(double*));
    //int n;
    for(int i=0; i<2;i++){
        d[i]=malloc(3*sizeof(double));
    }
    d[0][0]=0 ;
    d[0][1]= 2;
    d[0][2]= 5;
    d[1][0]= 3;
    d[1][1]= -1;
    d[1][2]= 8;
    printf("%f \n", fonc_card(d[0],3,1,1));
    printf("%f \n", lagrange(d,3,3));
    printf("%f \n", neville(d,3,1,2));
    coeff c = regression(d,3);
    printf("%f ,%f \n",c.a0,c.a1); 
     */
    int choix, x;
	//double *f=NULL;
    coeff c;
	double **val=malloc(sizeof(double *)*2);
	printf("Choississez le jeu d'essai :\n");
	scanf("%d",&choix);
	printf("Choississez un point x :\n");
	scanf("%d",&x);
	switch(choix){
		case 1:
			for(int i=0;i<2;i++){
				val[i]=malloc(sizeof(double)*20);
			}
			for(int i=0;i<20;i++){
				val[0][i]=i*2;
			}

			val[1][0]=0.99987;
			val[1][1]=0.99997;
			val[1][2]=1;
			val[1][3]=0.99997;
			val[1][4]=0.99988;
			val[1][5]=0.99973;
			val[1][6]=0.99953;
			val[1][7]=0.99927;
			val[1][8]=0.99897;
			val[1][9]=0.99846;
			val[1][10]=0.99805;
			val[1][11]=0.99751;
			val[1][12]=0.99705;
			val[1][13]=0.99650;
			val[1][14]=0.99664;
			val[1][15]=0.99533;
			val[1][16]=0.99472;
			val[1][17]=0.99472;
			val[1][18]=0.99333;
			val[1][19]=0.99326;

			printf("Avec la méthode de Lagrange, on trouve y = %lf\n\n",lagrange(val,20,x));
			printf("Avec la méthode de Neville, on trouve y = %lf\n\n",neville(val,x,0,19));
			c=regression(val, 20);
			printf("Par aproximation, on obtient la droite de régression : %lfx + %lf\n\n",c.a1,c.a0);
            
            FILE *f1 = NULL;
            //create and open the text file
            f1 = fopen("jeu1.csv", "w");
            if(f1 == NULL){
                printf("Error in creating the file\n");
                exit(1);
            }
            //write the data in file
          
            for(int j=0;j<20;j++){
                fprintf(f1,"%f,%f\n",val[0][j],val[1][j]);
            }
            fprintf(f1,"%s \n", "Lagrange");
            for(int i=0;i<41;i++){
                fprintf(f1,"%d,%f\n",i,lagrange(val,20,i));
            }
            fprintf(f1,"%s \n", "Neville");
            for(int i=0;i<41;i++){
                fprintf(f1,"%d,%f\n",i,neville(val,i,0,19));
            }
            
            fclose(f1);
          
			for(int i=0;i<2;i++){
				free(val[i]);
			}

			break;

		case 2 :
			
			for(int i=0;i<2;i++){
				val[i]=malloc(sizeof(double)*21);
			}

			val[1][0]=85;
			val[1][1]=83;
			val[1][2]=162;
			val[1][3]=79;
			val[1][4]=81;
			val[1][5]=83;
			val[1][6]=281;
			val[1][7]=81;
			val[1][8]=81;
			val[1][9]=80;
			val[1][10]=243;
			val[1][11]=84;
			val[1][12]=84;
			val[1][13]=82;
			val[1][14]=80;
			val[1][15]=226;
			val[1][16]=260;
			val[1][17]=82;
			val[1][18]=186;
			val[1][19]=77;
			val[1][20]=223;

			val[0][0]=752;
			val[0][1]=855;
			val[0][2]=871;
			val[0][3]=734;
			val[0][4]=610;
			val[0][5]=582;
			val[0][6]=921;
			val[0][7]=492;
			val[0][8]=569;
			val[0][9]=462;
			val[0][10]=907;
			val[0][11]=643;
			val[0][12]=862;
			val[0][13]=524;
			val[0][14]=679;
			val[0][15]=902;
			val[0][16]=918;
			val[0][17]=828;
			val[0][18]=875;
			val[0][19]=809;
			val[0][20]=894;

			printf("Avec la méthode de Lagrange, on trouve y = %lf\n\n",lagrange(val,21,x));
			printf("Avec la méthode de Neville, on trouve y = %lf\n\n",neville(val,x,0,20));
			c=regression(val, 21);
			printf("Par aproximation, on obtient la droite de régression : %lfx + %lf\n\n",c.a1,c.a0);
			
            FILE *f2 = NULL;
            //create and open the text file
            f2 = fopen("jeu2.csv", "w");
            if(f2 == NULL){
                printf("Error in creating the file\n");
                exit(1);
            }
            //write the data in file
          
            for(int j=0;j<21;j++){
                fprintf(f2,"%f,%f\n",val[0][j],val[1][j]);
            }
            fprintf(f2,"%s \n", "Lagrange");
            for(int i=460;i<921;i++){
                fprintf(f2,"%d,%f\n",i,lagrange(val,20,i));
            }
            fprintf(f2,"%s \n", "Neville");
            for(int i=460;i<921;i++){
                fprintf(f2,"%d,%f\n",i,neville(val,i,0,19));
            }
            
            fclose(f2);

			for(int i=0;i<2;i++){
				free(val[i]);
			}


			break;

		case 3 :
			
			for(int i=0;i<2;i++){
				val[i]=malloc(sizeof(double)*11);
			}
			
			val[1][0]=8.04;
			val[1][1]=6.95;
			val[1][2]=7.58;
			val[1][3]=8.81;
			val[1][4]=8.33;
			val[1][5]=9.96;
			val[1][6]=7.24;
			val[1][7]=4.26;
			val[1][8]=10.84;
			val[1][9]=4.82;
			val[1][10]=5.68;
			

			val[0][0]=10;
			val[0][1]=8;
			val[0][2]=13;
			val[0][3]=9;
			val[0][4]=11;
			val[0][5]=14;
			val[0][6]=6;
			val[0][7]=4;
			val[0][8]=12;
			val[0][9]=7;
			val[0][10]=5;

			

			printf("Avec la méthode de Lagrange, on trouve y = %lf\n\n",lagrange(val,11,x));
			printf("Avec la méthode de Neville, on trouve y = %lf\n\n",neville(val,x,0,10));
			c=regression(val, 11);
			printf("Par aproximation, on obtient la droite de régression : %lfx + %lf\n\n",c.a1,c.a0);

            FILE *f3 = NULL;
            //create and open the text file
            f3 = fopen("jeu3.csv", "w");
            if(f3 == NULL){
                printf("Error in creating the file\n");
                exit(1);
            }
            //write the data in file
          
            for(int j=0;j<11;j++){
                fprintf(f3,"%f,%f\n",val[0][j],val[1][j]);
            }
            fprintf(f3,"%s \n", "Lagrange");
            for(int i=0;i<16;i++){
                fprintf(f3,"%d,%f\n",i,lagrange(val,20,i));
            }
            fprintf(f3,"%s \n", "Neville");
            for(int i=0;i<16;i++){
                fprintf(f3,"%d,%f\n",i,neville(val,i,0,19));
            }
            
            fclose(f3);

			for(int i=0;i<2;i++){
				free(val[i]);
			}
			

			break;

		case 4 :
			for(int i=0;i<2;i++){
				val[i]=malloc(sizeof(double)*7);
			}
			
			val[1][0]=352;
			val[1][1]=128;
			val[1][2]=62.3;
			val[1][3]=35.7;
			val[1][4]=6.3;
			val[1][5]=0.4;
			val[1][6]=0.1;
			
			

			val[0][0]=20;
			val[0][1]=30;
			val[0][2]=40;
			val[0][3]=50;
			val[0][4]=100;
			val[0][5]=300;
			val[0][6]=500;
			
			/*
			val[1][0]=1;
			val[1][1]=4;
			val[1][2]=9;
			val[1][3]=16;
			val[1][4]=25;
			val[1][5]=36;
			val[1][6]=49;
			
			

			val[0][0]=1;
			val[0][1]=2;
			val[0][2]=3;
			val[0][3]=4;
			val[0][4]=5;
			val[0][5]=6;
			val[0][6]=7;
			*/
			c=ajust_puiss(val, 7);
			printf("On obtient les contantes positives a = %lf et A = %lf\n",-c.a1,c.a0);
			printf("Soit y = %lf\n", c.a0*powf(x,c.a1));

            FILE *f4 = NULL;
            //create and open the text file
            f4 = fopen("jeu4.csv", "w");
            if(f4 == NULL){
                printf("Error in creating the file\n");
                exit(1);
            }
            //write the data in file
          
            for(int j=0;j<7;j++){
                fprintf(f4,"%f,%f\n",val[0][j],val[1][j]);
            }
            
            fclose(f4);
			for(int i=0;i<2;i++){
				free(val[i]);
			}

			break;

		default :
			printf("Mauvais choix\n");
	}
	//free(c);

    //Populate structure variable
    //s_employee sAmlendraInfor =  {8886, "Amlendra", "Mishra"};
    //file pointer
    
	free(val);
	

}

