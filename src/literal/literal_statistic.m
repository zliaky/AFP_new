clear;
load('../mat/dataset.mat');
load('../mat/literal.mat');
load('../mat/emotion.mat');
l = zeros(size(literal_x, 1), 2);
for i = 1:size(train_x, 1)
    l(train_x(i, 8)+1, train_y(i, 1)+1) = l(train_x(i, 8)+1, train_y(i, 1)+1)+1;
end
s = 0;
for i = 1:size(literal_x, 1)
    if l(i, 1) > l(i, 2)
        s = s + l(i, 1);
    else
        s = s + l(i, 2);
    end
end
accuracy = s / sum(sum(l));
fprintf('Literal accuracy = %f.\n', accuracy);
literal_label = l;
l = zeros(size(emotion_x, 1), 2);
for i = 1:size(train_x, 1)
    l(train_x(i, 9)+1, train_y(i, 1)+1) = l(train_x(i, 9)+1, train_y(i, 1)+1)+1;
end
s = 0;
for i = 1:size(emotion_x, 1)
    if l(i, 1) > l(i, 2)
        s = s + l(i, 1);
    else
        s = s + l(i, 2);
    end
end
accuracy = s / sum(sum(l));
fprintf('Image accuracy = %f.\n', accuracy);
image_label = l;
save('../mat/statistic.mat', 'literal_label', 'image_label');
