%% Read in original RGB image.
rgbImage = imread('91-2l5qfbL.jpg');
fig = figure;
imshow(rgbImage)
% Enlarge figure to full screen.
set(gcf, 'Units', 'Normalized', 'OuterPosition', [0, 0, 1, 1]);
% Save as .png
saveas(fig,'rgbImage.png');
%% Split into channels
[r,g,b] = imsplit(rgbImage);
% Display them all.
fig = figure;
montage({r,g,b},'Size',[1 3]);
% Enlarge figure to full screen.
set(gcf, 'Units', 'Normalized', 'OuterPosition', [0, 0, 1, 1]);
% Save as .png
saveas(fig,'channels.png');
%% Apply Salt & Pepper filter to each channel
rNoise = imnoise(r,'salt & pepper');
gNoise = imnoise(g,'salt & pepper');
bNoise = imnoise(b,'salt & pepper');
% Display them all.
fig = figure;
montage({rNoise,gNoise,bNoise},'Size',[1 3]);
% Enlarge figure to full screen.
set(gcf, 'Units', 'Normalized', 'OuterPosition', [0, 0, 1, 1]);
% Save as .png
saveas(fig,'channelsSP.png');
%% Blending channels
M = bitxor(bitxor(bNoise,gNoise),rNoise);
fig = figure;
imshow(M)
% Enlarge figure to full screen.
set(gcf, 'Units', 'Normalized', 'OuterPosition', [0, 0, 1, 1]);
% Save as .png
saveas(fig,'blended.png');
%% Make it into a sqaure matrix
% (NEED TO) Fix this logic so that it actually makes a square out of the
% existing matrix and does not throw away a large chunk
rows = size(M,1);
cols = size(M,2);
reshapeFactor = floor((cols - rows) / 2);

% Making a rows x (reshapeFactor + rows) matrix
for i = 1:rows
    row = zeros(1,rows+reshapeFactor);
    for j = 1:(rows+reshapeFactor)
        row(j) = M(i,j);
    end
    intensity_sq(i,:) = row;
end
% Putting the remaining rows x (cols - reshapeFactor) matrix in a 1D array
temp = zeros(1,rows*reshapeFactor);
k = 1;
for j = (cols-reshapeFactor):cols
    for i = 1:rows
        temp(k) = M(i,j);
        k = k+1;
    end
end
% Adding the rest of the matrix to the bottom
k = 1;
while (k < length(temp))
    row = zeros(1,rows+reshapeFactor);
    for j=1:rows+reshapeFactor
        row(j) = temp(k);
        k = k + 1;
        if k > length(temp)
            break;
        end
    end
    if k < length(temp)
        intensity_sq(i,:) = row;
        i = i+1;
    end
end
% chopping off excess columns
intensity_sq = intensity_sq(:,1:size(intensity_sq,1));
% interweaving the noise back into the image
excessRows =  size(intensity_sq,1) - rows;
spacing = floor(rows/excessRows);
temp = intensity_sq(rows+1:size(intensity_sq,1),:);
intensity_sq = intensity_sq(1:rows,:);
k = 1;
for i=spacing:spacing:rows+excessRows
    intensity_sq = [intensity_sq(1:i-1,:);temp(k,:);intensity_sq(i:end,:)];
    if k < size(temp,1)
        k = k+1;
    else
        break;
    end
end
intensity_sq = uint8(intensity_sq);
fig = figure;
imshow(uint8(intensity_sq))
% Enlarge figure to full screen.
set(gcf, 'Units', 'Normalized', 'OuterPosition', [0, 0, 1, 1]);
% Save as .png
saveas(fig,'square.png');