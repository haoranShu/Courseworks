function putprice = Barrier(S0, Strike, T, sigma, r, M, N, B)

S = zeros(N,M+1);
V = zeros(N,1);
deltat = T/M;
d = sqrt(deltat);
for i = 1:N
    S(i,1) = S0;
    for j = 2:M+1
        normal = normrnd(0,1);
        S(i,j) = S(i,j-1)*exp((r-0.5*sigma^2)*deltat + sigma*normal*d);
    end
    if min(S(i,:)) <= B
        V(i) = 0;
    else
        V(i) = max(Strike - S(i,M+1),0);
    end
end

putprice = exp(-r*T)*mean(V);

end