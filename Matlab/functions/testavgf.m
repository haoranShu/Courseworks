function avg=testavgf(n)
% testavgf computes the
% average of n numbers
a = rand(n,1);   
s = 0;
for i = 1:n 
     s = s+a(i); 
end 
avg=s/n;
