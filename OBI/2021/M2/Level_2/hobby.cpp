#include<iostream>
#include<vector>
#include<map>

// 90 points... Why OBI? Why?
// The solution of your for this is totally a shit!
// Dont have any funcion, and how can a programmer
// rearch the 100 pounts in the time of contest?
// Just an insane can complet this man.
// Or the naphew of owner of OBI...

template<typename T>
using VECTOR = std::vector<T>;
template<typename T>
using MATRIX = std::vector<std::vector<T>>;

template<typename T,typename U>
using MAP = std::map<T,U>;

using STRING = std::string;
//
bool map_match(const MAP<STRING,int>letters_values,const STRING item){
    if(letters_values.find(item)==letters_values.end())
        return false;
    return true;
}

bool matrix_discover_vars
(const MATRIX<std::string>matrix,const VECTOR<int>row_sum,
 MAP<std::string,int>&letters_values){
    bool change=false;
    for(size_t i=0;i<matrix.size();++i){
        STRING var_id="";
        int var_count=0;

        int sum_out=0;
        int line_accept=0;
        for(size_t j=0;j<matrix[i].size();++j){
            std::string element=matrix[i][j];

            if(element==var_id){
                ++var_count;
                continue;
            }
            if(map_match(letters_values,element)){
                sum_out+=letters_values[element];
                continue;
            }
            if(!map_match(letters_values,element)&&!var_id.length()){
                var_id=element;
                var_count=1;
                line_accept=1;
                continue;
            }

            line_accept=0;
            break;
        }

        if(!line_accept)
            continue;

        letters_values[var_id]=(row_sum[i]-sum_out)/var_count;


        change=true;
    }

    return change;
}

MATRIX<STRING> matrix_spin(const MATRIX<STRING>&matrix){
    MATRIX<std::string>matrix_new(matrix[0].size(),VECTOR<std::string>(matrix.size()));
    for(size_t i=0;i<matrix.size();++i)
        for(size_t j=0;j<matrix[i].size();++j)
            matrix_new[j][i]=matrix[i][j];

    return matrix_new;
}

void matrix_display(const MATRIX<std::string>&matrix){
    for(size_t i=0;i<matrix.size();++i){
        for(size_t j=0;j<matrix[i].size();++j)
            std::cout<<matrix[i][j]<<" ";
        std::cout<<"\n";
    }
    std::cout<<"\n";
}

//
int main(){
    std::ios_base::sync_with_stdio(false);std::cin.tie(NULL);std::cout.tie(NULL);
    size_t n,m;
    std::cin>>n>>m;

    MATRIX<std::string>matrix(n,VECTOR<std::string>(m));
    VECTOR<int>row_sum(n),colm_sum(m);
    for(size_t i=0;i<n;++i){
        for(size_t j=0;j<=m;++j){
            std::string item;
            std::cin>>item;

            if(j==m){
                row_sum[i]=std::stoi(item);
                break;
            }
            matrix[i][j]=item;
        }
    }
    for(size_t i=0;i<m;++i){
        std::string item;
        std::cin>>item;
        colm_sum[i]=std::stoi(item);
    }

    MATRIX<STRING>matrix_spined=matrix_spin(matrix);
    MAP<STRING,int>letters_values;

    while(1){
        bool change_row=matrix_discover_vars(matrix,row_sum,letters_values);
        bool change_colm=matrix_discover_vars(matrix_spined,colm_sum,letters_values);
        if(!change_row&&!change_colm)
            break;

    }

    for(auto i:letters_values)
        std::cout<<i.first<<" "<<i.second<<"\n";

    return 0;
}
