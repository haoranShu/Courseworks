function N = bacteria(n,a,b,c);
disp(['In time = 0, we have ',num2str(n),' bacteria in the dish.']);
disp(['The probability of dead is ',num2str(a),'.']);
disp(['The probability of remain is ',num2str(b),'.']);
disp(['And the probability of split is ',num2str(c),'.']);
N = rand(n,1);
N = (N>a&N<(a+b))+(N>=(a+b))*2;
N = sum(N);
end
