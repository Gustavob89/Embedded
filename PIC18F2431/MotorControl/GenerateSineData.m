clear
clc

%% Variables:
n = [];
counter = [];
function_decimal_values = [];
function_hexadecimal_values = [];

for counter = 1:1:256
	n(counter) = counter-1;
end

%%

filename = 'sinedata.inc';
file1 = fopen(filename,'w');

%fprintf(file1,'#include "p18f2431.inc" \r\n \r\n');
fprintf(file1,'SINE_SIGNAL code \r\n \r\n');
fprintf(file1,'load_sine; ------------------------------------ \r\n
\r\n');

%%

function_decimal_values = sin(2*pi*n/255) + 1;

% divide por 2 para testar com uma amplitude diferente
function_decimal_values = function_decimal_values / 2;

function_decimal_values = function_decimal_values * 255/2;
function_decimal_values = round(function_decimal_values);

%%

figure(1);
hold on
plot(n,function_decimal_values, '.');
ylabel('Duty-cycle value (integer)')
xlabel('Memory position (integer)')
axis( [ 0, 256, 0, 128 ] )
title('8 bit sinewave duty-cycle values')
hold off

%%

for counter = 1:1:256
	message1 = sprintf(' LFSR 0, 0x%s', dec2hex(counter-1));
	message2 = sprintf(' movlw 0x%s', ...
	dec2hex(function_decimal_values(counter)));
	message3 = sprintf(' movwf INDF0');
	message4 = sprintf('\n');
	fwrite(file1, message1);
	fprintf(file1, '\r\n');
	fwrite(file1, message2);
	fprintf(file1, '\r\n');
	fwrite(file1, message3);
	fprintf(file1, '\r\n');
	fprintf(file1, '\r\n');
end

fwrite(file1, ' return; ---------------------------------------');
fclose(file1);