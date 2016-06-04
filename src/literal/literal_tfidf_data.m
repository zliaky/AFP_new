clear;
load('../mat/literal.mat');
N = size(literal_x, 1);
tf = 1./(sum(literal_x, 2)+eps);
idf = log2(N./(sum(literal_x > 0, 1)+eps));
literal_tfidf_x = literal_x .* (tf * idf);
save('../mat/literal_tfidf.mat', 'literal_tfidf_x');
