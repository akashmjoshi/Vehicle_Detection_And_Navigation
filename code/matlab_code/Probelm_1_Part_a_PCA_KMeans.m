% Akash Mukesh Joshi
% USC ID :4703642421
% USC Email : akashjos@usc.edu
% Submission Date : 6th November 2016
% Problem 1.a : PCA and KMeans Algorithm

clc; clear; close all;
fv_norm = csvread('prb1prta.csv');

% Initializing First Centroid Clustering Points
centroid = [ 1.50  -0.30  0.20;
            -10.0   0.00  0.00;
             2.00  -0.20 -0.40;
             6.00   0.40  0.10];

%% Running PCA for Dimensinality Reduction 25D to 3D
 [~,score,~,~,explainedVar] = pca(fv_norm(:,1:12)');
 figure;
 bar(explainedVar)
 for i = 1 : 1 : 12
     for j = 1 : 1 : 3
         fv_pca(i,j) = score(i,j);
     end
 end

%% Running KMeans on 3D Feature Vector
 [clusters(:,1), ~] = kmeans(fv_pca,4,'MaxIter',100,'Start',centroid);
 figure;
 scatter3(fv_pca(:,1),fv_pca(:,2),fv_pca(:,3),'r*');
 figure;
 gscatter(fv_pca(:,1),fv_pca(:,2),clusters)

%% Running KMeans on 25D Feature Vector
[clusters(:,2), ~] = kmeans(fv_norm(:,1:12)',5,'MaxIter',100);