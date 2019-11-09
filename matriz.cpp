#include <iostream>
#include <locale.h>
#include <vector>
#include <conio.h>
using namespace std;

vector<vector<double> > create_matrix(int len);
void print_matrix(vector<vector<double> > matriz,int len);              
void print_vector(vector<double> vetor,int len);
void adotar_padrao(vector<vector<double> > &matriz,vector<double> &vector_b);
vector<double> matrix_u(vector<vector<double> >& matriz,int len);
vector<vector<double> > matrix_l(vector<double> factor,int len);      
vector<double> vector_y(vector<double> factor,vector<double> vector_b,int len); //acha vetor y
vector<double> vector_x(vector<vector<double> > matrix, vector<double> y,int len); //resultado item a)

//OBSSSS: inverter o vetor retornado pela função vector_x...

int main(){

	int dimen_matriz,count=1; char validade;
	setlocale(LC_ALL, "Portuguese");
	vector<double> vector_b;
	
	cout<<"############TRABALHO DE METODOS############\n Fatoracao LU\n"<<endl;
	
	cout<<"\nDeseja calibrar o sistema usando a matriz A e o vetor d padrão?[Y/N]"<<endl;
	cin>>validade;
	cout<<"Digite a dimensao da matriz quadratica dos coeficientes"<<endl;
	cin>>dimen_matriz;
	vector<vector<double> > matriz=create_matrix(dimen_matriz);
	
	if(validade=='y'||validade=='1'){
		//vector<vector<double> > matriz=create_matrix(3);
		adotar_padrao(matriz,vector_b);
		dimen_matriz=3;
	}else{
		//vector<vector<double> > matriz=create_matrix(dimen_matriz);
		for(int i=0;i<dimen_matriz;i++){
			for(int j=0;j<dimen_matriz;j++){
				cout<<"Digite o elemento "<<(i*dimen_matriz+j)+1<<" da matriz A"<<endl;
				cin>>matriz[i][j];
			}		
		}
	
		system("cls"); 
	
		cout<<"\n";
		double aux;
		for(int i=0;i<dimen_matriz;i++){
			cout<<"Digite o elemento "<<i+1<<" do vetor b"<<endl;
			cin>>aux;
			vector_b.push_back(aux);
		}		
    }
	
	print_matrix(matriz,dimen_matriz);                      
	vector<double> factor=matrix_u(matriz,dimen_matriz);
	vector<vector<double> > matrix_factor=matrix_l(factor,dimen_matriz);
	vector<double> y=vector_y(factor,vector_b,dimen_matriz);
	vector<double> x=vector_x(matriz,y,dimen_matriz);
	
	system("cls"); 
	cout<<"############TRABALHO DE METODOS############\n Fatoracao LU\n"<<endl;
	
	cout<<"Matriz U:"<<endl;
	print_matrix(matriz,dimen_matriz);
	cout<<"Matriz L:"<<endl;
	print_matrix(matrix_factor,dimen_matriz);
	cout<<"Vetor Y:"<<endl;
	print_vector(y,dimen_matriz);
	cout<<"Vetor X invertido:"<<endl;
	print_vector(x,dimen_matriz);
	
	cout<<"Resultado: "<<endl;
	
	for(int i=dimen_matriz-1;i>=0;i--){
		cout<<"X"<<count<<"="<<x[i]<<endl;
		count++;
	}
	
}

vector<double> vector_x(vector<vector<double> > matrix, vector<double> y,int len){
	
	vector<double> x; double aux=0,count=0;
	
	x.push_back(y[len-1]/matrix[len-1][len-1]);
	
	for(int i=len-2;i>=0;i--){
		for(int k=len-2;k>=i;k--){
			aux=aux+(-1)*(matrix[i][k+1])*x[count];	
			count++;
		}
		x.push_back((y[i]+aux)/matrix[i][i]);
		aux=0; count=0;
	}
	
	return x;
}

vector<double> vector_y(vector<double> factor,vector<double> vector_b,int len){
	
	vector<double> y; double aux=0,count=0;
	
	y.push_back(vector_b[0]);
	
	for(int i=1;i<len;i++){
		for(int k=0;k<i;k++){
			aux=aux+(-1)*factor[k+count]*y[k];
		}
		y.push_back(aux+vector_b[i]);    
		aux=0;
		count++;
	}
	
	return y;
	
}

vector<double> matrix_u(vector<vector<double> >& matriz,int len){
	
	double pivot=0,aux=0;
	
	vector<double> factor;
	
	for(int k=0;k<len;k++){
		pivot=matriz[k][k];	
		for(int i=0;i<len;i++){
			if(i>k){
				aux=matriz[i][k];
				factor.push_back(aux/pivot);
				for(int j=0;j<len;j++){
					matriz[i][j]=matriz[i][j]-matriz[k][j]*aux/pivot;
				}
			}
		}	
	}
	
	return factor;
}


vector<vector<double> > matrix_l(vector<double> factor,int len){
	
	vector<vector<double> > matrix=create_matrix(len);
	int count=0;
	
	for(int i=0;i<len;i++){
		matrix[i][i]=1;
	}
	
	for(int i=1;i<len;i++){
		for(int j=0;j<i;j++){
			matrix[i][j]=factor[count];
			count++;
		}
	}
	
	return matrix;
		
}

void adotar_padrao(vector<vector<double> > &matriz,vector<double> &vector_b){
	
	int aux1[3]={16,38,38},aux2[9]={20,7,9,7,30,8,9,8,30},count=0;
	
	while(count<3){
		if(count<3)
			vector_b.push_back(aux1[count]);
		for(int i=0;i<3;i++){
			matriz[count][i]=aux2[3*count+i];
		}
		count++;
	}
}

vector<vector<double> > create_matrix(int len){
	
	vector<vector<double> > matriz(len,vector<double>(len));
	
	return  matriz;
	
}

void print_matrix(vector<vector<double> > matriz,int len){
		
	for(int i=0;i<len;i++){
		for(int j=0;j<len;j++){
			cout<<matriz[i][j]<<" ";
		}
		cout<<"\n";		
	}		
	cout<<"\n";	
}

void print_vector(vector<double> vetor,int len){
	
	cout<<"[ ";
	for(int i=0;i<len;i++){
		cout<<vetor[i]<<" ";
	}
	cout<<"]"<<endl;
}
