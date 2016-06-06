clear;
load('../../mat/data.mat');

T = 101;
sample_rate = 0.5;
vote = zeros(size(test_y));
for i = 1:T
    N = length(train_y);
    S = ceil(N * sample_rate);
    sample = randperm(N);
    s_train_x = train_x(sample(1:S), :);
    s_train_y = train_y(sample(1:S), :);
    factor = TreeBagger(501, s_train_x, s_train_y);
    [~, scores] = predict(factor, test_x);
    pred_y = scores(:, 1) < scores(:, 2);
    acc = sum(pred_y == test_y) / length(test_y);
    now = clock;
    fprintf('[%02d:%02d:%02.0f] ', now(4), now(5), now(6));
    fprintf('Round %d, accuracy = %f.\n', i, acc);
    vote = vote + scores(:, 2);
end
vote(vote < T/2) = 0;
vote(vote > T/2) = 1;
accuracy = sum(vote == test_y) / length(test_y);
fprintf('Final Accuracy = %f.\n', accuracy);
result = vote;
save('result.mat', 'result');
