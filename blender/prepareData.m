%PREPAREDATA  Converts the footbone data into a C-code.
%
%   Reads the FootBones.x3d file and parses it into some C-code for the 
%   LastGenerator software.
%   

% Copyright (C) 2015 Tobias Schäfer

filename = 'FootBones.x3d';
footLength = 28.67e-2; % cm
footWidth = 9.56e-2; % cm

fhd = fopen(filename,'r');
if fhd <=0
	error('Konnte Datei nicht oeffnen.');
end
text = char(fread(fhd,Inf,'char*1')');
fclose(fhd);

tE = regexp(text,'<Transform DEF="Empty_([a-zA-Z0-9]+)_TRANSFORM"[\s\r\n]*translation="([0-9\- \.]+)"[\s\r\n]*scale="([0-9\- \.]+)"','tokens');
tI = regexp(text,'<Transform DEF="Icosphere([12])_([a-zA-Z0-9]+)_TRANSFORM"[\s\r\n]*translation="([0-9\- \.]+)"[\s\r\n]*scale="([0-9\- \.]+)"','tokens');

%N = cell(0,1);
%for n = 1:length(tI)
%	N(end+1,1) = tI{n}(2);
%end
%N = unique(N);
%for n = 1:size(bone,1)
%	fprintf(1,'    0, ''%s'', [0,0,0], 0, [0,0,0], 0, [0,0,0];...\n',N{n});
%	fprintf(1,'    %u, ''%s'', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...\n',bone{n,1},bone{n,2});
%end

% Template for the bone information (and linkage (1st column))
% Link, Name, P1, r1, P2, r2, L
bone = {...
    NaN, 'Tibia', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    1, 'Fibula', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    1, 'Talus', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    3, 'Talus2', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    3, 'Calcaneus', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    3, 'Cuboideum', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    3, 'Naviculare', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    7, 'Cuneiforme1', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    7, 'Cuneiforme2', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    7, 'Cuneiforme3', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    6, 'Metatarsalis1', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    6, 'Metatarsalis2', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    10, 'Metatarsalis3', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    9, 'Metatarsalis4', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    8, 'Metatarsalis5', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    11, 'PhalanxI1', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    12, 'PhalanxI2', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    13, 'PhalanxI3', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    14, 'PhalanxI4', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    15, 'PhalanxI5', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    16, 'PhalanxII1', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    17, 'PhalanxII2', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    18, 'PhalanxII3', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    19, 'PhalanxII4', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    20, 'PhalanxII5', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    21, 'PhalanxIII1', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    22, 'PhalanxIII2', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    23, 'PhalanxIII3', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    24, 'PhalanxIII4', [NaN,NaN,NaN], NaN, [NaN,NaN,NaN], NaN, [NaN,NaN,NaN];...
    };

assert(all((cell2mat(bone(2:end,1))-(2:size(bone,1))')<0),'Linkage of bones contains rings. Please check.');

bonestructure = struct();
offset = [0,0,0];

% Add data to bones
for n = 1:length(tI)
  
  % Name of bone
  name = tI{n}{2};
  
	m =	find(strcmp(bone(:,2),name));
	assert(~isempty(m), 'New bone in x3d file introduced. Adapt bone list.');
	assert(length(m) < 2, 'Two bones with same name in bone list.');
	ref = bone{m,1};
  if isnan(ref)
    ref = [];
  else
    ref = bone{ref,2};
  end
	N = str2num(tI{n}{1});
	pos = sscanf(tI{n}{3},'%f %f %f');
	pos = [-pos(1),pos(3),pos(2)];
	radius = sscanf(tI{n}{4},'%f %f %f');
	radius = mean(abs(radius));
	bone(m,(1:2)+2*N) = {pos/100,radius/100};
%  bonestructure.(name).name = name;
  bonestructure.(name).parent = ref;
  bonestructure.(name).init.(sprintf('r%u',N)) = radius;
  bonestructure.(name).init.(sprintf('p%u',N)) = pos;
  if strcmpi(name, 'tibia')
    offset = pos;
  end
end
for n = 1:length(tE)
  % Name of bone
	m =	find(strcmp(bone(:,2),tE{n}{1}));
	assert(~isempty(m), 'New bone in x3d file introduced. Adapt bone list.');
	assert(length(m) < 2, 'Two bones with same name in bone list.');
	pos = sscanf(tE{n}{2},'%f %f %f');
	pos = [-pos(1),pos(3),pos(2)];
	bone(m,7) = {pos/100};
end


% Fill in 2nd bone point. (Copy missing data from first.)
for n = 1:size(bone,1)
	if isnan(bone{n,5}(1))
		bone(n,5) = bone(n,3);
	end
	if isnan(bone{n,6})
		bone(n,6) = bone(n,4);
	end
end

% Set missing rotational joints
for n = 1:size(bone,1)
	if ~isnan(bone{n,7}(1))
		continue;
	end
	m = bone{n,1};
	if isnan(m)
		bone(n,7) = bone(n,3); % For bone without link link to P1.
	else
		bone(n,7) = bone(m,5); % Link to P2 of parent bone.
	end
end


fn = fieldnames(bonestructure);
minx = inf;
maxx = -inf;
for n = 1:length(fn)
  if isfield(bonestructure.(fn{n}).init, 'p1')
    minx = min(minx, bonestructure.(fn{n}).init.p1(1));
    maxx = max(maxx, bonestructure.(fn{n}).init.p1(1));
  end
  if isfield(bonestructure.(fn{n}).init,'p2')
    minx = min(minx, bonestructure.(fn{n}).init.p2(1));
    maxx = max(maxx, bonestructure.(fn{n}).init.p2(1));
  end
end
L = maxx - minx;

for n = 1:length(fn)
  bonestructure.(fn{n}).init.p1 = (bonestructure.(fn{n}).init.p1 - offset) ./ L;
  bonestructure.(fn{n}).init.r1 = bonestructure.(fn{n}).init.r1 / L;
  if isfield(bonestructure.(fn{n}).init, 'p2')
    bonestructure.(fn{n}).init.p2 = (bonestructure.(fn{n}).init.p2 - offset) ./ L;
    bonestructure.(fn{n}).init.r2 = bonestructure.(fn{n}).init.r2 / L;
  end
  bonestructure.(fn{n}).formula = [];
  if isfield(bonestructure.(fn{n}).init, 'p1') && isfield(bonestructure.(fn{n}).init,'p2')
    L2 = norm(bonestructure.(fn{n}).init.p2 -  bonestructure.(fn{n}).init.p1);
    bonestructure.(fn{n}).formula.length = sprintf('L*%g',L2);
  else
    L2 = 0;
    bonestructure.(fn{n}).formula.length = sprintf('0');
  end
  if isfield(bonestructure.(fn{n}).init, 'r1')
    bonestructure.(fn{n}).formula.r1 = sprintf('L*R*%g',bonestructure.(fn{n}).init.r1);
    bonestructure.(fn{n}).formula.s1 = sprintf('L*R*S*%g',L2);
  end
  if isfield(bonestructure.(fn{n}).init, 'r2')
    bonestructure.(fn{n}).formula.r2 = sprintf('L*R*%g',bonestructure.(fn{n}).init.r2);
    bonestructure.(fn{n}).formula.s2 = sprintf('L*R*S*%g',L2);
  end
end

fhd = fopen('../data/FootModelDefault.json','wt');
fwrite(fhd, mat2json(bonestructure));
fclose(fhd);

return;


% Print code

fprintf(1,'\n\t// Links:\n');
for n = 1:size(bone,1);
	m = bone{n,1};
	if isnan(m)
		continue;
	end
	fprintf(1,'\t%s->AddChild(%s);\n', bone{m,2}, bone{n,2});
end



fhd = fopen('../data/FootModelDefault.txt','wt');


fprintf(1,'\n\t// Relative links:\n');
for n = 1:size(bone,1);
	
	parent = bone{n,1};
	name = bone{n,2};
	p1 = bone{n,3};
	r1 = bone{n,4};
	p2 = bone{n,5};
	r2 = bone{n,6};
	anchor = bone{n,7};
	
	if isnan(parent)
		p1p = [0,0,0];
		r1p = 0;
		p2p = [0,0,1];
		r2p = 0;
	else
		p1p = bone{parent,3};
		r1p = bone{parent,4};
		p2p = bone{parent,5};
		r2p = bone{parent,6};
	end	

	len = sqrt(sum((p2-p1).^2));
	lenp = sqrt(sum((p2p-p1p).^2));

	epsilon = 1e-6;
	
	if len < epsilon
		len = epsilon;
		normal = [0,0,1];
	else
		normal = (p2-p1)./len;
	end
	if lenp < epsilon
		lenp = epsilon;
		normalp = [0,0,1];
	else
		normalp = (p2p-p1p)./lenp;
	end
		
	anchorD = sum((anchor-p1p).*normalp);
	hp = anchorD*normalp+p1p;
	if isnan(parent)
		localR = 1.0;
	else
		localR = r1p + (r2p-r1p) * min(max(anchorD,0),1);
	end
	%anchorR = sqrt(sum((hp-anchor).^2));
	
	anchorN = (anchor-hp)/localR;
	link= (p1-anchor)/(localR+r1);

	s1 = 0.01;
	s2 = 0.01;
		
	fprintf('\t%s->anchorD = %g;\n',name, anchorD/lenp);
	fprintf('\t%s->anchorN.Set(%g, %g, %g);\n', name, ...
	   anchorN(1),anchorN(2),anchorN(3));
	
	fprintf('\t%s->link.Set(%g, %g, %g);\n', name, ...
	   link(1),link(2),link(3));

	fprintf('\t%s->normal.Set(%g, %g, %g);\n', name, ...
	   normal(1),normal(2),normal(3));
	
	fprintf('\t%s->length = %g;\n',name, len);

	fprintf('\t%s->r1 = %g;\n',name, r1);
	fprintf('\t%s->r2 = %g;\n',name, r2);
	
	fprintf('\t%s->s1 = %g;\n',name, s1);
	fprintf('\t%s->s2 = %g;\n',name, s2);
		
	% Print to file
	fprintf(fhd, '%s|%g|%g|%g', name, ...
	   anchorN(1),anchorN(2),anchorN(3));
	fprintf(fhd, '|%g|%g|%g', ...
	   link(1),link(2),link(3));
	fprintf(fhd, '|%g|%g|%g', ...
	   normal(1),normal(2),normal(3));
	fprintf(fhd, '|%g*L', anchorD/lenp/footLength);
	fprintf(fhd, '|%g*L', len/footLength);
	fprintf(fhd, '|%g*L*W', r1/footLength/footWidth);
	fprintf(fhd, '|%g*L*W', r2/footLength/footWidth);
	fprintf(fhd, '|%g*L*W', s1/footLength/footWidth);
	fprintf(fhd, '|%g*L*W\n', s2/footLength/footWidth);
		
%	return;
	
%	bone{n,5} = bone{n,5} - bone{n,3};
	
%	bL = sqrt(sum(bone{n,5}.^2));
%	if isnan(m) || bL == 0
%		bL = 1.0;
%	end
	
%	bone{n,3} = bone{n,3} - bone{n,7};
%	if isnan(m)
%		bone{n,7} = [0,0,0];
%	else	
%		bone{n,7} = bone{n,7} - bone{m,3};
%	end

%	fprintf('\t%s->r1 = %f;\n',bone{n,2},bone{n,4});
%	fprintf('\t%s->r2 = %f;\n',bone{n,2},bone{n,6});

%	fprintf('\t%s->p1.Set(%f, %f, %f);\n', ...
%	   bone{n,2}, bone{n,3}(1),bone{n,3}(2),bone{n,3}(3));
%	fprintf('\t%s->p2.Set(%f, %f, %f);\n', ...
%	   bone{n,2}, bone{n,5}(1),bone{n,5}(2),bone{n,5}(3));

%	fprintf('\t%s->link.Set(%f, %f, %f);\n', ...
%	   bone{n,2}, bone{n,3}(1),bone{n,3}(2),bone{n,3}(3));
%	fprintf('\t%s->bone.Set(%f, %f, %f);\n', ...
%	   bone{n,2}, bone{n,5}(1),bone{n,5}(2),bone{n,5}(3));
%	fprintf('\t%s->anchor.Set(%f, %f, %f);\n', ...
%	   bone{n,2}, bone{n,7}(1),bone{n,7}(2),bone{n,7}(3));

end
fclose(fhd);

