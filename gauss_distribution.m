close all;
clear all;

sigma = 8;
N = 50;
Nx = N;
Ny = N;
dep = 0.5;
for m=1:Nx+1
    for n=1:Ny+1
        x = -(Nx*dep)/2+(m-1)*dep;
        y = -(Ny*dep)/2+(n-1)*dep;
        Z(m,n) = exp(-((x/sigma)^2+(y/sigma)^2));
    end
end
mesh(Z);
    