a = input('a = ');
b = input('b = ');
if a < b
    c = a;
    a = b;
    b = c;
end
gcd = b;
while mod(a,b) ~= 0
    gcd = mod(a,b);
    a = b;
    b = gcd;
end
disp(['The greatest common divisor of a and b is ',num2str(gcd),'.']);
