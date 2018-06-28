#include "gen_img_fingerprint.h"

void usage(){
    cout<<"Usage: do_detect_sim pic1 pic2"<<endl;
}

int main(int argc, char* argv[]){
    if(argc!=3){
        usage();
        return 0;    
    }
    string img_file1 = argv[1];
    string img_file2 = argv[2];
    Mat img1 = imread(img_file1);
    Mat img2 = imread(img_file2);
    
    DetermineSimilarPicture(img1, img2);
    return 0;
}
