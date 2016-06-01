%% Binarize and add noise section

% parameters to change
imageDir = '';
transferRatio = 0.5;

dir = './images/'
datafile = 'binary.dat';
IM = imread(strcat(dir, imageDir));
if size(IM, 3) == 3
  [X, map] = rgb2ind(IM, 32);
else
  [X, map] = gray2ind(IM, 32);
end
BW = im2bw(X, map, transferRatio);

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

% %%%% ADD NOISE TO IMAGE %%%%
% imgSize=512
[height, length] = size(BW);
f = fopen(datafile, 'w');
fprintf(f, '%d,%d\n', [height, length]);
fclose(f);
spins = zeros(height, length);
for i = 1:height
    for j = 1:length
        spins(i,j) = 2*BW(i,j) - 1;
        if rand(1,1) < 0.2
            spins(i,j) = -spins(i,j);
        end
    end
end

% %%%% CONVERT NOISY SPINS TO IMAGE AND FILE OUTPUT %%%%
newim = zeros(height, length);
for i = 1:height
    for j = 1:length
        if spins(i,j) >= 0
            spins(i,j) = 1;
            newim(i,j) = 1;
        else
            newim(i,j) = 0;
            spins(i,j) = -1;
        end
    end
end
dlmwrite(datafile, spins, '-append');


%% Restore image from data
restoreIMPath = 'restored.txt';
A = dlmread(restoreIMPath);
[col, row] = size(A);
A(2:height+1,1:length) = (A(2:height+1,1:length) + 1)/2;
num_missed = sum(sum(abs(BW - A(2:height+1,1:length))))/(height * length);
flip_rate = sum(sum(abs(BW - newim)))/(height * length);

f1 = figure(1);
subplot(2,2,1)
imshow(BW);
title('Noise Free Image')

subplot(2,2,2)
imshow(newim);
title('Noisy Image')

subplot(2,2,3)
imshow(A(2:height+1,1:length))
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
