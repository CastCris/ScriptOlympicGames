#include<iostream>
#include<vector>

template<typename T>
using VECTOR = std::vector<T>;

class BIT{
    private:
        VECTOR<int>bit_vct;

        int lsb(int n){
            return n&(-n);
        }

    public:
        BIT(const VECTOR<int>vct){
            bit_vct.clear();
            bit_vct.push_back(0);
            for(size_t i=0;i<vct.size();++i)
                bit_vct.push_back(0);

            for(size_t i=1;i<=vct.size();++i)
                update(i, vct[i-1]);
        }

        void update(size_t index, int delta){
            while(index<bit_vct.size()){
                bit_vct[index]+=delta;
                index+=lsb(index);
            }
        }

        void display(){
            for(size_t i=0;i<bit_vct.size();++i)
                printf("%i ",bit_vct[i]);
            printf("\n");
        }

};

int main(){
    BIT tst({1,1,6,4,9});
    tst.display();
    
    return 0;
}
