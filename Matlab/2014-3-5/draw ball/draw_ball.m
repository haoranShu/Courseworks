function X = draw_ball(n,N,K)
r = [ones(K,1);zeros(N-K,1)];
x = rand(N,1);
[a,b] = sort (x);
X = sum(r(b(1:n)));

