function u = proj(x,y)
u = ((x*y')/norm(y)^2)*y;
