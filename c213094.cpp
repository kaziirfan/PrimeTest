#include<iostream>
#include<fstream>

using namespace std;
int main()
{
  int arr[100],i,j,f=0,cnt=0;

  ifstream fin("input.txt");
  ofstream fout("output.txt");
  for(i=0;!fin.eof();i++)
    {
        fin>>arr[i];
        cnt++;

    }

    for(i=0;i<cnt;i++)
    {
        if(arr[i]== 0|| arr[i]== 1)
        {
            f=2;
        }
        else
        {
            for(j=2;j<=arr[i]/2;j++)
            {
                if(arr[i]%j==0)
                {
                    f=2;
                    break;
                }
                else
                {
                    f=1;
                }
            }
        }
        if(arr[i]==2)
        {
            f=1;
        }

        if(f==1)
        {
           fout<<arr[i]<< " is prime"<< endl;

        }
        else if(f==2)
        {
            fout<<arr[i]<< " is composite"<< endl;
        }
    }



        return 0;
}








