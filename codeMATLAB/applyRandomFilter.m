function [allRandOutput, lithOutput, psychOutput] = applyRandomFilter()
figure();

img = imread('Lena.bmp');
[rows cols channels] = size(img);
subplot(1, 4, 1); imshow(img); title('Original Image');
dim = 5;
numLimit = 10;

bias = 5;

% All random numbers
allRandomFilter = randi(numLimit, dim, dim) - bias;
allRandOutput = (imfilter(img, allRandomFilter));
subplot(1, 4, 2); imshow(allRandOutput); title('All Random Output');

% Random numbers in lithograph template
lithRandomFilter = ones(dim, dim) * -1;
randFilter = randi(numLimit, dim - 2, dim - 2) - bias;
lithRandomFilter(2:dim - 1, 2:dim - 1) = randFilter;
lithOutput = imfilter(img, lithRandomFilter);
subplot(1, 4, 3); imshow(lithOutput); title('Random Lith Output');

% Random filters in psychedelic filter template
psychRandomFilter = zeros(dim, dim);
psychRandomFilter(:, 2) = ones(dim, 1) * -1;
psychRandomFilter(:, dim) = ones(dim, 1);

% set top and bottom rows of filter
for i = 1:dim
    psychRandomFilter(1, i) = (i - 1) * -1;
    psychRandomFilter(dim, i) = (i - 1) * -1;
end
% Set random numbers in the middle of filter matrix
width = (dim - 1) - 2;
height = dim - 2;

psychRandomFilter(2:2 + height - 1, 3:3 + width -1) = randi(numLimit, height, width) - bias;

psychOutput = imfilter(img, psychRandomFilter);
subplot(1, 4, 4); imshow(psychOutput); title('Random Psych Output');

% Add salt and pepper noise
%  FIGURE OUT REPLACEMENT FOR randi() calls
saltPepper = img;
for i = 1:2:rows
    val = randi(255);
    for j = 1:2:cols
        
        %rowIndex = randi(rows);
        %colIndex = randi(cols);
        saltPepper(i, j) = val;

    end
end
figure(); imshow(saltPepper); title('Salt and pepper');

end