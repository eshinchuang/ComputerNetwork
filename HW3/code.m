idx = load("network_A.mat");
bp1 = struct2cell(idx);
A = cell2mat(bp1);
tree = (zeros(100,100));
for i =1: 100
    stack = [];
    visit = [zeros(100)];
    visit(i) == 1;
    for j = 1 : 100
        if(i ~= j && A(i,j) > 0 && visit(j) == 0)
            stack = [stack, j];
            visit(j) = 1;
            tree(i,j) = A(i,j);
            tree(j,i) = A(i,j);
        end
    end
    while(~isempty(stack))
    %   disp(stack(1));
        for j = 1 : 100
            if(j ~= i && A(stack(1),j) > 0 && visit(j) == 0)
                if(A(i,j) == 0)
                    A(i,j) = A(i,stack(1)) + A(stack(1),j);
                    A(j,i) = A(i,j);
                    tree(i,j) = A(i,j);
                    tree(j,i) = A(i,j);
                    stack = [stack,j];
                elseif(A(i,j) > A(i,stack(1)) + A(stack(1),j))
                     A(i,j) = A(i,stack(1)) + A(stack(1),j);
                     A(j,i) = A(i,j);
                     tree(i,j) = A(i,j);
                     tree(j,i) = A(i,j);
                     stack = [stack,j];
                end
            end
        end
        stack(1) = [];
    end
end
save result.mat tree;