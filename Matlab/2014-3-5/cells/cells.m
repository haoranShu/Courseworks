n = input('Plese input the original number of cells in the dish: ');
a = input('The possilibity that a cell dies after one time unit is: ');
b = input('The possilibity that a cell remains after one time unit is: ');
c = input('The possilibity that a cell duplicates after one time unit is: ');
t = input('How many time units we are observing: ');
num(n,a,b,c,t)
plot(1:t,ans)