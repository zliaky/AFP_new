function gather = gather_onehot_data(dataset)
    load('../mat/emotion.mat');
    load('../mat/literal.mat');
    load('../mat/literal_tfidf.mat');
    load('../mat/punctuation.mat');
    load('../mat/punctuation_tfidf.mat');
    N = size(dataset, 1);
    gender = dataset(:, 2)-1;
    age = 2016-dataset(:, 3);
    surf_scene = onehot(dataset(:, 4), 5);
    marriage_status = onehot(dataset(:, 5), 10);
    education = onehot(dataset(:, 6), 6);
    profession = onehot(dataset(:, 7), 12);
    category_id = onehot(dataset(:, 10)+1, 149);
    series_id = onehot(dataset(:, 11)+1, 3633);
    advertiser_id = onehot(dataset(:, 12)+1, 992);
    product_type = onehot(dataset(:, 13)+1, 7);
    product_id = onehot(dataset(:, 14)+1, 497);
    imp_time = dataset(:, 15);
    pos_id = onehot(dataset(:, 16)+1, 4);
    information = [gender, age, surf_scene, marriage_status, education, ...
        profession, category_id, series_id, advertiser_id, ...
        product_type, product_id, imp_time, pos_id];
    literal = literal_x(dataset(:, 8)+1, :);
    literal_tfidf = literal_tfidf_x(dataset(:, 8)+1, :);
    punctuation = punctuation_x(dataset(:, 8)+1, :);
    punctuation_tfidf = punctuation_tfidf_x(dataset(:, 8)+1, :);
    emotion = emotion_x(dataset(:, 9)+1, :);
    gather = [information, literal, literal_tfidf, ...
        punctuation, punctuation_tfidf, emotion];
end
