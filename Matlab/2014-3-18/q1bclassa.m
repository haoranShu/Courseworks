k = input('The array k = ');
n = length(k);
for i = 1:n-1
    if k(i) < k(i+1)
        c = k(i);
        k(i) = k(i+1);
        k(i+1) = c;
    end
        gcd = k(i+1);
    while mod(k(i),k(i+1)) ~= 0
        gcd = mod(k(i),k(i+1));
        k(i) = k(i+1);
        k(i+1) = gcd;
    end
end
disp(['The greatest common divisor of a and b is ',num2str(gcd),'.']);
