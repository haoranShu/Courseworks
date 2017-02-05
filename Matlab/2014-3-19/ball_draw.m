function X = ball_draw(n,N,K)
balls = [ones(K,1);zeros(N-K,1)];
draw = rand(N,1);
[~, order] = sort(draw);
result = balls(order(1:n));
X = sum(result);
end
