clear;
load('../mat/punctuation.mat');
N = size(punctuation_x, 1);
tf = 1./(sum(punctuation_x, 2)+eps);
idf = log2(N./(sum(punctuation_x > 0, 1)+eps));
punctuation_tfidf_x = punctuation_x .* (tf * idf);
save('../mat/punctuation_tfidf.mat', 'punctuation_tfidf_x');
