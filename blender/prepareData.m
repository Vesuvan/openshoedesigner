
y = loadxml('FootBones.x3d');

a = cell(0,5);

for n = 1:size(y,1)
	if y{n,3} ~= 3 || ~strcmp(y{n,1},'Transform')
		continue;
	end
	tokens = regexp(y{n,2}.DEF,'^"Icosphere([12])_([A-Za-z0-9]+)','tokens','once');
	if isempty(tokens)
		continue;
	end
	N = str2num(tokens{1});1
	m =	find(strcmp(a(:,1),tokens{2}));
	if isempty(m)
		a(end+1,:) = [tokens(2),{NaN},{0},{NaN},{0}];
	end
	m =	find(strcmp(a(:,1),tokens{2}));
	
	
	pos = sscanf(y{n,2}.translation,'"%f %f %f"')/100;
	radius = sscanf(y{n,2}.scale,'"%f %f %f"')/100;
	radius = mean(radius);
	
	if isnan(a{m,2}) && isnan(a{m,4})
		a(m,2:5) = [{pos},{0},{pos},{0}];	
	end
	
	a(m,(N*2):(N*2+1)) = [{pos},{radius}];
end

for n = 1:size(a,1)
	fprintf('%s->p1.Set(%f, %f, %f);\n',a{n,1},a{n,2}(1),a{n,2}(2),a{n,2}(3));
	fprintf('%s->r1 = %f;\n',a{n,1},a{n,3});
	fprintf('%s->p2.Set(%f, %f, %f);\n',a{n,1},a{n,4}(1),a{n,4}(2),a{n,4}(3));
	fprintf('%s->r2 = %f;\n',a{n,1},a{n,5});
end

