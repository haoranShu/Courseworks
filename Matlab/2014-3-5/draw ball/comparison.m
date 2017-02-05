function C = comparison(n,N,K,t)
distri_bar(n,N,K,t);
hold on
p = zeros(n+1,1);
for i = 1:n+1
    if i <= K+1 & n-i+1 <= N-K
        p(i) = nchoosek(K,i-1)*nchoosek(N-K,n-i+1)/nchoosek(N,n);
    else
        p(i) = 0;
    end
end
plot(0:1:n,p,'--r','LineWidth',2)
