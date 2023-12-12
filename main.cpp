#include <bits/stdc++.h>
using namespace std;

float shunting_yard(float num[], char symb[])
{
    deque<float> x;
    deque<char> y;
    
    for(int i = 0; i < 3; i++)
    {
        if(symb[i] == 'x')
        {
            float res = num[i]*num[i+1];
            if(i == 2)
            {
                x.push_back(res);
            }
            else num[i+1] = res;
        }
        else if(symb[i] == ':')
        {
            float res = num[i]/num[i+1];
            if(i == 2)
            {
                x.push_back(res);
            }
            else num[i+1] = res;
        }
        else if(symb[i] == '-' || symb[i] == '+')
        {
            if(i == 2) 
            {
                x.push_back(num[i]); x.push_back(num[i+1]);
                y.push_back(symb[i]);
            }
            else
            {
                x.push_back(num[i]);
                y.push_back(symb[i]);
            }
        }
    }
    float ans;
    while(!y.empty())
    {
        char sign = y.front(); y.pop_front();
        float a = x.front(); x.pop_front();
        float b = x.front(); x.pop_front();
        ans = (sign == '+')? (a+b) : (a-b);
        x.push_front(ans);
    }
    return ans;
}

void PRINT_EQUATION(int num[], char symb[], int root)
{
    for(int i = 0; i < 4; i++)
    {
        if(i == root)
        {
            cout << "SQRT(" << num[i] << ")";
        }
        else
        {
            cout << num[i];
        }
        if(i != 3) cout << " " << symb[i] << " ";
    }
    cout << '\n';
}

int main()
{
    // INTRO :)
    cout << "=== EQUATION HI-LOW ===" << '\n';
    
    // Input jumlah pemain
    cout << "Silahkan masukkan jumlah pemain : ";
    int jumlahPemain; cin >> jumlahPemain;

    // Deklarasi array data pemain
    int  ANGKA[jumlahPemain][3];
    char SIMBOL[jumlahPemain][3];
    bool AKAR[jumlahPemain];

    // Input data pemain
    for(int i = 0; i < jumlahPemain; i++)
    {
        cout << "INPUT DATA PEMAIN KE -" << i+1 << '\n';
        for(int j = 0; j < 3; j++)
        {
            cout << "Masukkan kartu ke -" << j+1 << " : ";
            cin >> ANGKA[i][j];
        }
        for(int j = 0; j < 3; j++)
        {
            cout << "Masukkan simbol ke -" << j+1 << " (selain kartu akar) : ";
            cin >> SIMBOL[i][j];
        }
        sort(SIMBOL[i], SIMBOL[i]+3);
        cout << "Apakah pemain memiliki kartu akar? (y/n) : ";
        char temp; cin >> temp;
        if(temp == 'y' || temp == 'Y') AKAR[i] = true;
        else AKAR[i] = false;   
    }

    float LOW[jumlahPemain];
    float HIGH[jumlahPemain];

    for(int i = 0; i < jumlahPemain; i++)
    {
        LOW[i] = INT_MAX;
        HIGH[i] = INT_MAX;
    }

    int LOW_NUM[jumlahPemain][4];
    char LOW_SYMB[jumlahPemain][3];
    int LOW_ROOT_POS[jumlahPemain];
    int REQ_LOW[jumlahPemain];

    int HIGH_NUM[jumlahPemain][4];
    char HIGH_SYMB[jumlahPemain][3];
    int HIGH_ROOT_POS[jumlahPemain];
    int REQ_HIGH[jumlahPemain];

    for(int i = 0; i < jumlahPemain; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            int TEMPORARY[4];
            for(int k = 0; k < 3; k++) TEMPORARY[k] = ANGKA[i][k];
            TEMPORARY[3] = j;

            do
            {
                do
                {
                    bool undef = false;
                    for(int k = 0; k < 3; k++)
                    {
                        if(SIMBOL[i][k] == ':' && TEMPORARY[k+1] == 0) undef = true;
                    }
                    if(undef) continue;

                    if(AKAR[i])
                    {
                        for(int k = 0; k < 4; k++)
                        {
                            float CUR[4];
                            for(int x = 0; x < 4; x++) CUR[x] = (x == k)? sqrt(TEMPORARY[x]) : TEMPORARY[x];
                            float value = shunting_yard(CUR, SIMBOL[i]);
                            if(abs(1-value) < abs(1-LOW[i]))
                            {
                                LOW_ROOT_POS[i] = k;
                                LOW[i] = value;
                                for(int x = 0; x < 4; x++) LOW_NUM[i][x] = TEMPORARY[x];
                                for(int x = 0; x < 3; x++) LOW_SYMB[i][x] = SIMBOL[i][x];
                                REQ_LOW[i] = j;
                            }
                            if(abs(20-value) < abs(20-HIGH[i]))
                            {
                                HIGH_ROOT_POS[i] = k;
                                HIGH[i] = value;
                                for(int x = 0; x < 4; x++) HIGH_NUM[i][x] = TEMPORARY[x];
                                for(int x = 0; x < 3; x++) HIGH_SYMB[i][x] = SIMBOL[i][x];
                                REQ_HIGH[i] = j;
                            }
                        }
                    }
                    else
                    {
                        float CUR[4];
                        for(int x = 0; x < 4; x++) CUR[x] = TEMPORARY[x];
                        float value = shunting_yard(CUR, SIMBOL[i]);
                        if(abs(1-value) < abs(1-LOW[i]))
                        {
                            LOW_ROOT_POS[i] = -1;
                            LOW[i] = value;
                            for(int x = 0; x < 4; x++) LOW_NUM[i][x] = TEMPORARY[x];
                            for(int x = 0; x < 3; x++) LOW_SYMB[i][x] = SIMBOL[i][x];
                            REQ_LOW[i] = j;
                        }
                        if(abs(20-value) < abs(20-HIGH[i]))
                        {
                            HIGH_ROOT_POS[i] = -1;
                            HIGH[i] = value;
                            for(int x = 0; x < 4; x++) HIGH_NUM[i][x] = TEMPORARY[x];
                            for(int x = 0; x < 3; x++) HIGH_SYMB[i][x] = SIMBOL[i][x];
                            REQ_HIGH[i] = j;
                        }
                    }
                } while (next_permutation(TEMPORARY, TEMPORARY+4)); 
            } while (next_permutation(SIMBOL[i], SIMBOL[i]+3));
            

        }
    }

    for(int i = 0; i < jumlahPemain; i++)
    {
        cout << "LANGKAH TERBAIK PEMAIN KE -" << i+1 << '\n';
        cout << '\n';
        cout << "ANGKA TERDEKAT KE 1 : " << LOW[i] << '\n';
        cout << "DENGAN JARAK : " << abs(1-LOW[i]) << '\n';
        cout << "JIKA MENDAPATKAN KARTU : " << REQ_LOW[i] << '\n';
        cout << "DAN MENGGUNAKAN PERSAMAAN : "; PRINT_EQUATION(LOW_NUM[i], LOW_SYMB[i], LOW_ROOT_POS[i]);
        cout << '\n';
        cout << "ANGKA TERDEKAT KE 20 : " << HIGH[i] << '\n';
        cout << "DENGAN JARAK : " << abs(20-HIGH[i]) << '\n';
        cout << "JIKA MENDAPATKAN KARTU : " << REQ_HIGH[i] << '\n';
        cout << "DAN MENGGUNAKAN PERSAMAAN : "; PRINT_EQUATION(HIGH_NUM[i], HIGH_SYMB[i], HIGH_ROOT_POS[i]);
        cout << '\n';
    }
}