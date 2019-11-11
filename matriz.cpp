#include <iostream>
#include <locale.h>
#include <vector>
#include <conio.h>
using namespace std;

vector<vector<double> > create_matrix(int len);
void print_matrix(vector<vector<double> > matriz,int len);              
void print_vector(vector<double> vetor,int len);
void adotar_padrao(vector<vector<double> > &matriz,vector<double> &vector_b);
vector<double> matrix_LU(vector<vector<double> > matriz,int len,vector<double> vector_b);            
vector<double> matrix_doolittle(vector<vector<double> > matriz,int len,vector<double> vector_b);
vector<vector<double> > matrix_l(vector<double> factor,int len);      
vector<double> vector_y(vector<double> factor,vector<double> vector_b,int len); 
vector<double> vector_x(vector<vector<double> > matrix, vector<double> y,int len); 


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
		adotar_padrao(matriz,vector_b);
		dimen_matriz=3;
	}else{
		for(int i=0;i<dimen_matriz;i++){
			for(int j=0;j<dimen_matriz;j++){
				cout<<"Digite o elemento "<<(i*dimen_matriz+j)+1<<" da matriz A"<<endl;
				cin>>matriz[i][j];
			}		
		}
		vector<vector<double> > matriz=create_matrix(3);
		system("cls"); 
	
		cout<<"\n";
		double aux;
		for(int i=0;i<dimen_matriz;i++){
			cout<<"Digite o elemento "<<i+1<<" do vetor b"<<endl;
			cin>>aux;
			vector_b.push_back(aux);
		}		
    }
    system("cls");
    
    cout<<"\n\n Dados metodo LU"<<endl;
    vector<double> LU_x=matrix_LU(matriz,dimen_matriz,vector_b);
    cout<<"\nDados metodo doolittle:\n"<<endl;
	vector<double> doolittle_x =matrix_doolittle(matriz,dimen_matriz,vector_b);
	cout<<"\n\n#####Tabela resultado:#####\n\n     LU   doolittle\n"<<endl;
	
	vector<double>::iterator it=doolittle_x.begin();
	vector<double>::iterator it2=LU_x.begin();
	
	for(int i=dimen_matriz-1;i>=0;i--){
		cout<<"X"<<dimen_matriz-i<<"    "<<*(it2+i)<<"     "<<*(it+i)<<endl;
	}

}

vector<double> matrix_doolittle(vector<vector<double> > matriz,int len,vector<double> vector_b){
	
	vector<vector<double> > matrix_u=create_matrix(len);
	vector<vector<double> > matrix_l=create_matrix(len);
	vector<double> factor;
	double soma=0; int count1=0,count2=1;
	
	for(int i=0;i<len;i++){
		for(int j=i;j<len;j++){
			soma=0;	
			for(int z=0;z<i;z++)
				soma=soma+(matrix_l[i][z]*matrix_u[z][j]);
			matrix_u[i][j]=matriz[i][j]-soma; 
 		}
		for(int j=i;j<len;j++){
			if(i==j){
				matrix_l[i][i]=1;
			}else{
				soma=0;
				for(int z=0;z<i;z++){
					soma=soma+(matrix_l[j][z]*matrix_u[z][i]);
				}
				matrix_l[j][i]=(matriz[j][i]-soma)/matrix_u[i][i];
				}
			}			
		}
	
	for(int i=1;i<len;i++){
		for(int j=0;j<i;j++){
			factor.push_back(matrix_l[i][j]);
		}
	}
	
	vector<double> y=vector_y(factor,vector_b,len);
	vector<double> x=vector_x(matrix_u,y,len);
	
	cout<<"Matriz U:"<<endl;
	print_matrix(matrix_u,len);
	cout<<"Matriz L:"<<endl;
	print_matrix(matrix_l,len);
	cout<<"Vetor Y:"<<endl;
	print_vector(y,len);
	
	return x;
	
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

vector<double> matrix_LU(vector<vector<double> > matriz,int len,vector<double> vector_b){
	
	double pivot=0,aux=0; int count=1;
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
	
	vector<vector<double> > matrix_factor=matrix_l(factor,len);
	vector<double> y=vector_y(factor,vector_b,len);
	vector<double> x=vector_x(matriz,y,len);
	
	system("cls"); 
	cout<<"############TRABALHO DE METODOS############\n Fatoracao LU\n"<<endl;
	cout<<"Matriz U:"<<endl;
	print_matrix(matriz,len);
	cout<<"Matriz L:"<<endl;
	print_matrix(matrix_factor,len);
	cout<<"Vetor Y:"<<endl;
	print_vector(y,len);
	
	return x;
	
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
