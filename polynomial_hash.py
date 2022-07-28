# https://leetcode.com/problems/longest-palindromic-substring/

s = input()
n = len(s)
p = 239
mod = 10**9 + 7

def count_hash(st):
    h = [ord(st[0])]
    for i in range(1, len(s)):
        h += [(h[i-1] + ord(st[i])*p**i)%mod]
    return h

def take_hash(h,l,r):
    return ((h[r-1]-h[l])*p**(n-l))%mod

h, rh = count_hash(s), count_hash(s[::-1])
bl = 0
bs = ""

def odd_palindrome(i):
    global bl
    global bs
    i //= 2
    l = 0; r = min(i, n-i-1)+1
    while r - l > 1:
        m = (l+r)//2
        lx = i-m
        rx = i+m+1
        if take_hash(h,lx,rx) == take_hash(rh, n-rx, n-lx):
            l = m
        else:
            r = m
    
    if 2*l + 1 > bl:
        bs = s[i-l:i+l+1]
        bl = 2*l + 1

def even_palindrome(i):
    global bl
    global bs
    l_bound = (i - 1)//2
    r_bound = (i + 1)//2
    l = 0; r = min(l_bound, n-r_bound-1)+1
    while r - l > 1:
        m = (l+r)//2
        lx = l_bound-m
        rx = r_bound+m+1

        if take_hash(h,lx,rx) == take_hash(rh, n-rx, n-lx):
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