#include <iostream>
#include <math.h>
#include <vector>
#include <time.h>
#include <windows.h>

using std::cout;
using std::endl;
using std::vector;

vector<vector<vector<int>>> ten_rand_xyz (10, vector<vector<int>>(10, vector<int>(10, 0)));
float randsSizeX = float(ten_rand_xyz.size());
float randsSizeY = float(ten_rand_xyz[0].size());
float randsSizeZ = float(ten_rand_xyz[0][0].size());

int seed_rand()
{
    return rand() % 100;
}

float fromWave3d(float axisPositionX, float axisPositionY, float axisPositionZ, vector<vector<vector<int>>> rands)
{
    //four points need to be looked up
    //x1,y1, x1,y2, x2,y1, x2,y2

    float x = axisPositionX*randsSizeX;

    float ax1 = std::floor(axisPositionX*randsSizeX);//needs to round down
    float ax1m = fmod(ax1, randsSizeX);
    float ax2 = ax1+1.0;
    float ax2m = fmod(ax2, randsSizeX);

    float y = axisPositionY*randsSizeY;

    float ay1 = std::floor(axisPositionY*randsSizeY);//needs to round down
    float ay1m = fmod(ay1, randsSizeY);
    float ay2 = ay1+1.0;
    float ay2m = fmod(ay2, randsSizeY);

    float z = axisPositionZ*randsSizeZ;

    float az1 = std::floor(axisPositionZ*randsSizeZ);//needs to round down
    float az1m = fmod(az1, randsSizeZ);//fmod creates wrap around
    float az2 = az1+1.0;
    float az2m = fmod(az2, randsSizeZ);


    float x1y1z1 = rands[ax1m][ay1m][az1m];
    float x2y1z1 = rands[ax2m][ay1m][az1m];
    float xy1z1 = ((ax2m - x)/(ax2m - ax1m)) * x1y1z1 + ((x - ax1m)/(ax2m - ax1m)) * x2y1z1;

    float x1y2z1 = rands[ax1m][ay2m][az1m];
    float x2y2z1 = rands[ax2m][ay2m][az1m];
    float xy2z1 = ((ax2m - x)/(ax2m - ax1m)) * x1y2z1 + ((x - ax1m)/(ax2m - ax1m)) * x2y2z1;

    float x1y1z2 = rands[ax1m][ay1m][az2m];
    float x2y1z2 = rands[ax2m][ay1m][az2m];
    float xy1z2 = ((ax2m - x)/(ax2m - ax1m)) * x1y1z2 + ((x - ax1m)/(ax2m - ax1m)) * x2y1z2;

    float x1y2z2 = rands[ax1m][ay2m][az2m];
    float x2y2z2 = rands[ax2m][ay2m][az2m];
    float xy2z2 = ((ax2m - x)/(ax2m - ax1m)) * x1y2z2 + ((x - ax1m)/(ax2m - ax1m)) * x2y2z2;
    //x is the pair meeting
    float xyz1 = ((ay2m - y)/(ay2m - ay1m)) * xy1z1 + ((y - ay1m)/(ay2m - ay1m)) * xy2z1;
    float xyz2 = ((ay2m - y)/(ay2m - ay1m)) * xy1z2 + ((y - ay1m)/(ay2m - ay1m)) * xy2z2;

    float xyz = ((az2m - z)/(az2m - az1m)) * xyz1 + ((z - az1m)/(az2m - az1m)) * xyz2;
    return xyz;

}

void printNoise(float zIncrement)
{
        float xSize = 50.0;
        float ySize = 50.0;

        float xIncrement = 1.0 / xSize;
        float yIncrement = 1.0 / ySize;

        char chara1[int(xSize*ySize+xSize+1.0)];

        chara1[0] = '\n';

        int iInt = 0;
        for(float i = 0.00; i <= 1.00; i = i + yIncrement, iInt++)
        {
            int jInt = 1;

            for(float j = 0.00; j <= 1.00; j = j + xIncrement, jInt++)
            {
                float uh = 1.0;
                float index = (xSize * iInt) + jInt;
                int iindex = int(index);

                float k = fromWave3d(i, j, zIncrement, ten_rand_xyz);//THIS wat i causing it?

                if (k > 80) {        chara1[iindex] = 219;}
                else if (k > 60) {   chara1[iindex] = 178;}
                else if (k > 40) {   chara1[iindex] = 177;}
                else if (k > 20) {   chara1[iindex] = 176;}
                else {               chara1[iindex] = ' ';}

                if (jInt == int(xSize)) {chara1[iindex] = '\n';}

            }

            chara1[int(iInt*xSize+jInt-1)] = '\0';
            jInt++;

        }
    cout << chara1 << endl;

}

float increment = 0;

void printFlow()
{
    system ("CLS");
    printNoise(increment);
    increment += 0.02;
    increment = fmod(increment, 1.0);
    //system("pause");
    Sleep(200);
    printFlow();
}

int main()
{
    srand(time(NULL));
    int i = 0;
    for (vector<vector<int>> & r : ten_rand_xyz)
    {
        for (vector<int> & s : r)
        {
            for (int & t : s)
            {
                //cout << i << ", ";
                t = seed_rand();
                i++;
            }
        }
    }

    printFlow();
    return 0;
}
