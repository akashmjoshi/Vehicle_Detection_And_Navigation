function Original_image = readraw(filename,Size_Col,Size_Row)
%readraw - read RAW format grey scale image of square size into matrix G
% Usage:	G = readraw(filename)

% Initialize counter variables that assist in reading the image
Blue_count= 1;
Red_count= 1;
Green_count= 1;

% Declare arrays for reading raw files to individual 1D color arrays
Blue= uint8(zeros(1,Size_Row*Size_Col));
Red= uint8(zeros(1,Size_Row*Size_Col));
Green= uint8(zeros(1,Size_Row*Size_Col));

disp(['	Retrieving Image ' filename ' ...']);

% Get file ID for file
fid=fopen(filename,'rb');

% Check if file exists
if (fid == -1)
    error('can not open input image file press CTRL-C to exit \n');
    pause
end

% Get all the pixels from the image
pixel = fread(fid, inf, 'uint8=>uint8');
% Close file
fclose(fid);

[Y,X,K] = size(pixel);

% Segregate Red Green and Blue parts of the image
for m= 1:X*Y*K
    if mod(m,3)== 0
        Blue(1,Blue_count)= pixel(m);
        Blue_count = Blue_count+1;
    elseif mod(m,3)== 1
        Red(1,Red_count)= pixel(m);
        Red_count = Red_count+1;
    elseif mod(m,3)== 2
        Green(1,Green_count)= pixel(m);
        Green_count = Green_count+1;
    end
end

% Reshape the 1D color arrays into 2D image channels
Red_plane = uint8(zeros(Size_Row,Size_Col));
Green_plane = uint8(zeros(Size_Row,Size_Col));
Blue_plane = uint8(zeros(Size_Row,Size_Col));

count = 1;
m = 1;

for i = 1:Size_Col*Size_Row
    Red_plane(m,count) = Red(1,i);
    
    count = count+1;
    
    if count == Size_Col+1
        count = 1;
        m = m+1;
    end
end

count = 1;
m = 1;

for i = 1:Size_Col*Size_Row
    Green_plane(m,count) = Green(1,i);
    
    count = count+1;
    
    if count == Size_Col+1
        count = 1;
        m = m+1;
    end
end


count = 1;
m = 1;
for i = 1:Size_Col*Size_Row
    Blue_plane(m,count) = Blue(1,i);
    
    count = count+1;
    
    if count == Size_Col+1
        count = 1;
        m = m+1;
    end
end

% Construct the Original image by Concatenating the 3 2D color channels to
% one array and show it
Original_image = uint8(zeros(Size_Row,Size_Col,3));

for m = 1:Size_Row
    for n = 1:Size_Col
        Original_image(m,n,1) = Red_plane(m,n);
        Original_image(m,n,2) = Green_plane(m,n);
        Original_image(m,n,3) = Blue_plane(m,n);
    end
end

% figure;
% imshow(Original_image);
end %function
