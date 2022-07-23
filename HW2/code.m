idx = load("network_A.mat");
bp1 = struct2cell(idx);
A = cell2mat(bp1);
tree = (zeros(100,100));
stack = [];
levelsort = [];
levelsort = [levelsort 1];
visit = [zeros(100)];
while( ~isempty(levelsort) )
    stack = levelsort;
    levelsort = [];
    while (~isempty(stack) )
        for i = 1: 100
            if( A(stack(1), i) == 1 && visit(i) == 0)
                visit(i) = 1;
                levelsort = [levelsort, i];
                tree(stack(1), i) = 1;
                tree(i, stack(1)) = 1;
            end
        end
        stack(1) = [];
    end
    levelsort = sort(levelsort);
end

save result.mat tree;