I = imread('Lena.bmp');
%converting I to 1D array
temp = I(:);
temp = temp';

% finding arrays of p&q's
% current implementation is to alternate between storing p&q
p = {};
q = {};
k = 1;
i = 1;
flag  = 0;
while(i<size(temp,2)+1) 
    % checking if p{k} needs to be initilized or not
    if flag==1
       flag = 0;
    elseif flag==0
        p{k} = num2str(temp(i));
        i = i+1;
    end
    % storing a p bitstring
    while (size(p{k},2)<512)
        % preventing indexing outside of temp
        if i>size(temp,2)
            break;
        end
        % converting current pixel to string
        pixel = num2str(temp(i));
        % if the current pixel will make p{k} longer than 512 take the
        % overage and put it into q{k}
        if (size(p{k},2)+size(pixel,2))>512
            ovr = size(p{k},2)+size(pixel,2)-512;
            p{k} = [p{k} pixel(1:size(pixel,2)-ovr)];
            q{k} = pixel(size(pixel,2)-ovr:size(pixel,2));
            flag = 1;
            i = i+1;
            break;
        else
            p{k} = [p{k} pixel];
            i = i+1;
        end
    end
    
    % preventing indexing outside of temp
    if i>size(temp,2)
        break;
    end

    % checking if q{k} needs to be initilized or not
    if flag==1
       flag = 0;
    elseif flag==0
        q{k} = num2str(temp(i));
        i = i+1;
    end
    % storing a q bitstring
    while (size(q{k},2)<512)
        % preventing indexing outside of temp
        if i>size(temp,2)
            break;
        end
        % converting current pixel to string
        pixel = num2str(temp(i));
        % if the current pixel will make q{k} longer than 512 take the
        % overage and put it into the next p{k}
        if (size(q{k},2)+size(pixel,2))>512
            ovr = size(q{k},2)+size(pixel,2)-512;
            q{k} = [q{k} pixel(1:size(pixel,2)-ovr)];
            p{k+1} = pixel(size(pixel,2)-ovr:size(pixel,2));
            flag = 1;
            i = i+1;
            break;
        else
            q{k} = [q{k} pixel];
            i = i+1;
        end
    end
    
    k = k+1;
end

% converting back to double
pnew = str2double(p);
qnew = str2double(q);