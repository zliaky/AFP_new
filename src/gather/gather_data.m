function gather = gather_data(dataset)
    load('../mat/emotion.mat');
    load('../mat/literal.mat');
    load('../mat/literal_tfidf.mat');
    load('../mat/punctuation.mat');
    load('../mat/punctuation_tfidf.mat');
    load('../mat/statistic.mat');
    N = size(dataset, 1);
    gender = dataset(:, 2)-1;
    age = 2016-dataset(:, 3);
    surf_scene = dataset(:, 4);
    marriage_status = dataset(:, 5);
    education = dataset(:, 6);
    profession = dataset(:, 7);
    category_id = dataset(:, 10)+1;
    series_id = dataset(:, 11)+1;
    advertiser_id = dataset(:, 12)+1;
    product_type = dataset(:, 13)+1;
    product_id = dataset(:, 14)+1;
    imp_time = dataset(:, 15);
    pos_id = dataset(:, 16)+1;
    information = [gender, age, surf_scene, marriage_status, education, ...
        profession, category_id, series_id, advertiser_id, ...
        product_type, product_id, imp_time, pos_id];
    literal = dataset(:, 8)+1;
%     literal = literal_label(dataset(:, 8)+1, :);
%     literal = (literal(:, 1)+1)./(literal(:,1)+literal(:,2)+2);
%     literal = literal_x(dataset(:, 8)+1, :);
%     literal_tfidf = literal_tfidf_x(dataset(:, 8)+1, :);
%     punctuation = punctuation_x(dataset(:, 8)+1, :);
%     punctuation_tfidf = punctuation_tfidf_x(dataset(:, 8)+1, :);
    image = dataset(:, 9)+1;
%     emotion = emotion_x(dataset(:, 9)+1, :);
%     gather = [information, literal, literal_tfidf, ...
%         punctuation, punctuation_tfidf, emotion];
%     gather = [information, literal, emotion];
    gather = [information, literal, image];
end
