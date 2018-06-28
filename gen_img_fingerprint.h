#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int CalcPictureSimilar(Mat pic1, Mat pic2);
unsigned long long int GenerateTextureFingerprint(Mat texturePic);
void DetermineSimilarPicture(Mat pic1, Mat pic2);
int hamming(unsigned long long int h1, unsigned long long int h2);


