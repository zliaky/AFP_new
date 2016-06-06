function vector = onehot(index, n)
    vector = zeros(size(index, 1), n);
    for i = 1:size(index, 1)
        vector(i, index(i, 1)) = 1;
    end
end
