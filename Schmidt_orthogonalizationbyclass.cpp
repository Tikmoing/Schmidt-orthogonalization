#include<iostream>
#include<ctime>
#include<random>
#include<vector>
#include<string>
#include<windows.h>
#include<cmath>

using namespace std;

class vectorOperate{
    public :
        //输出一个向量
        static void printVector(vector<double> inpus){
            for(int i = 0 ; i < inpus.size() ; i ++) cout<<inpus[i]<<" ";
            cout<<endl;
        }
        //生成一个随机向量
        static vector<double> getVector(int dim){
            vector<double> res;
            default_random_engine send(time(NULL));
            uniform_real_distribution<double> randDouble(-5,5);
            for(int i = 0 ; i < dim ; i ++) res.push_back(randDouble(send));
            Sleep(1000);
            return res;
        }
        //内积
        static double scalarProduct(vector<double> A,vector<double> B){
            if(A.size() != B.size()) return -1;
            double res = 0;
            for(int i = 0 ; i < A.size() ; i ++) res += A[i]*B[i];
            return res;
        }
        //内积开方
        static double scalarProductSqrt(vector<double> A,vector<double> B){
            return sqrt( scalarProduct(A,B) );
        }
        //和
        static  vector<double> add(vector<double> A,vector<double> B){
            for(int i = 0 ; i < A.size() ; i ++)  A[i] += B[i];
            return A;
        }
        //减
        static  vector<double> minus(vector<double> A,vector<double> B){
            for(int i = 0 ; i < A.size() ; i ++ ) A[i] -= B[i];
            return A;
        }

        //数乘
        static vector<double> mulit(double lambda,vector<double> B){
            for(int i = 0 ; i < B.size() ; i ++) B[i] *= lambda;
            return B;
        }

};

vector<double> signInBaisVector(vector<double> target,vector<vector<double>> bais); //在基向量集中进行表示
vector<vector<double>> schmidtOrthogonalization(vector<vector<double>> inpus);  //施密特正交化
vector<vector<double>> getBaisVector(int dimension); //得到单位正交化基向量集

int main(void){
    cout<<"Please input the dimension of your vector:"<<endl;
    int dimension;
    cin>>dimension;
    vector<vector<double>> bais = getBaisVector(dimension);
    for(int i = 0 ; i < bais.size() ; i ++){
        vectorOperate::printVector(bais[i]);
    }

    vector<double> myvector = vectorOperate::getVector(dimension);
    vector<double> signIn = signInBaisVector(myvector,bais);

    cout<<"Problem Vector:"<<endl;
    vectorOperate::printVector(myvector);
    cout<<"In baisVector:"<<endl;
    vectorOperate::printVector(signIn);
    system("pause");
    return 0;
}

//在基向量集中进行表示
vector<double> signInBaisVector(vector<double> target,vector<vector<double>> bais){
    vector<double> res;
    for(int i = 0 ; i < bais.size() ; i ++){
        res.push_back(  vectorOperate::scalarProduct(target,bais[i]) );
    }
    return res;
}

//生成基向量集
vector<vector<double>> getBaisVector(int dimension){
    vector<vector<double>> res;
    for(int i = 0 ; i < dimension; i ++){
        res.push_back( vectorOperate::getVector(dimension) );
        // printVector(res[i]);
    }

    res = schmidtOrthogonalization(res);
    return res;
}

//施密特正交化
vector<vector<double>> schmidtOrthogonalization(vector<vector<double>> inpus){
    vector<vector<double>> res;
    
    res.push_back(vectorOperate::mulit(1/vectorOperate::scalarProductSqrt(inpus[0],inpus[0]),inpus[0]));

    for(int i = 1 ; i < inpus.size() ; i ++){
        for(int j = i-1 ; j >= 0; j --){
            inpus[i] = vectorOperate::add(  inpus[i] , vectorOperate::mulit( -vectorOperate::scalarProduct( inpus[i],res[j] ),  res[j])  );
        } 
        res.push_back(vectorOperate::mulit( 1/vectorOperate::scalarProductSqrt(inpus[i],inpus[i]) , inpus[i] ));
    }
    return res;    
}

