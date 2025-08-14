#include<iostream>
#include<vector>
#include<map>
#include<set>

//
int main(){
    int n;
    std::cin>>n;

    std::map<std::string, int>str_map;
    std::vector<std::string>str_vct;
    for(int i=0;i<n;++i){
        std::string str_inp;
        std::cin>>str_inp;

        std::set<std::string>str_set;
        for(size_t j=0;j<str_inp.length();++j){
            for(size_t k=j;k<str_inp.length();++k){
                std::string substring;
                for(size_t l=j;l<=k;++l)
                    substring+=str_inp[l];

                if(str_set.find(substring)!=str_set.end())
                    continue;
                str_set.insert(substring);

                if(str_map.find(substring)==str_map.end()){
                    str_map[substring]=1;
                    continue;
                }
                ++str_map[substring];
            }
        }

        str_vct.push_back(str_inp);
    }

    int tot=0;
    for(size_t i=0;i<str_vct.size();++i){
        // std::cout<<str_map[str_vct[i]]<<" "<<str_vct[i]<<"\n";
        tot+=str_map[str_vct[i]]-1;
    }

    std::cout<<tot<<"\n";

    return 0;
}
