clear;
load('../mat/dataset.mat');
train_gather_x = gather_onehot_data(train_x);
test_gather_x = gather_onehot_data(test_x);
train_x = train_gather_x;
test_x = test_gather_x;
save('../mat/data_onehot.mat', 'train_x', 'train_y', 'test_x', 'test_y', '-v7.3');
