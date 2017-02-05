function D = distri_bar(n,N,K,t)
disp(['In a total number of ',num2str(t),' experiments, we obtained: '])
x = zeros(n+1,1);
for i = 1:n+1
    for k = 1:t
        if draw_ball(n,N,K) == i-1;
            x(i) = x(i)+1;
        else
            x(i) = x(i);
        end
    end
end
bar(0:1:n,x/t)

    