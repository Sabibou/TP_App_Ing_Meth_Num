#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//compiler avec -lm

/*fonction permettant le calcul de la fonction auxiliaire cardinale
*/
float cardinale(int N, int i, float *val, float x){  // Soit N le nombre de points, i l'indice, val le tableau contenant les valeurs de x_i, et x le réel rentré par l'utilisateur
	float denominateur=1;
	float numerateur=1;
	for(int j=0; j<N; j++){
		if(j!=i){   //pour j=0 allant à N-1 (avec j!=i), on calcule séparément le numérateur et le dénominateur
			denominateur*=(val[i]- val[j]); //on multiplie la valeur du dénominateur possédée par x_i-x_j
			numerateur*=(x-val[j]); //on multiplie la valeur du numénateur possédé par x-x_j
		}
	}
	return numerateur/denominateur; //on renvoie le résultat approché de la fraction
}

float lagrange(int N, float **val, float x){
	float y=0;
	for(int i=0;i<N;i++){
 		y+=val[1][i]*cardinale(N,i,val[0],x);
	}
	return y;
}


float neville(int i, int k, float x, float **val){

	if(k==0){ //quand le polynôme atteint le degré 0 on renvoie y_i
		return val[1][i];
	}
	else{
		return(((x-val[0][i+k])*neville(i, k-1, x, val) + (val[0][i] - x)*neville(i+1, k-1,x, val))/(val[0][i]-val[0][i+k]));
	}
}

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
		moy_x_au_carre+=powf(logf(val[0][i]),2);
		moy_y+=logf(val[1][i]);
		moy_x+=logf(val[0][i]);
		moy_xy+=logf(val[0][i])*logf(val[1][i]);
	}
	float b=(moy_xy - moy_x*moy_y)/(moy_x_au_carre-powf(moy_x,2));
	printf("%f\n",moy_y-b*moy_x);
	float a=powf(10, moy_y-(b*moy_x));
	fonct[0]=a;
	fonct[1]=b;
	return fonct;

}

int main(){

	int choix, x;
	float *f=NULL;
	float **val=malloc(sizeof(float *)*2);
	printf("Choississez le jeu d'essai :\n");
	scanf("%d",&choix);
	printf("Choississez un point x :\n");
	scanf("%d",&x);
	switch(choix){
		case 1:
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

			break;

		case 2 :
			
			for(int i=0;i<2;i++){
				val[i]=malloc(sizeof(float)*21);
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

			printf("Avec la méthode de Lagrange, on trouve y = %f\n\n",lagrange(21,val,x));
			printf("Avec la méthode de Neville, on trouve y = %f\n\n",neville(0,20,x,val));
			f=regression(val, 21);
			printf("Par aproximation, on obtient la droite de régression : %fx + %f\n\n",f[1],f[0]);
			
			for(int i=0;i<2;i++){
				free(val[i]);
			}


			break;

		case 3 :
			
			for(int i=0;i<2;i++){
				val[i]=malloc(sizeof(float)*11);
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
			

			printf("Avec la méthode de Lagrange, on trouve y = %f\n\n",lagrange(11,val,x));
			printf("Avec la méthode de Neville, on trouve y = %f\n\n",neville(0,10,x,val));
			f=regression(val, 11);
			printf("Par aproximation, on obtient la droite de régression : %fx + %f\n\n",f[1],f[0]);

			for(int i=0;i<2;i++){
				free(val[i]);
			}
			

			break;

		case 4 :
			for(int i=0;i<2;i++){
				val[i]=malloc(sizeof(float)*7);
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
			
			f=axb(val, 7);
			printf("On obtient les contantes positives a = %f et A = %f\n",f[1],f[0]);
			printf("Soit y = %f\n", f[0]*powf(x,-f[1]));

			for(int i=0;i<2;i++){
				free(val[i]);
			}

			break;

		default :
			printf("Mauvais choix\n");
	}
	free(f);
	free(val);
	

}