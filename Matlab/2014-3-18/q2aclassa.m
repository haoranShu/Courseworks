clear all
s = input('Input argument for zeta(s,n), s = ');
n = input('Input n, n>1, n = ');
zeta = 0;
for m = 1:n
    zeta = zeta+1/m^s;
end
zeta