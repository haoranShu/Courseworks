function [i,sum] = sum2N(N)
sum = 0; i = 0;
while sum < N
    i = i+1;
    sum = sum+i;
end