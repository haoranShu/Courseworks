%Now we play a card game
%1 to 13
%The posability of winning after changing and not changing
function f = change_or_not(t)
cards = [ones(4,1);2*ones(4,1);3*ones(4,1);4*ones(4,1);5*ones(4,1);
6*ones(4,1);7*ones(4,1);8*ones(4,1);9*ones(4,1);10*ones(4,1);11*ones(4,1);
12*ones(4,1);13*ones(4,1)];
not = zeros(1,13);
change = zeros(1,13);
total = zeros(1,13);
for k = 1:t
    x = rand(52,1);
    [a,b] = sort(x);
    player1 = cards(b(1));
    player2 = cards(b(2));
    y = cards(b(3:52));
    for i = 1:13
        if player1 == i
            total(i)=total(i)+1;
            if player2 > player1
            not(i) = not(i)+1;
        else
            not(i) = not(i);
        end
            z = rand(50,1);
            [m,l] = sort(z);
            player2 = y(l(1));
            if player2 > player1
                change(i) = change(i)+1;
            else
                change(i) = change(i);
            end
        else
            change(i) = change(i);
            not(i) = not(i);
        end
    end
end
f = [change./total;not./total;(change-not)./total];
            
        

