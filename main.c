#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//compiler avec -lm

float cardinale(int N, int i, float *val, float x){
	float denominateur=1;
	float numerateur=1;
	for(int j=0; j<N; j++){
		if(j!=i){
			denominateur*=(val[i]- val[j]);
			numerateur*=(x-val[j]);
		}
	}
	return numerateur/denominateur;
}

float lagrange(int N, float **val, float x){
	float y=0;
	for(int i=0;i<N;i++){
 		y+=val[1][i]*cardinale(N,i,val[0],x);
	}
	return y;
}
/*
void difference_divisee(float **val, int k, int i, float ** diff_div){
	if(k==1){
		diff_div[1][i]= ((val[1][i] - val[1][1])/(val[0][i]-val[0][1]));
	}
	else{
		diff_div[k][i]= ((diff_div[k-1][i] - diff_div[k-1][k])/(val[0][i]-val[0][k]));
	}
}

float newton(float **val, int N, float x){
	
	float **diff_div=malloc(sizeof(float *)*N-2);
	for(int i=n-1;i>1;i--){
		diff_div[i]=malloc(sizeof(float)*i);
	}

	for(int k=0;k<N-2;k++){
		for(int i=0;i<N-1-k;i++){
			difference_divisee(val, k, i, diff_div );
		}
	}

	float y=diff_div[][];

	for(int i=0; i<N;i++){
		y+=diff_div[i][i];
	}

	for(int i=n-1;i>1;i--){
		free(diff_div[i]);
	}
	free(diff_div);
}
*/

float neville(int i, int k, float x, float **val){

	if(k==0){
		return val[1][i];
	}
	else{
		return(((x-val[0][i+k])*neville(i, k-1, x, val) + (val[0][i] - x)*neville(i+1, k-1,x, val))/(val[0][i]-val[0][i+k]));
	}
}
/*
float moyenne_x_ou_y(float *val, int n){
	float somme=0;
	for(int i=0;i<n;i++){
		somme+=val[i];
	}
	return somme/n;
}

float moyenne_xy(float **val, int n){
	float somme=0;
	for(int i=0;i<n;i++){
		somme+=val[1][i]*val[0][i];
	}
	return somme/n;
}

float moyenne_x_au_carre(float *val, int n){
	float somme=0;
	for(int i=0;i<n;i++){
		somme+=powf(val[i],2);
	}
	return somme/n;
}

float regression(float **val, int N, float x){
	float a1=(moyenne_xy(val, N) - moyenne_x_ou_y(val[0],N)*moyenne_x_ou_y(val[1],N))/(moyenne_x_au_carre(val[0],N)-powf(moyenne_x_ou_y(val[0],N),2));
	float a0=(moyenne_x_ou_y(val[1], N)*moyenne_x_au_carre(val[0],N) - moyenne_x_ou_y(val[0],N)*moyenne_xy(val,N))/(moyenne_x_au_carre(val[0],N)-powf(moyenne_x_ou_y(val[0],N),2));
	printf("%f\n%f\n",a1,a0);
	return a1*x+a0;
}
*/
float *regression(float **val, int n){
	float *fonct=malloc(sizeof(float)*2);
	float moy_x=0,moy_y=0,moy_xy=0,moy_x_au_carre=0;
	for(int i=0;i<n;i++){
		moy_x_au_carre+=powf(val[0][i],2);
		moy_y+=val[1][i];
		moy_x+=val[0][i];
		moy_xy+=val[0][i]*val[1][i];
	}
	fonct[1]=(moy_xy - moy_x*moy_y)/(moy_x_au_carre-powf(moy_x,2));
	fonct[0]=(moy_y*moy_x_au_carre-moy_x*moy_xy)/(moy_x_au_carre-powf(moy_x,2));
	return fonct;

}

float *axb(float **val, int n){
	float *fonct=malloc(sizeof(float)*2);
	float moy_x=0,moy_y=0,moy_xy=0,moy_x_au_carre=0;
	for(int i=0;i<n;i++){
		moy_x_au_carre+=powf(val[0][i],2);
		moy_y+=val[1][i];
		moy_x+=val[0][i];
		moy_xy+=val[0][i]*val[1][i];
	}
	float b=(moy_xy - moy_x*moy_y)/(moy_x_au_carre-powf(moy_x,2));
	float a=powf(10, moy_y-b*moy_x);
	fonct[0]=a;
	fonct[1]=b;
	return fonct;

}

int main(){

	int choix, x;
	float *f=NULL;
	printf("Choississez le jeu d'essai :\n");
	scanf("%d",&choix);
	printf("Choississez un point x :\n");
	scanf("%d",&x);
	switch(choix){
		case 1:
			float **val=malloc(sizeof(float *)*2);
			for(int i=0;i<2;i++){
				val[i]=malloc(sizeof(float)*20);
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

			printf("Avec la méthode de Lagrange, on trouve y = %f\n\n",lagrange(20,val,x));
			printf("Avec la méthode de Neville, on trouve y = %f\n\n",neville(0,19,x,val));
			f=regression(val, 20);
			printf("Par aproximation, on obtient la droite de régression : %fx + %f\n\n",f[1],f[0]);

			for(int i=0;i<2;i++){
				free(val[i]);
			}
			free(val);

			break;

		case 2 :
			float **val2=malloc(sizeof(float *)*2);
			for(int i=0;i<2;i++){
				val2[i]=malloc(sizeof(float)*21);
			}

			val2[1][0]=85;
			val2[1][1]=83;
			val2[1][2]=162;
			val2[1][3]=79;
			val2[1][4]=81;
			val2[1][5]=83;
			val2[1][6]=281;
			val2[1][7]=81;
			val2[1][8]=81;
			val2[1][9]=80;
			val2[1][10]=243;
			val2[1][11]=84;
			val2[1][12]=84;
			val2[1][13]=82;
			val2[1][14]=80;
			val2[1][15]=226;
			val2[1][16]=260;
			val2[1][17]=82;
			val2[1][18]=186;
			val2[1][19]=77;
			val2[1][20]=223;

			val2[0][0]=752;
			val2[0][1]=855;
			val2[0][2]=871;
			val2[0][3]=734;
			val2[0][4]=610;
			val2[0][5]=582;
			val2[0][6]=921;
			val2[0][7]=492;
			val2[0][8]=569;
			val2[0][9]=462;
			val2[0][10]=907;
			val2[0][11]=643;
			val2[0][12]=862;
			val2[0][13]=524;
			val2[0][14]=679;
			val2[0][15]=902;
			val2[0][16]=918;
			val2[0][17]=828;
			val2[0][18]=875;
			val2[0][19]=809;
			val2[0][20]=894;

			printf("Avec la méthode de Lagrange, on trouve y = %f\n\n",lagrange(21,val2,x));
			printf("Avec la méthode de Neville, on trouve y = %f\n\n",neville(0,20,x,val2));
			f=regression(val2, 21);
			printf("Par aproximation, on obtient la droite de régression : %fx + %f\n\n",f[1],f[0]);
			
			for(int i=0;i<2;i++){
				free(val2[i]);
			}
			free(val2);

			break;

		case 3 :
			float **val3=malloc(sizeof(float *)*2);
			for(int i=0;i<2;i++){
				val3[i]=malloc(sizeof(float)*11);
			}

			val3[1][0]=8.04;
			val3[1][1]=6.95;
			val3[1][2]=7.58;
			val3[1][3]=8.81;
			val3[1][4]=8.33;
			val3[1][5]=9.96;
			val3[1][6]=7.24;
			val3[1][7]=4.26;
			val3[1][8]=10.84;
			val3[1][9]=4.82;
			val3[1][10]=5.68;
			

			val3[0][0]=10;
			val3[0][1]=8;
			val3[0][2]=13;
			val3[0][3]=9;
			val3[0][4]=11;
			val3[0][5]=14;
			val3[0][6]=6;
			val3[0][7]=4;
			val3[0][8]=12;
			val3[0][9]=7;
			val3[0][10]=5;
			

			printf("Avec la méthode de Lagrange, on trouve y = %f\n\n",lagrange(11,val3,x));
			printf("Avec la méthode de Neville, on trouve y = %f\n\n",neville(0,10,x,val3));
			f=regression(val3, 11);
			printf("Par aproximation, on obtient la droite de régression : %fx + %f\n\n",f[1],f[0]);

			for(int i=0;i<2;i++){
				free(val3[i]);
			}
			free(val3);

			break;

		case 4 :

			break;

		default :
			printf("Mauvais choix\n");
	}
	free(f);
	

}