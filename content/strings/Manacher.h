/**
 * Author: deuslovelt
 * Date: 2022-11-08
 * License: CC0
 * Source: 
 * Description: abcd
 */

int cir[max_v];

int main()
{
    string t; ci(t);

    string s = "#";
    reverse(t.begin(), t.end());
    while (t.size()) s += t.back(), s += '#', t.pop_back();

    int n = s.size();

    auto mana = [&]()
    {
        int r = 0, p = 0;
        fa(i,0,n)
        {
            cir[i] = i <= r ? min(cir[2*p-i],r-(int)i): 0;

            while (i - cir[i] - 1 >= 0 && i + cir[i] + 1 < n && s[i - cir[i] - 1] == s[i + cir[i] + 1]) ++cir[i];

            if (r < i + cir[i]) r = i + cir[i], p = i;            
        }
    };

    mana();    
    fa(i, 1, n-1) co(cir[i] << " ");
    return 0;
}
