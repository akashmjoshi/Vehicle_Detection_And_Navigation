% Akash Mukesh Joshi
% USC ID :4703642421
% USC Email : akashjos@usc.edu
% Submission Date : 6th November 2016
% Problem 3.b and 3.c : Structured Edge

clc; clear; close all;
% Initalizing Variables
Size_Row = 321;
Size_Col = 481;
% Read Raw File
prompt = 'Input Image Filename as "Filename" : ';
str = input(prompt,'s');
% str = 'Elephant';
Imagedata = readRGB(strcat(str,'.raw'),Size_Col,Size_Row);
IGT1 = uint8(readGS(strcat(str,'_gt1.raw'),Size_Col,Size_Row));
IGT2 = uint8(readGS(strcat(str,'_gt2.raw'),Size_Col,Size_Row));
IGT3 = uint8(readGS(strcat(str,'_gt3.raw'),Size_Col,Size_Row));
IGT4 = uint8(readGS(strcat(str,'_gt4.raw'),Size_Col,Size_Row));
IGT5 = uint8(readGS(strcat(str,'_gt5.raw'),Size_Col,Size_Row));
if(strcmp(str,'Elephant') || strcmp(str,'Jaguar'))
    IGT6 = uint8(readGS(strcat(str,'_gt6.raw'),Size_Col,Size_Row));
end

% Selecting Different Thresholds for Different Images
if(strcmp(str,'Elephant'))
    bthres = 0.15; % Optimized
elseif(strcmp(str,'Zebra'))
    bthres = 0.13; % Optimized
else
    bthres = 0.10; % Optimized
end
%% set opts for training (see edgesTrain.m)
opts=edgesTrain();                % default options (good settings)
opts.modelDir='models/';          % model will be in models/forest
opts.modelFnm='modelBsds';        % model name
opts.nPos=5e5; opts.nNeg=5e5;     % decrease to speedup training
opts.useParfor=0;                 % parallelize if sufficient memory

%% train edge detector (~20m/8Gb per tree, proportional to nPos/nNeg)
tic, model=edgesTrain(opts); toc; % will load model if already trained

%% set detection parameters (can set after training)
% We can change model parameters here: NOTE
model.opts.multiscale=1;          % for top accuracy set multiscale=1
model.opts.sharpen=2;             % for top speed set sharpen=0
model.opts.nTreesEval=4;          % for top speed set nTreesEval=1
model.opts.nThreads=10;           % max number threads for evaluation
model.opts.nms=1;                 % set to true to enable nms

%% detect edge and visualize results
tic, EEdges=edgesDetect(Imagedata,model); toc
SEEdges = 1 - EEdges;
figure(); im(Imagedata); figure(); im(SEEdges);

% Forming Binary Image
BSEEdges = EEdges;
BSEEdges(EEdges >= bthres) = 0;
BSEEdges(EEdges < bthres) = 1;
figure(); im(BSEEdges);

%% Performance Evaluation
% Invert and Normalize Ground Truth Image
IGT=struct('groundTruth',[]);
if(strcmp(str,'Elephant') || strcmp(str,'Jaguar'))
    IGT.groundTruth = cell(1,6);
else
    IGT.groundTruth = cell(1,5);
end

for i = 1 : 5
    IGT.groundTruth{i}=struct('Boundaries',[]);
end

% Creating Ground Truth Boundaries
IGT.groundTruth{1,1}.Boundaries=(1-(IGT1/255));
IGT.groundTruth{1,2}.Boundaries=(1-(IGT2/255));
IGT.groundTruth{1,3}.Boundaries=(1-(IGT3/255));
IGT.groundTruth{1,4}.Boundaries=(1-(IGT4/255));
IGT.groundTruth{1,5}.Boundaries=(1-(IGT5/255));
if(strcmp(str,'Elephant') || strcmp(str,'Jaguar'))
    IGT.groundTruth{1,6}.Boundaries=(1-(IGT6/255));
end

%  Performing Performance Evaluation
disp('Starting Performance Evaluation...')
[thrs,cntR,sumR,cntP,sumP,V]=edgesEvalImg(1-BSEEdges,IGT);

% Calculating F-Measure using Precision and Recall
Recall = cntR./sumR;
Precision = cntP./sumP;

% Removing Zero or NAN Terms
Precision = Precision(Precision~=0);
Precision(isnan(Precision)) = [];
Recall = Recall(Recall~=0);
Recall(isnan(Recall)) = [];

% Calculating Mean Precision and Recall
Recall_mean = mean(Recall);
Precision_mean = mean(Precision);

% Calculating F-Measure
disp('Performance Evaluation Done');
F_Measure =(2 * Recall_mean * Precision_mean / (Recall_mean + Precision_mean))

% Performance Evaluation Table
