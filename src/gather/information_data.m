clear;
train = csvread('../txt/train.txt');
test = csvread('../txt/test.txt');
train_x = train(:, 1:16);
train_y = train(:, 17);
test_x = test;
test_y = zeros(size(test, 1), 1);
save('../mat/dataset.mat', 'train_x', 'train_y', 'test_x', 'test_y');
