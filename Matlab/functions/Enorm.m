function v = Enorm(x)
%Enorm computes the Euclidean norm of x
n = length(x);
sum = 0;
for i = 1:n
    sum = sum+x(i)^2;
end
v = sqrt(sum);