%PREPAREDATA  Converts the footbone data into a C-code.
%
%   Reads the FootBones.x3d file and parses it into some C-code for the 
%   LastGenerator software.
%   

% Copyright (C) 2015 Tobias Schäfer

filename = 'FootBones.x3d';

footLength = 28.67; % cm
EUSize = (footLength+2)/2*3; % = EU 46

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

% Add data to bones
for n = 1:length(tI)
  % Name of bone
	m =	find(strcmp(bone(:,2),tI{n}{2}));
	assert(~isempty(m), 'New bone in x3d file introduced. Adapt bone list.');
	assert(length(m) < 2, 'Two bones with same name in bone list.');
	
	N = str2num(tI{n}{1});
	pos = sscanf(tI{n}{3},'%f %f %f');
	pos = [-pos(1),pos(3),pos(2)];
	radius = sscanf(tI{n}{4},'%f %f %f');
	radius = mean(abs(radius));
	bone(m,(1:2)+2*N) = {pos/100,radius/100};
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



% Make all bones relative to their parents
for n = size(bone,1):-1:1
	m = bone{n,1};
	bone{n,5} = bone{n,5} - bone{n,3};
	bone{n,3} = bone{n,3} - bone{n,7};
	if isnan(m)
		bone{n,7} = [0,0,0];
	else	
		bone{n,7} = bone{n,7} - bone{m,3};
	end
end

% Print code

fprintf(1,'\n\t// Links:\n');
for n = 1:size(bone,1);
	m = bone{n,1};
	if isnan(m)
		continue;
	end
	fprintf(1,'\t%s->AddChild(%s);\n', bone{m,2}, bone{n,2});
end

fprintf(1,'\n\t// Relative links:\n');
for n = 1:size(bone,1);

	fprintf('\t%s->r1 = %f;\n',bone{n,2},bone{n,4});
	fprintf('\t%s->r2 = %f;\n',bone{n,2},bone{n,6});

%	fprintf('\t%s->p1.Set(%f, %f, %f);\n', ...
%	   bone{n,2}, bone{n,3}(1),bone{n,3}(2),bone{n,3}(3));
%	fprintf('\t%s->p2.Set(%f, %f, %f);\n', ...
%	   bone{n,2}, bone{n,5}(1),bone{n,5}(2),bone{n,5}(3));

	fprintf('\t%s->link.Set(%f, %f, %f);\n', ...
	   bone{n,2}, bone{n,3}(1),bone{n,3}(2),bone{n,3}(3));
	fprintf('\t%s->bone.Set(%f, %f, %f);\n', ...
	   bone{n,2}, bone{n,5}(1),bone{n,5}(2),bone{n,5}(3));
	fprintf('\t%s->anchor.Set(%f, %f, %f);\n', ...
	   bone{n,2}, bone{n,7}(1),bone{n,7}(2),bone{n,7}(3));



end



