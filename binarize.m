RGB = imread('lena_gray.bmp');
[X,map] = gray2ind(RGB,32);
%[X,map] = rgb2ind(RGB,32);
BW = im2bw(X, map, 0.5);
% figure(1)
% imshow(BW);

%imshow(X,map), figure, imshow(BW);

spins = zeros(512);

for i = 1:512
    for j = 1:512
        spins(i,j) = 2*BW(i,j) - 1;
        spins(i,j) = spins(i,j) + 0.9216*randn(1,1);
    end
end

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

f1 = figure(1)
subplot(1,3,1)
%figure(1)
imshow(BW);
subplot(1,3,2)
%figure(2)
imshow(newim);

A = dlmread('IRisingmodel/restored.txt');
subplot(1,3,3)
%figure(3)
imshow(A(2:513,1:512))
set(f1, 'Position', [200 200 1200 500])

figure(4)
plot(1:10000,A(1,1:10000))

dlmwrite('IRisingmodel/spins.dat',spins);