close all;
clear all;

% % Load data
raw = csvread("ntc.csv");

% % Code
x = raw(:,1);
y = raw(:,2);

t = x;
ad = 1024 .* (y ./ (y + 10));

figure;
plot(ad, t, 'blue', 'LineWidth', 3)
ylim([-50 200]);
xlim([0 1200]);

ylabel('Temperature [°C]')
xlabel('Value')
grid on

p = polyfit(ad, t, 10);
ad2 = 0:1023;
t2 = round(polyval(p, ad2), 1);
hold on
plot(ad2, t2, 'r')

% % Conversion
dlmwrite('data.dlm', t2*10, ',');