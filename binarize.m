RGB = imread('img.png'); %GOOGLE G
[X,map] = rgb2ind(RGB,32); %GOOGLE G
BW = im2bw(X, map, 0.8); %GOOGLE G

% RGB = imread('cherry.png'); %CHERRIES
%[X,map] = rgb2ind(RGB,32); %CHERRIES
%BW = im2bw(X, map, 0.5); %CHERRIES

% Gray = imread('lena_gray.bmp'); %LENA
%[X,map] = gray2ind(Gray,32); %LENA
%BW = im2bw(X, map, 0.5); %LENA

%%%% ADD NOISE TO IMAGE %%%%
spins = zeros(512);
for i = 1:512
    for j = 1:512
        spins(i,j) = 2*BW(i,j) - 1;
        spins(i,j) = spins(i,j) + 1.41*randn(1,1);
    end
end

%%%% CONVERT NOISY SPINS TO IMAGE AND FILE OUTPUT %%%%
newim = zeros(512);
for i = 1:512
    for j = 1:512
        if spins(i,j) >= 0 
            spins(i,j) = 1;
            newim(i,j) = 1;
        else
            newim(i,j) = 0;
            spins(i,j) = -1;
        end
    end
end
dlmwrite('spins.dat',spins);

A = dlmread('restored.txt');
[col, row] = size(A);
A(2:513,1:512) = (A(2:513,1:512) + 1)/2;
num_missed = sum(sum(abs(BW - A(2:513,1:512))))

f1 = figure(1);
subplot(2,2,1)
imshow(BW);
title('Noise Free Image')

subplot(2,2,2)
imshow(newim);
title('Noisy Image')

subplot(2,2,3)
imshow(A(2:513,1:512))
title('Ising Model Restoration')

subplot(2,2,4)
imshow(medfilt2(newim));
title('Median Filter Restoration')

set(f1, 'Position', [200 200 1200 500])

figure(4)
plot(1:row,A(1,1:row))
title('MC Acceptance Rate vs. Iteration')
xlabel('Iteration Number')
ylabel('Monte Carlo Acceptance Rate')