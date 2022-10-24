#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float fonc_card(float * X, int n, float x, int i){
    float l = 1;
    float res = 1;
    for(int j=0;j<n;j++){
        if(j!=i){
            //printf("%f , %f\n",X[i],X[j]);
            res = (x-X[j])/(X[i]-X[j]);
            l *= res;
        }        
    }
    return l;
}

float lagrange(float** XY, int n, float x){
    float p = 0;
    float res = 0;
    for(int i=0;i<n;i++){
        res = XY[1][i]*fonc_card(XY[0],n,x,i);
        p += res; 
    }
    return p;
}

float neville(float** XY, int n, float x, int i, int deg){
    //float* P = malloc(n*sizeof(float));
    if(deg==0){
        return XY[1][i];
    }
    else{
        return ((x-XY[0][i+deg])*neville(XY,n,x,i,deg-1)-(x-XY[0][i])*neville(XY,n,x,i+1,deg-1))/(XY[0][i]-XY[0][i+deg]);
    }  
}


struct coefficients{
    float a0;
    float a1;
};
typedef struct coefficients coeff;

coeff regression(float **XY, int n){
	coeff c;
	float x_barre=0,y_barre=0,xy_barre=0,x_barre_au_carre=0;
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

coeff ajust_puiss(float **XY, int n){
	coeff c;
	float x_barre=0,y_barre=0,xy_barre=0,x_barre_au_carre=0;
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
    float ** d= malloc(2*sizeof(float*));
    //int n;
    for(int i=0; i<2;i++){
        d[i]=malloc(3*sizeof(float));
    }
    d[0][0]=0 ;
    d[0][1]= 2;
    d[0][2]= 4;
    d[1][0]= 0.99987;
    d[1][1]= 0.99997;
    d[1][2]= 1;
    printf("%f \n", fonc_card(d[0],3,1,1));
    printf("%f \n", lagrange(d,3,8));
    printf("%f \n", neville(d,3,8,1,2));
    coeff c = regression(d,3);
    printf("%f ,%f \n",c.a0,c.a1);
    
}
