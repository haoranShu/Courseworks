n = input('Please enter an n such that is bigger than 1, n = ');
phi = 0;
for k = 1:n
    b = k;
    m = n;
    gcd = b;
    while mod(m,b) ~= 0
        gcd = mod(m,b);
        m = b;
        b = gcd;
    end
    phi = phi+gcd*exp(-2*pi*i*k/n);
end
phi