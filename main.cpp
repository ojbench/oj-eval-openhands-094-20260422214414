#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    if(!(cin >> m >> n)) return 0;
    vector<vector<int>> a(m, vector<int>(n));
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++) cin >> a[i][j];
    }

    auto inb = [&](int i, int j){ return i>=0 && i<m && j>=0 && j<n; };

    // Output 3m rows, 3n cols
    int H = 3*m, W = 3*n;
    vector<int> out_row(W);

    for(int r=0;r<H;r++){
        int bi = r/3; int di = r%3; // block row index and offset
        for(int c=0;c<W;c++){
            int bj = c/3; int dj = c%3; // block col index and offset
            if(di==1 && dj==1){
                out_row[c] = a[bi][bj];
            } else {
                // non-center point: compute A/B classes by Manhattan distance to centers
                // center positions have coordinates (3*i+1, 3*j+1)
                int cr = r, cc = c;
                long long sumA=0, cntA=0, sumB=0, cntB=0;
                // We'll check neighbor centers within range so that manhattan distance 1 or 2
                // That means centers with |(3*i+1)-r| + |(3*j+1)-c| equal to 1 or 2.
                // Candidate i in [bi-1..bi+1], j in [bj-1..bj+1] is sufficient.
                for(int ii = bi-1; ii<=bi+1; ++ii){
                    for(int jj = bj-1; jj<=bj+1; ++jj){
                        if(!inb(ii,jj)) continue;
                        int center_r = 3*ii + 1;
                        int center_c = 3*jj + 1;
                        int d = abs(center_r - cr) + abs(center_c - cc);
                        if(d==1){ sumA += a[ii][jj]; cntA++; }
                        else if(d==2){ sumB += a[ii][jj]; cntB++; }
                    }
                }
                int val = 0;
                if(cntA==0 && cntB>0){
                    val = (int)floor((double)sumB / cntB);
                } else if(cntB==0 && cntA>0){
                    val = (int)floor((double)sumA / cntA);
                } else if(cntA>0 && cntB>0){
                    double meanA = (double)sumA / cntA;
                    double meanB = (double)sumB / cntB;
                    val = (int)floor(meanA*0.8 + meanB*0.2);
                } else {
                    // no neighbors (shouldn't happen except tiny images where unreachable), fallback to nearest center
                    val = a[bi][bj];
                }
                if(val<0) val=0; if(val>100) val=100;
                out_row[c] = val;
            }
        }
        for(int c=0;c<W;c++){
            cout << out_row[c] << (c+1==W? '\n' : ' ');
        }
    }
    return 0;
}
