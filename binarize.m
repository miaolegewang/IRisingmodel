% RGB = imread('img.png'); %GOOGLE G
% [X,map] = rgb2ind(RGB,32); %GOOGLE G
% BW = im2bw(X, map, 0.8); %GOOGLE G

% RGB = imread('cherry.png'); %CHERRIES
%[X,map] = rgb2ind(RGB,32); %CHERRIES
%BW = im2bw(X, map, 0.5); %CHERRIES

% Gray = imread('lena_gray.bmp'); %LENA
% [X,map] = gray2ind(Gray,32); %LENA
% BW = im2bw(X, map, 0.5); %LENA

% Gray = imread('monkey.png'); %LENA
% [X,map] = gray2ind(Gray,32); %LENA
% BW = im2bw(X, map, 0.06); %LENA

%%%% ADD NOISE TO IMAGE %%%%
% imgSize=512
imgSize = 256
spins = zeros(imgSize);
for i = 1:imgSize
    for j = 1:imgSize
        spins(i,j) = 2*BW(i,j) - 1;
        if rand(1,1) < 0.2
            spins(i,j) = -spins(i,j);
        end
    end
end

%%%% CONVERT NOISY SPINS TO IMAGE AND FILE OUTPUT %%%%
newim = zeros(imgSize);
for i = 1:imgSize
    for j = 1:imgSize
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
A(2:imgSize+1,1:imgSize) = (A(2:imgSize+1,1:imgSize) + 1)/2;
num_missed = sum(sum(abs(BW - A(2:imgSize+1,1:imgSize))))/(imgSize^2)
flip_rate = sum(sum(abs(BW - newim)))/(imgSize^2)

f1 = figure(1);
subplot(2,2,1)
imshow(BW);
title('Noise Free Image')

subplot(2,2,2)
imshow(newim);
title('Noisy Image')

subplot(2,2,3)
imshow(A(2:imgSize+1,1:imgSize))
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
