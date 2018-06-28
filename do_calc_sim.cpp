#include <vector>
#include <string>
#include <fstream>
#include <boost/timer.hpp>
#include <boost/progress.hpp>
#include "gen_img_fingerprint.h"

#include <dirent.h>

#define SIM_THRESH 10

void usage(){
    cout<<"Usage: do_detect_sim /path/to/pic_dir"<<endl;
}

void getFileName(string fileDir, vector<string> *imglist){
    DIR *dir;
    struct dirent *ptr;
    string filename;
    if((dir=opendir(fileDir.c_str()))==NULL){
        cout<<"[ERROR] open img dir error"<<endl;
        exit(1);
    }
    while((ptr=readdir(dir))!=NULL){
        if(strcmp(ptr->d_name, "..")==0) continue;
        if(strcmp(ptr->d_name, ".")==0) continue;
        if(ptr->d_name[0] == '.') continue;
        filename = ptr->d_name;
        if(filename.substr(filename.find_last_of(".")+1)=="jpg" || filename.substr(filename.find_last_of(".")+1)=="bmp"){
            string filepath = fileDir + filename;
            imglist->push_back(filepath);
            cout<<"img file->\t"<<filepath<<endl;
        } 
    }
    closedir(dir);
}


int main(int argc, char* argv[]){
    if(argc!=2){
        usage();
        return 0;    
    }
    vector<string> vec;
    getFileName(argv[1], &vec); 

    
    ofstream out;
    out.open("./calc_sim_results.txt");
    if(!out.is_open()){
        cout<<"[ERROR] open file error"<<endl;
        return 0;
    }
    
    cout<<"find total "<<vec.size()<<" img"<<endl;
    
    int cnt = 0;
    for(int i=vec.size()-1; i>0; i--)
        cnt+=i;
    cout<<"total step "<<cnt<<endl;
    boost::progress_display pd(cnt);
    boost::progress_timer time_keeper;

    for(auto iter1=vec.begin(); iter1!=vec.end(); iter1++){
        for(auto iter2=iter1+1; iter2!=vec.end(); iter2++){
            Mat pic1 = imread(*iter1);
            Mat pic2 = imread(*iter2);
            int sim = CalcPictureSimilar(pic1, pic2);
            if(sim < SIM_THRESH){
                out<<*iter1<<"\t"<<*iter2<<"\t"<<sim<<endl;
            }
            ++pd;
        }
    }
    out.close();
    
    return 0;
}

