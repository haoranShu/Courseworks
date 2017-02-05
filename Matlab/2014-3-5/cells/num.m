function N = num(n,a,b,c,t)
N = zeros(t,1);
if a+b+c ~= 1
    disp(['Error!ÍæÎÒÄØ£¿£¡']);
else
    if 0<=a & a<=1 & 0<=b & b<=1 & 0<=c & c<=1
        for k = 1:t
            x = rand(n,1);
            N(k) = n-sum(x<=a)+sum(x>a+b);
            disp(['After ', num2str(k),' hours, we have ',num2str(N(k)),' cells.']);
            n = N(k);
        end
    else
        disp(['Error!ÍæÎÒÄØ£¿£¡']);
    end
end
        