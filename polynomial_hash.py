# https://leetcode.com/problems/longest-palindromic-substring/

s = input()
n = len(s)
p = 239
mod = 10**9 + 7

class Hash:
    def __init__(self, s):
        self.h = [ord(s[0])]
        self.n = len(s)
        for i in range(1, self.n):
            self.h += [(self.h[i-1] + ord(s[i])*p**i)%mod]
    
    def get(self, l, r):
        return ((self.h[r-1]-self.h[l])*p**(self.n-l))%mod


h, rh = Hash(s), Hash(s[::-1])
bl = 0
bs = ""

def odd_palindrome(i):
    global bl, bs
    i //= 2
    l = 0; r = min(i, n-i-1)+1
    while r - l > 1:
        m = (l+r)//2
        lx = i-m
        rx = i+m+1
        if h.get(lx,rx) == rh.get(n-rx,n-lx):
            l = m
        else:
            r = m
    
    if 2*l + 1 > bl:
        bs = s[i-l:i+l+1]
        bl = 2*l + 1

def even_palindrome(i):
    global bl, bs
    l_bound = (i - 1)//2
    r_bound = (i + 1)//2
    l = 0; r = min(l_bound, n-r_bound-1)+1
    while r - l > 1:
        m = (l+r)//2
        lx = l_bound-m
        rx = r_bound+m+1

        if h.get(lx,rx) == rh.get(n-rx,n-lx):
            l = m
        else:
            r = m
    
    if 2*l+2 > bl:
        bs = s[l_bound-l:r_bound+l+1]
        bl = 2*l+2


for i in range(2*n):
    if i%2: odd_palindrome(i)
    else: even_palindrome(i)

print(bs)