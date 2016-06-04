clear;
literal = textread('../txt/vector_literal.txt');
literal_x = zeros(size(literal, 1), 7060);
for i = 1:size(literal, 1)
    for j = 1:size(literal, 2)
        if literal(i, j) < 0
            break;
        end
        literal_x(i, literal(i, j) + 1) = literal_x(i, literal(i, j) + 1) + 1;
    end
end
save('../mat/literal.mat', 'literal_x');
