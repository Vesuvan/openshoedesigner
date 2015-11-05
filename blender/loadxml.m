function y = loadxml(filename)
%LOADXML  Load a XML Description.
%
%   y = loadxml(filename)
%       Load the file into a cell structure.
%   
%   Input:
%       filename ...
%                   File to load
%
%   Output:
%       y ......... Cell structure

% Copyright (C) 2015 Tobias Schäfer

if nargin < 1
  help(mfilename());
  return
end


fhd = fopen(filename,'r');
if fhd <=0
	error('Konnte Datei nicht oeffnen.');
end
text = char(fread(fhd,Inf,'char*1')');
fclose(fhd);

tok = regexp(text,'<([^>]*)>','tokens');

y = cell(0,3);
level = cell(0,1);

for n = 1:length(tok)
	text = strtrim(tok{n}{1});
	if isempty(text)
		continue;
	end
	if text(1) == '?' || text(1) == '!'
		continue;
	end
	
	
	text = regexp(text,'(\/|[A-Za-z0-9_:]+|=|"[^"]*"|''[^'']*'')','tokens');
	if length(text) == 0
		continue;
	end
	flagOpen = true;
	flagKeepClose = false;
	flagClose = false;

	name = '';
	if text{1}{1}(1) == '/'
		flagClose = true;
		flagOpen = false;
		text = text(2:end);
	end
	if text{end}{1}(1) == '/'
		flagKeepClose = true;
		flagOpen = false;
		text = text(1:end-1);
	end
	if length(text) == 0
		error('Kein Tagname.');
	end
	name = text{1}{1};
	text = text(2:end);
	N = length(text);
	if mod(N,3) ~= 0
		disp(['Zeile ca.: ',mat2str(n)]);
		error('Zuweisungen passen nicht.');
	end
	pair = struct();
	for m = 1:(N/3)
		fname = text{m*3-2}{1};
		fname = strrep(fname,':','_');
		pair.(fname) = text{m*3-0}{1};
		if ~strcmp(text{m*3-1}{1},'=')
			error('Keine Zuweisung.');
		end
	end		

	if flagOpen
		level(end+1,1) = {name};	
	end	
	if flagOpen || flagKeepClose
		y(end+1,1) = {name};
		y(end,2) = {pair};
		y(end,3) = length(level);	
	end
	if flagClose
		if ~strcmp(name,level{end,1})
			disp(['Zeile ca.: ',mat2str(n)]);
			disp(tok{n}{1});
			disp(['Erwartet: ',level{end,1}]);
			disp(['Gefunden: ',name]);
			error('Namen passen nicht.')
		end
		level = level(1:end-1);
	end
end

